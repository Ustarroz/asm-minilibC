        BITS 64
	
        SECTION .text		
	GLOBAL my_strchr

strchr:
					;rdi is the base recuperation arguments
	mov rcx, 0 			;taking a couter (rcx can be an argument) and setting it to zero
	
while1: cmp BYTE[rdi + rcx], sil 		;comparison between the byte of rdi + rcx (sil is the fist 8 bits of the parameter)
	je end
	cmp byte[rdi + rcx], 0			;comparison between the byte and the \0
  	je end					;if 0 go to end
	inc rcx				  	  ;incrementing counter for next char
	jmp while1	  			  ;go back to while
	
end:
	mov rax, rdi 				;setting the return value to rdi
	ret	 				 ;return rax wich is the value for return

	
