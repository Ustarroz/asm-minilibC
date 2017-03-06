global strlen:function
global strcmp:function
section .text
	
strlen:
	xor rax,rax

strlen_loop:
	cmp byte [rdi+rax],0
	je  end_strlen_loop
	inc rax
	jmp strlen_loop

end_strlen_loop:
	ret

strcmp:
	xor rcx,rcx
	
strcmp_loop:
	cmp byte [rdi+rcx],0
	je  end_strcmp_loop
	cmp byte [rsi+rcx],0
	je  end_strcmp_loop
	xor rdx,rdx		
	mov rdx,[rdi+rcx]
	cmp byte [rsi+rcx],dl
	jne  end_strcmp_loop
	inc rcx
	jmp strcmp_loop
	
end_strcmp_loop:
	xor rdx,rdx		
	mov rdx,[rdi+rcx]
	cmp byte[rsi+rcx],dl
	jge end_strcmp_neg
	xor rax, rax	
	mov al, [rdi+rcx]
	sub al, [rsi+rcx]
	ret

end_strcmp_neg:
	xor rax, rax	
	mov al, [rsi+rcx]
	sub al, [rdi+rcx]
	neg rax
	ret

strchr:
					;rdi is the base recuperation arguments
	mov rcx, 0 			;taking a couter (rcx can be an argument) and setting it to zero
	
while_strchr: cmp BYTE[rdi + rcx], sil 		;comparison between the byte of rdi + rcx (sil is the fist 8 bits of the parameter)
	je end_strchr
	cmp byte[rdi + rcx], 0			;comparison between the byte and the \0
  	je end_strchr					;if 0 go to end
	inc rcx				  	  ;incrementing counter for next char
	jmp while_strchr	  			  ;go back to while
	
end_strchr:
	mov rax, rdi 				;setting the return value to rdi
	ret	 				 ;return rax wich is the value for return
