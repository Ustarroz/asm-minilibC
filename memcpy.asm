	BITS 64

        SECTION .text
        GLOBAL my_memcpy
	
my_memcpy:		
        xor rcx, rcx
	xor r8b, r8b

while1:	
        cmp rcx, rdx 
        je end
        mov r8b, [rsi + rcx]
	mov [rdi + rcx], r8b
        inc rcx
        jmp while1 

end:
	mov rax, rdi
        ret		
