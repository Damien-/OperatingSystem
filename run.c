#include "typedef.h"
extern void yield();
extern void writeScrPM(char* s, int i, int j);
uint8_t fin = 0;
void break4(){
	//writeScrPM("PLS STAHP", 21, 0);
	return;
}

int global_var = 0;
int finished = 0;
mutex_t m;  // make sure you call mutex_init(&m) in the main
          //   and put this declaration above the main to 
          //   appease the compiler.
int convert_num_h(unsigned int num, char buf[]) {
    if (num == 0) {
        return 0;
    }
    int idx = convert_num_h(num / 10, buf);
    buf[idx] = num % 10 + '0';
    buf[idx+1] = '\0';
    return idx + 1;
}

void convert_num(unsigned int num, char buf[]) {
    if (num == 0) {
        buf[0] = '0';
        buf[1] = '\0';
    } else {
        convert_num_h(num, buf);
    }
}
void p10(){
    int i = 0;
    char buf[100] = "P10 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 10);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 10, 0);
        mutex_unlock(&m);
    }
    while (finished != 10);
	if(global_var == 1000000) 	
		writeScrPM("Success!!", 11, 0);
	else 
		writeScrPM("Failiure", 11, 0);
	while(1);
}
void p1() {
    int i = 0;
    char buf[100] = "P1 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
	    break4();
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 1);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 1, 0);
        mutex_unlock(&m);
    }
    while (1);
}
void p2() {
    int i = 0;
    char buf[100] = "P2 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 2);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 2, 0);
        mutex_unlock(&m);
    }
    while (1);
}
void p3() {
    int i = 0;
    char buf[100] = "P3 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 3);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 3, 0);
        mutex_unlock(&m);
    }
    while (1);
}

void p4() {
    int i = 0;
    char buf[100] = "P4 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 4);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 4, 0);
        mutex_unlock(&m);
    }
    while (1);
}

void p5() {
    int i = 0;
    char buf[100] = "P5 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 5);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 5, 0);
        mutex_unlock(&m);
    }
    while (1);
}
void p6() {
    int i = 0;
    char buf[100] = "P6 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 6);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 6, 0);
        mutex_unlock(&m);
    }
    while (1);
}
void p7() {
    int i = 0;
    char buf[100] = "P7 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 7);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 7, 0);
        mutex_unlock(&m);
    }
    while (1);
}
void p8() {
    int i = 0;
    char buf[100] = "P8 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 8);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 8, 0);
        mutex_unlock(&m);
    }
    while (1);
}

void p9() {
    int i = 0;
    char buf[100] = "P9 Number is: ";
    for (i = 0; i < 100000; i++) {
        mutex_lock(&m);
        int my_var = global_var;
        my_var++;
        global_var = my_var;

        if (i == 99999) {
            finished++;
	    fin = 1;
	    writeScrPM("x", 20, 9);
        }
        convert_num(global_var, buf+14);
        writeScrPM(buf, 9, 0);
        mutex_unlock(&m);
    }
    while (1);
}


void run1(){
	int i = 0;
	writeScrPM("process p1:", 1, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 1, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("I", 1, 12+i); 	
		//asm("int $32");//yield();
	}
}
void run2(){
	int i = 0;
	writeScrPM("process p2:", 2, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 2, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("a", 2, 12+i); 	
		//asm("int $32");//yield();
	}
}
void run3(){
	int i = 0;
	writeScrPM("process p3:", 3, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 3, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("m", 3, 12+i); 	
		//asm("int $32");//yield();
	}
}
void run4(){
	int i = 0;
	writeScrPM("process p4:", 4, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 4, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("a", 4, 12+i); 	
		//asm("int $32");//yield();
	}
}
void run5(){
	int i = 0;
	writeScrPM("process p5:", 5, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 5, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("w", 5, 12+i); 	
		//asm("int $32");//yield();
	}
}
void run6(){
	int i = 0;
	writeScrPM("process p6:", 6, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 6, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("e", 6, 12+i); 	
		//asm("int $32");//yield();
	}
}
void run7(){
	int i = 0;
	writeScrPM("process p7:", 7, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 7, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("s", 7, 12+i); 	
		//asm("int $32");//yield();
	}
}
void run8(){
	int i = 0;
	writeScrPM("process p8:", 8, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 8, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("o", 8, 12+i); 	
		//asm("int $32");//yield();
	}
}
void run9(){
	int i = 0;
	writeScrPM("process p9:", 9, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 9, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("m", 9, 12+i); 	
		//asm("int $32");//yield();
	}
}
void run10(){
	int i = 0;
	writeScrPM("process p10:", 10, 0);
	//asm("sti");
	while(1){
		writeScrPM("           ", 10, 13);
		for(i = 0; i < 10; i++)
			writeScrPM("e", 10, 12+i); 	
		//asm("int $32");//yield();
	}
}
