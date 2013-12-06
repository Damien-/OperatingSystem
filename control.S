.intel_syntax noprefix
.global start
.global yield
.global schedule
.extern curr
.extern dequeue
.extern enqueue
.extern timerTick
.extern enqueueQ
.extern readyCheck
.global spinLock
.global unlock
.global mLock
.global break3
.local mque, rdyB, mB

unlock:
	push eax
	push ebx

	mov eax, 0
	mov ebx, [esp + 12]
	xchg eax, [ebx]

	pop ebx
	pop eax
	ret

spinLock:
	push eax
	push ebx
	mov ebx, [esp + 12]
_spinloop:
	
	mov eax, 1
	xchg eax, [ebx]
	cmp eax, 0
	jne _spinloop
	
	pop ebx
	pop eax
	ret

yield:
	pushf
	push cs
	push OFFSET _yPLS
	pushad
	push ds
	push es
	push fs
	push gs
	mov eax, [curr]
	mov [eax], esp
	mov [eax+4], ss	

	call enqueue
	call dequeue	

	mov [curr], eax
	mov esp, [eax]
	mov ss, [eax+4]
	pop gs
	pop fs
	pop es
	pop ds
	popad
	iret
_yPLS:
	ret

mLock:	
	#to make sure timer does not interrupt it
	#cli
	#function was not storing where to jump back when switching context
	#only wasted 6 hours on that...
	push eax
	
	mov eax, 0
	mov timerTick, eax	

	mov eax, [esp + 8]
	mov mque, eax
	mov eax, [esp + 12]
	mov rdyB, eax
	mov eax, [esp + 16]
	mov mB, eax

	pop eax

	pushf
	push cs
	push OFFSET _rhrh

	pushad
	push ds
	push es
	push fs
	push gs
	mov eax, [curr]
	mov [eax+4], ss		
	mov [eax], esp

	#enqueue current on the mutex que(qq)
	pushd mque
	call enqueueQ
	
	#test if mutex que works or not by running everything on ready q
	#call enqueue

	#unlock the bolt on mutex
	pushd mB
	call unlock

	#get lock on the ready que
	pushd rdyB
	call spinLock

	#deque and start running the process from ready que
	call dequeue

	mov [curr], eax
	mov esp, [eax]
	mov ss, [eax+4]
	pop gs
	pop fs
	pop es
	pop ds
	popad	

	iret
_rhrh:
	ret

schedule:
	push eax
	mov al, 0x20
	out 0x20, al
	push edx
	mov edx, timerTick
	inc edx
	//if timerTicks is 3 then goto SWITCH
	mov timerTick,edx
	cmpb edx, 3
	pop edx
	je _switch
	pop eax
	iret
_switch:
	mov eax, 0
	mov timerTick, eax
	pop eax
_swc:
	pushad
	push ds
	push es
	push fs
	push gs
	mov eax, [curr]
	mov [eax+4], ss	
	mov [eax], esp	
	
	call enqueue
start:
	call dequeue	

	mov [curr], eax
	mov ss, [eax+4]
	mov esp, [eax]
	pop gs
	pop fs
	pop es
	pop ds
	popad
	iret
