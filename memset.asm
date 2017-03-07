	BITS 64

	SECTION .text
	GLOBAL my_memset

my_memset:
	xor rcx, rcx
 				;taking a couter (rcx can be an argument) and setting it to zero
while1:
	cmp rcx ,rdx 		;comparison between the byte of rdi + rcx (sil is the fist 8 b\
	je end
	mov [rdi + rcx], sil
	inc rcx			;incrementing counter for next char
	jmp while1	  		 	 ;go back to while
	
end:
	mov rax, rdi 			;setting the return value to rdi
	ret	 			 ;return rax wich is the value for return
	
