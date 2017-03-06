	BITS 64

	SECTION .text
	GLOBAL my_memset

my_memset:
	mov rbx, 1
 				;taking a couter (rcx can be an argument) and setting it to zero
while1:
	cmp rbx ,rdx 		;comparison between the byte of rdi + rcx (sil is the fist 8 b\
	je end
	mov [rdi], sil
	je end		   			 ;if 0 go to end
	inc rbx
	inc rdi				;incrementing counter for next char
	jmp while1	  		 	 ;go back to while
	
end:
	mov rax, rdi 			;setting the return value to rdi
	ret	 			 ;return rax wich is the value for return
	
