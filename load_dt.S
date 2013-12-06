.intel_syntax noprefix
.global loadGDT
.global loadIDT
loadGDT:
	push ebp
	mov ebp, esp

	push eax
	mov eax,[ebp+8]

	lgdt [eax]

	pop eax
	pop ebp
	ret
loadIDT:
	push ebp
	mov ebp, esp

	push eax
	mov eax,[ebp+8]

	lidt [eax]

	pop eax
	pop ebp
	ret
