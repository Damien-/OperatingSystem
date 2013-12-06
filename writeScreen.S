.intel_syntax noprefix
.global writeScr
.global writeScrPM

writeScr:

	push ebp
	mov ebp, esp
	pushf
	cli
	push eax
	push esi
	push edi
	
	mov eax, 0
	add eax, 0xB8000
	mov edi, eax

	mov eax, [ebp+12]
	imul eax, 80
	add eax, [ebp+16]
	shl eax, 1
	add edi, eax
	
	mov esi, [ebp+8]
	
_check:
	cmpb [esi],0
	je _done
	movsb es:[edi], ds:[esi]
	movb es:[edi], 31
	inc edi
	jmp _check

writeScrPM:

	push ebp
	mov ebp, esp
	pushf
	cli	
	push eax
	push esi
	push edi

	mov eax, 0
	mov edi, eax
	
	mov eax, 32
	mov es, eax

	mov eax, [ebp+12]
	imul eax, 80
	add eax, [ebp+16]
	shl eax, 1
	add edi, eax
	
	mov esi, [ebp+8]
	
_checkPM:
	cmpb [esi],0
	je _done
	movsb es:[edi], ds:[esi]
	movb es:[edi], 31
	inc edi
	jmp _checkPM
	
_done:	

	pop edi
	pop esi
	pop eax
	popf
	pop ebp

	ret
	
