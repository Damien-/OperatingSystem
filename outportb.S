.intel_syntax noprefix
.global outportb

outportb:
	push ebp
	mov ebp, esp
	push eax
	push edx

	mov edx, [ebp+8]
	mov eax, [ebp+12]
	out dx, al	

	pop edx
	pop eax
	pop ebp
	ret
