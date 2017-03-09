	BITS 64
	
	SECTION .text
	GLOBAL my_memmove
	
my_memmove:
	mov rcx, rdx
	xor r8b, r8b
while1:
	cmp rcx, 0
	je end
	mov r8b, [rsi + rcx]
	mov [rdi + rcx], r8b
	dec rcx
	jmp while1
end:		
	mov rax, rdi
        ret
