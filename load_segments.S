.intel_syntax noprefix
.global loadSegments
	
loadSegments:
	push ebp	
	mov ebp, esp		
	push eax
	pushf
	
	mov eax, [ebp+12] // set up ds selector
	mov ds, eax
	// note that gs = fs = ds
	mov eax, [ebp+24] // set up es selector
	mov es, eax
	mov eax, [ebp+20] // set up fs selector
	mov fs, eax
	mov eax, [ebp+20] // set up gs selector
	mov gs, eax
	/* The next two lines will only mess up the stack if the esp
	now points to someplace different. However, we set it up so
	that our new selector points the same place as the one set
	up by the boot loader */
	mov eax, [ebp+16] // set up ss selector
	mov ss, eax
	mov eax, [ebp+8] // now we load cs. 
	push eax
	push OFFSET _loadcs
	retf
_loadcs:
	popf
	pop eax 
	pop ebp
	ret
