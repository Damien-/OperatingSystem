#include "typedef.h"

lgdt_t lgdtT;
lidt_t lidtT;
gdt_entry_t gdt[5];
idt_entry_t idt[256];
pcb_t* head;
pcb_t* tail;
pcb_t* curr;
pcb_t* mdeq;
uint8_t timerTick = 0;

int readyQready=0;


int pcb_next=0;
pcb_t pcbs[PRCS_NO+1];
uint32_t stack[PRCS_NO+1][STACK_SIZE];

void outportb(uint16_t p, uint8_t o);
extern void enqueue();
extern void dequeue();

extern void run1();
extern void run2();
extern void run3();
extern void run4();
extern void run5();
extern void run6();
extern void run7();
extern void run8();
extern void run9();
extern void run10();

extern void p1();
extern void p2();
extern void p3();
extern void p4();
extern void p5();
extern void p6();
extern void p7();
extern void p8();
extern void p9();
extern void p10();

extern mutex_t m;


void writeScrPM(char* s, int row, int col);
void printMutex(){
	char buf[100] = "Lock = ;";
	char buf2[100] = "Bolt = ;";
	convert_num(m.lock, buf+7);
	convert_num(m.bolt, buf2+7);
	writeScrPM(buf, 12, 0);
	writeScrPM(buf2, 12, 9);
}
void printIDH(){
	asm("cli");/*
	if(head == null) {
		writeScrPM("NULL                                       ", 17, 0);
		asm("sti");
		return;
	}//*/
	pcb_t* p = head;
	writeScrPM("                                          ", 17, 0);
	int i = 0;
	while(p){
		char buf[100] = "  ";
		convert_num(p->id, buf+1);
		writeScrPM(buf, 17, i);
		i = i+3;
		p = p->next;
	}
	asm("sti");
}
void printIDM(){
	asm("cli");
	if(m.q == null) {
		writeScrPM("NULL                                       ", 18, 0);
		asm("sti");
		return;
	}
	pcb_t* p = m.q;
	writeScrPM("                                          ", 18, 0);
	int i = 0;
	while(p){
		char buf[100] = "  ";
		convert_num(p->id, buf+1);
		writeScrPM(buf, 18, i);
		i = i+3;
		p = p->next;
	}
	asm("sti");
}
void loadGDT(lgdt_t* l);
void loadIDT(lidt_t* l);
void loadSegments(uint8_t c,uint8_t d,uint8_t s,uint8_t f,uint8_t e);
void writeScr(char* s, int row, int col);
void clearScr(){
	int i, j;	
	for(i = 0; i < 25; i++)
		for(j = 0;j < 80; j++)
			writeScr(" ", i , j);	
}
void clearScrPM(){
	int i, j;	
	for(i = 0; i < 25; i++)
		for(j = 0;j < 80; j++)
			writeScrPM(" ", i , j);	
}

void start();
void yield();
void schedule();
void defaultHandler(){
	writeScrPM("Error: Default Interrupt Handler has been triggered!", 0, 0);
	while(1);
}
void initGDTEntry(gdt_entry_t *entry, uint32_t baseAddress, uint32_t limit, uint8_t access, uint8_t attributes){
	
	entry->base_low = baseAddress & 0xFFFF;
	entry->base_mid = (baseAddress >> 16) & 0xFF;
	entry->base_high = (baseAddress >> 24) & 0xFF;
	
	entry->limit_low = limit & 0xFFFF;
	entry->attr = (limit >> 16) & 0x0F;

	entry->attr |= (attributes & 0xF0);
	entry->access = access;
	
}
void initIDTEntry(idt_entry_t *entry, uint32_t base, uint16_t selector, uint8_t access){
	entry->base_low16 = base & 0xFFFF;
	entry->base_hi16 = (base >> 16) & 0xFFFF;
	entry->selector = selector & 0xFFFF;
	entry->access = access;
	entry->always0 = 0x0;
}
void constructGDT(){	
	uint8_t acs, atr;
	acs = 0; atr = 0;
	uint32_t limit = 0;
	uint32_t base = 0;
	initGDTEntry(&gdt[0], base, limit, acs, atr);
	limit = 655359;	acs = 154; atr = 64;
	initGDTEntry(&gdt[1], base, limit, acs, atr);
	acs = 146;
	initGDTEntry(&gdt[2], base, limit, acs, atr);
	initGDTEntry(&gdt[3], base, limit, acs, atr);
	base = 753664; limit = 3999;
	initGDTEntry(&gdt[4], base, limit, acs, atr);	
}
void constructIDT(){
	uint8_t access = 0x8e;
	uint16_t selector = 0x08;
	int i = 0;	
	// 0 - 31 setting these entries to point to the default handler
	for(i = 0; i < 32; i++)
		initIDTEntry(&idt[i], (uint32_t) defaultHandler, selector, access);
	// point to your schedule function
	initIDTEntry(&idt[32], (uint32_t) schedule, selector, access);
	//entries 33 to 255 setting these entries to point to 0	
	for(i = 33; i < 256; i++)
		initIDTEntry(&idt[i], 0, 0, 0);
}

pcb_t* allocatePCB(){
	return &pcbs[(pcb_next++)%PRCS_NO];
}
void createProcess(uint32_t ds, uint32_t ss, uint32_t* stackTop, uint32_t cs, uint32_t processEntry){
	uint32_t* sp = stackTop;
	// eflags
	*(sp--) = 0x200;
	// cs
	*(sp--) = cs;
	// entry	
	*(sp--) = processEntry;
	//ebp
	*(sp--) = 0;		
	//esp
	*(sp--) = 0;	
	//edi
	*(sp--) = 0;
	//esi
	*(sp--) = 0;
	//edx
	*(sp--) = 0;
	//ecx
	*(sp--) = 0;
	//ebx
	*(sp--) = 0;
	//eax
	*(sp--) = 0;
	//ds
	*(sp--) = ds;
	//es - video
	*(sp--) = ds;
	//fs
	*(sp--) = ds;
	//gs
	*(sp) = ds;
	pcb_t* t = allocatePCB();
	t->id = pcb_next;
	t->ss = ss;
	t->esp = (uint32_t) sp;
	curr = t;
	//enqueueQ(&mtest);
	enqueue();
	curr = null;
	
}
void setupPIC() {
	outportb(0x20, 0x11); // start 8259 master initialization
	outportb(0xA0, 0x11); // start 8259 slave initialization
	outportb(0x21, 0x20); // set master base interrupt vector (idt 32-38)
	outportb(0xA1, 0x28); // set slave base interrupt vector (idt 39-45)
	outportb(0x21, 0x04); // set cascade ...
	outportb(0xA1, 0x02); // on IRQ2
	outportb(0x21, 0x01); // finish 8259 initialization
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
	outportb(0x21, 0xfe); // Turn on the clock IRQ
	outportb(0xa1, 0xff); // Turn off all others
}

int main(){
	int i = 0;
	clearScr();
	writeScr("Initializing OS", 0, 0);
	writeScr("Setting up OS descriptors...", 1, 0);

	constructGDT();
	lgdtT.offset = (uint32_t) &gdt;
	lgdtT.limit = (sizeof(struct gdt_entry)*5) - 1;
	loadGDT(&lgdtT);

	constructIDT();
	lidtT.offset = (uint32_t) &idt;
	lidtT.limit = (sizeof(struct idt_entry)*256) - 1;
	loadIDT(&lidtT);
	
	asm("cli");
	setupPIC();

	uint8_t cs = 8;
	uint8_t ds = 16; 
	uint8_t ss = 24;
	uint8_t fs = ds; 
	uint8_t es = 32;

	loadSegments(cs,ds,ss,fs,es);
	
	writeScrPM("done.", 2, 28);
	clearScrPM();
	head = null;
	tail = null;

  	writeScrPM("Running ten processes...", 0, 0);
	writeScrPM("-          -", 20, 0);
	mutex_init(&m);

	// Process 1
	createProcess(ds,  ss, stack[0] + STACK_SIZE, cs, (uint32_t) p1);
	
	// Process 2
	createProcess(ds,  ss, stack[1] + STACK_SIZE, cs, (uint32_t) p2);
	
	// Process 3
	createProcess(ds,  ss, stack[2] + STACK_SIZE, cs, (uint32_t) p3);
	
	// Process 4
	createProcess(ds,  ss, stack[3] + STACK_SIZE, cs, (uint32_t) p4);
	
	// Process 5
	createProcess(ds,  ss, stack[4] + STACK_SIZE, cs, (uint32_t) p5);
	
	// Process 6
	createProcess(ds,  ss, stack[5] + STACK_SIZE, cs, (uint32_t) p6);
	
	// Process 7
	createProcess(ds,  ss, stack[6] + STACK_SIZE, cs, (uint32_t) p7);
	// Process 8
	createProcess(ds,  ss, stack[7] + STACK_SIZE, cs, (uint32_t) p8);
	// Process 9
	createProcess(ds,  ss, stack[8] + STACK_SIZE, cs, (uint32_t) p9);
	// Process 10
	createProcess(ds,  ss, stack[9] + STACK_SIZE, cs, (uint32_t) p10);
	//*/
	start();
}
