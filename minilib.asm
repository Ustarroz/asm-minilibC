global strlen:function
global strlen:function	
global strncmp:function
global strcmp:function
global strcasecmp:function
global strchr:function	
section .text

	;; strlen
strlen:
	xor rax,rax		;set rax to 0: use as increment

strlen_loop:
	cmp byte [rdi+rax],0	;compare the byte of rdi (string) at pos rax with 0
	je  end_strlen_loop	;end function in case of eq
	inc rax			;increment rax
	jmp strlen_loop		;go back to the begining of the loop

end_strlen_loop:
	ret			;return the value store in rax

	;; strcmp
	
strcmp:
	xor rcx,rcx		;set rcx to 0 (use as increment)
	
strcmp_loop:
	cmp byte [rdi+rcx],0	;compare the byte of rdi (string1) at pos rcx with 0: end of string1
	je  end_strcmp_loop	;end loop in case of eq
	cmp byte [rsi+rcx],0	;compare the byte of rsi (string2) at pos rcx with 0: end of string2
	je  end_strcmp_loop	;end loop in case of eq
	xor rdx,rdx
	mov rdx,[rdi+rcx]	;use rdx to store one of the byte (can't compare two byte of a string)
	cmp byte [rsi+rcx],dl	;compare byte of the two string at pos rcx
	jne  end_strcmp_loop	;end loop if not equal: char comparison
	inc rcx
	jmp strcmp_loop
	
end_strcmp_loop:
	xor rdx,rdx
	mov rdx,[rdi+rcx]
	cmp byte[rsi+rcx],dl	;compare the byte at rcx (different char or end)
	jge end_strcmp_neg	;if string2 gt than string1, go to negative result
	xor rax, rax	
	mov al, [rdi+rcx]	;store byte of string1 in rax (al subpart of rax)
	sub al, [rsi+rcx]	;substract byte of string2 from byte of string2 (rax = string1 - string2)
	ret			;return rax

end_strcmp_neg:
	xor rax, rax
	mov al, [rsi+rcx]	;store byte of string2 in rax (al first byte of rax)
	sub al, [rdi+rcx]	;substract byte of string1 from byte of string2 (rax = string2 - string1)
	neg rax			;neg rax to obtain the result of strcmp (rax = string1 - string2)
	ret			;return rax

	;; strchr
strchr:
				;rdi is the base recuperation arguments
	mov rcx, 0 		;taking a couter (rcx can be an argument) and setting it to zero
	
while_strchr:
	cmp BYTE[rdi + rcx], sil ;compare the byte of rdi + rcx and sil (the fist byte of the rdi)
	je end_strchr
	cmp byte[rdi + rcx], 0	;comparison between the byte and the \0
  	je end_strchr		;if 0 go to end
	inc rcx			;incrementing counter for next char
	jmp while_strchr	;go back to while
	
end_strchr:
	mov rax,rdi		;setting the return value to rdi
	ret			;return rax wich is the value for return

	;; strncmp
strncmp:
	xor r8,r8		;set r8 as 0 for inc
	xor rax,rax		;set rax as 0 for the ret
	cmp rdx,0		;check if the rdx (number of byte to cmp) equal 0
	je end_strncmp		;left the progr if no byte to compare
	
strncmp_loop:
	cmp r8,rdx		;
	je  end_strncmp_loop
	cmp byte [rdi+r8],0
	je  end_strncmp_loop
	cmp byte [rsi+r8],0
	je  end_strncmp_loop
	xor rcx,rcx
	mov rcx,[rdi+r8]
	cmp byte [rsi+r8],cl
	jne end_strncmp_loop
	inc r8
	jmp strncmp_loop
	
end_strncmp_loop:
	xor rcx,rcx
	mov rcx,[rdi+r8]
	cmp byte[rsi+r8],cl
	jge end_strncmp_neg
	mov al, [rdi+r8]
	sub al, [rsi+r8]
	mov rax, 1
	ret

end_strncmp_neg:
	mov al, [rsi+r8]
	sub al, [rdi+r8]
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
