global strlen:function
global strlen:function	
global strncmp:function
global strcasecmp:function
global strchr:function	
section .text

	;; strlen
strlen:
	xor rax,rax

strlen_loop:
	cmp byte [rdi+rax],0
	je  end_strlen_loop
	inc rax
	jmp strlen_loop

end_strlen_loop:
	ret

	;; strcmp
	
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

	;; strchr
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
	mov rax,rdi 				;setting the return value to rdi
	ret	 				 ;return rax wich is the value for return

	;; strncmp
strncmp:
	xor r8,r8
	xor rax,rax
	cmp rdx,0
	je end_strncmp
	
strncmp_loop:
	cmp r8,rdx
	je  end_strncmp_loop
	cmp byte [rdi+r8],0
	je  end_strncmp_loop
	cmp byte [rsi+r8],0
	je  end_strncmp_loop
	xor rcx,rcx		
	mov rcx,[rdi+r8]
	cmp byte [rsi+r8],cl
	jne  end_strncmp_loop
	inc r8
	jmp strncmp_loop
	
end_strncmp_loop:
	xor rcx,rcx
	mov rcx,[rdi+r8]
	cmp byte[rsi+r8],cl
	jge end_strncmp_neg
	mov al, [rdi+r8]
	sub al, [rsi+r8]
	ret

end_strncmp_neg:
	mov al, [rsi+rcx]
	sub al, [rdi+rcx]
	neg rax
end_strncmp:
	ret

	;; strcasecmp
strcasecmp:
	xor r8,r8
	xor rdx,rdx
	mov rdx,rdi
	xor rcx,rcx
	mov rcx,rsi
	
strcasecmp_loop:
	cmp byte [rdx+r8],0
	je  end_strcasecmp_loop
	cmp byte [rcx+r8],0
	je  end_strcasecmp_loop
	xor rdi,rdi
	mov dil,[rdx+r8]
	xor rsi,rsi
	xor sil,[rcx+r8]
	call strcasecmp_char
	cmp rax,0
	jne end_strcasecmp_loop
	inc r8
	jmp strcasecmp_loop
	
end_strcasecmp_loop:
	xor rdi,rdi
	mov dil,[rdx+r8]
	xor rsi,rsi
	xor sil,[rcx+r8]
	call strcasecmp_char
	ret

strcasecmp_char:
	call case_char
	xor rdi,rdi
	mov rdi, rsi
	xor rsi,rsi
	mov rsi, rax
	call case_char
	xor rdi,rdi
	mov rdi, rax
	xor rax,rax
	cmp rsi, rdi
	jg strcasecmp_char_neg
	mov rax,rsi
	sub rax,rdi
	ret
strcasecmp_char_neg:
	mov rax,rdi
	sub rax,rsi
	neg rax
	ret
	
case_char:
	xor rax,rax
	mov rax,rdi
	cmp al,65
	jl end_case_char
	cmp al,90
	jg end_case_char
	add rax,32
end_case_char:
	ret
