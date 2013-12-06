#ifndef _TYPES
#define _TYPES

#define null 0
#define STACK_SIZE 1024
#define PRCS_NO 10

//Types used
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

//GDT ENTRY
typedef struct gdt_entry{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t attr;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;
//IDT
typedef struct idt_entry{
	uint16_t base_low16;
	uint16_t selector;
	uint8_t always0;
	uint8_t access;
	uint16_t base_hi16;
} __attribute__((packed)) idt_entry_t;
//LGDT
typedef struct lgdt{
	uint16_t limit;
	uint32_t offset;
}__attribute__((packed)) lgdt_t;
//LIDT
typedef struct lidt{
	uint16_t limit;
	uint32_t offset;
}__attribute__((packed)) lidt_t;

//PCB
typedef struct pcb{
	uint32_t esp;
	uint32_t ss;
	uint8_t id;
	struct pcb* next;
}pcb_t;
//Mutex
typedef struct mutex{
	int lock;
	int bolt; 
	pcb_t* q;
}mutex_t;


#endif
