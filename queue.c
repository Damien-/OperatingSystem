#include "typedef.h"

extern pcb_t* head;
extern pcb_t* curr;
extern pcb_t* mdeq;
extern mutex_t m;

extern void printIDH();
extern void printIDM();
void break2(){}


void enqueue(){
	if(head == null){
		head = curr;
		head->next = null;
	}
	else{
		pcb_t* tmp = head;
		while(tmp->next)
			tmp = tmp->next;		
		tmp->next = curr;
		tmp = tmp->next;
		tmp->next = null;					
	}
	curr = null;
	printIDH();
	printIDM();
}

void enqueueT(){
	if(head == null){
		head = mdeq;
		head->next = null;
	}
	else{
		pcb_t* tmp = head;
		while(tmp->next != null)
			tmp = tmp->next;		
		tmp->next = mdeq;
		tmp = tmp->next;
		tmp->next = null;					
	}
	printIDH();
	printIDM();
}
void dequeue(){
	if(head == null) return;
	if(head->next == null) {
		curr = head;
		head = null;
	}
	else{
		curr = head;
		head = head->next;
		curr->next = null;
	}
	//printIDH();
}


void enqueueQ(pcb_t** q){
	if(*q == null){
		*q = curr;
		(*q)->next = null;
	}
	else{
		pcb_t* tmp = *q;
		while(tmp->next!=null)
			tmp = tmp->next;		
		tmp->next = curr;
		tmp = tmp->next;
		tmp->next = null;					
	}
	curr = null;
	//printIDM();
}
void enqueueMQ(){
	pcb_t* t = m.q;
	if(t == null){
		t = curr;
		t->next = null;
	}
	else{
		pcb_t* tmp = t;
		while(tmp->next!=null)
			tmp = tmp->next;		
		tmp->next = curr;
		tmp = tmp->next;
		tmp->next = null;					
	}
	curr = null;
	//printIDM();
}
/*
void enqueueQ(pcb_t* q){
	if(q == null){
		q = curr;
		q->next = null;
	}
	else{
		pcb_t* tmp = q;
		while(tmp->next)
			tmp = tmp->next;		
		tmp->next = curr;
		tmp = tmp->next;
		tmp->next = null;					
	}
	curr = null;
}//*/
void dequeueQ(pcb_t** q){
	if(*q == null) return;
	if((*q)->next == null) {
		mdeq = *q;
		*q = null;
	}
	else{
		mdeq = *q;
		*q = (*q)->next;
		mdeq->next = null;
	}
}
