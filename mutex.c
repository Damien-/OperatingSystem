#include "typedef.h"
extern pcb_t* head;
extern pcb_t* curr;
extern pcb_t* mdeq;

extern uint8_t timerTick;
extern void printMutex();
extern int readyQready;
extern void start();
extern void writeScrPM();
int rdy = 0;
int* rdyB = 0;
pcb_t** mque = 0;
int* mB = 0;
extern uint8_t fin;
void break3(){}


void mutex_init(mutex_t* m){
	m->lock = 0;
	m->bolt = 0;
	m->q = null;
}
extern void spinLock(int* b);
extern void unlock(int* l);
extern void mLock(pcb_t** q, int* s, int* d);
extern void mLdeq();

extern void printIDH();
extern void printIDM();

void break1(){
	writeScrPM("BB1", 20, 0);
}

void readyCheck(int* s){
	if(head != null) unlock(s);
}

void mutex_lock(mutex_t* m){
	
	writeScrPM("LOCK ENTERED!!     ", 13, 0);
	writeScrPM("L",14,0);
	spinLock(&(m->bolt));
	if(m->lock == 1){
		writeScrPM("LOCKED ALREADY!!     ", 13, 0);
		mLock(&(m->q), &readyQready, &(m->bolt));
		unlock(&readyQready);	       
	}
	else{
		writeScrPM("LOCKING DOWN!!", 13, 0);
		spinLock(&(m->lock));	        
		unlock(&(m->bolt));
	}
	writeScrPM("LOCK EXITING      ", 13, 0);
}

void mutex_unlock(mutex_t* m){  
	writeScrPM("UNLOCK ENTERED!!", 15, 0);
	writeScrPM("U",14,0);
	spinLock(&(m->bolt));
	if(m->q != null && timerTick == 2){		
		dequeueQ(&(m->q));
		enqueueT();
		unlock(&readyQready);
	}
	else if(m->q != null && fin == 1){
		fin = 0;
		dequeueQ(&(m->q));
		enqueueT();
		unlock(&readyQready);
			
	}
	else{
		writeScrPM("UNLOCKING", 15, 0);
		unlock(&(m->lock));
	}
	writeScrPM("UNLOCK EXITING       ", 15, 0);
	unlock(&(m->bolt));

}
