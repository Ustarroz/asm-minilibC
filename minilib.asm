BITS 64
	
global strlen
global strcmp
global strncmp
global strcasecmp
global strchr
global memset
global memcpy
global memmove
global rindex
global strstr
global strpbrk
global strcspn
global write
global read
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
	cmp rdi,0
	je end_strchr_null
				;rdi is the base recuperation arguments
	mov rcx, 0 		;taking a couter (rcx can be an argument) and setting it to zero
	
while_strchr:
	cmp BYTE[rdi + rcx], sil ;compare the byte of rdi + rcx and sil (the fist byte of the rdi)
	je end_strchr
	cmp byte[rdi + rcx], 0	;comparison between the byte and the \0
  	je end_strchr_null		;if 0 go to end
	inc rcx			;incrementing counter for next char
	jmp while_strchr	;go back to while
	
end_strchr:
	mov rax,rdi		;setting the return value to rdi
	add rax,rcx
	ret			;return rax wich is the value for return
end_strchr_null:
	xor rax,rax
	ret

	;; strncmp
strncmp:
	xor r8,r8		;set r8 as 0 for inc
	xor rax,rax		;set rax as 0 for the ret
	cmp rdx,0		;check if the rdx (number of byte to cmp) equal 0
	je end_strncmp		;left the progr if no byte to compare
	sub rdx,1
	
strncmp_loop:
	cmp r8,rdx		;check for end of strncmp
	je  end_strncmp_loop
	cmp byte [rdi+r8],0	;compare str1 to end
	je  end_strncmp_loop
	cmp byte [rsi+r8],0	;compare str2 to end
	je  end_strncmp_loop
	xor rcx,rcx
	mov rcx,[rdi+r8]	;use rcx to store a byte of str1
	cmp byte [rsi+r8],cl	;compare byte of str2 (in rdi+r8) and str1
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

	;; memset
memset:
	xor rcx, rcx
	mov rax, rdi
 				;taking a couter (rcx can be an argument) and setting it to zero
loop_memset:			;comparison between the byte of rdi + rcx (sil is the fist 8
	cmp rcx,rdx
	je end_memset
	mov byte [rax+rcx],sil
	inc rcx			;incrementing counter for next char
	jmp loop_memset          ;go back to while
end_memset:
	ret	 		;return rax wich is the value for return


	;; rindex
rindex:
	call strlen
	xor rdx, rdx
	mov rdx, rax
	xor rax,rax
	mov rax, rdi
rindex_loop:
	cmp byte [rax+rdx],sil
	je  end_rindex_loop
	dec rdx
	cmp rdx,0
	jge rindex_loop
	
end_rindex_null:	
	xor rax,rax
	ret
end_rindex_loop:
	add rax,rdx
	ret


	;; memcpy
memcpy:
	cmp rdi, 0
	je end_memcpy
        xor rcx, rcx
	xor r8, r8

while_memcpy:	
        cmp rcx, rdx 
        je end_memcpy
        mov r8b, [rsi + rcx]
	mov [rdi + rcx], r8b
        inc rcx
        jmp while_memcpy

end_memcpy:
	mov rax, rdi
        ret		

	;; strstr
strstr:
	cmp rdi, 0
	je end_null_strstr
	cmp rsi, 0
	je end_null_strstr
	xor rax,rax
	mov rax,rdi
	xor r8,r8
	mov r8b,[rsi]
	cmp r8, 0
	je end_strstr
	xor rcx, rcx
	xor rdx, rdx
	mov rdx, rdi
	
while_strstr:
	cmp byte [rdx+rcx], 0
	je end_null_strstr
	xor r8,r8
	mov r8b,[rsi]
	cmp byte [rdx+rcx],r8b
	jne redo_loop_strstr
	mov rdi,rdx
	add rdi,rcx
	call cmp_strstr
	cmp rax,0
	jne end_strstr
	inc rcx
	jmp while_strstr
redo_loop_strstr:
	inc rcx
	jmp while_strstr
end_null_strstr:
	xor rax, rax
end_strstr:	
	ret

cmp_strstr:
	xor r8,r8
	xor rax,rax
	mov rax,rdi

while_cmp_strstr:
	cmp byte [rsi+r8],0
	je end_cmp_strstr
	cmp byte [rax+r8],0
	je end_null_cmp_strstr
	xor r9,r9
	mov r9b, [rsi+r8]
	cmp byte [rax+r8],r9b
	jne end_null_cmp_strstr
	inc r8
	jmp while_cmp_strstr
end_null_cmp_strstr:
	xor rax,rax
end_cmp_strstr:	
	ret

	
	;; memmove
memmove:
	cmp rdi,0
	je end_memmove_null
	cmp rsi,0
	je end_memmove_null
	mov rcx, rdx
	xor r8b, r8b
	cmp rdi,rsi
	jg while_memmove
	call memcpy
	ret
	
while_memmove:
	cmp rcx, 0
	je end_memmove
	dec rcx
	mov r8b, [rsi + rcx]
	mov [rdi + rcx], r8b
	jmp while_memmove
end_memmove:		
	mov rax, rdi
        ret
end_memmove_null:
	xor rax,rax
	ret

	;; strpbrk

strpbrk:
	cmp rdi,0
	je strpbrk_null
	cmp rsi,0
	je strpbrk_null
	xor rcx, rcx
	xor r8,r8
	xor rdx, rdx
	mov rdx, rsi
strpbrk_loop:
	cmp byte [rdx+rcx],0
	je strpbrk_end
	xor rsi,rsi
	mov sil,[rdx+rcx]
	call index
	inc rcx
	cmp rax,0
	je strpbrk_loop
	cmp r8,0
	je strpbrk_replace
	cmp r8,rax
	jg strpbrk_replace
	jmp strpbrk_loop
strpbrk_replace:
	xor r8,r8
	mov r8,rax
	jmp strpbrk_loop
	
strpbrk_end:
	cmp r8,0
	je strpbrk_null
	xor rax,rax
	mov rax,r8
	ret
strpbrk_null:
	xor rax,rax
	ret

index:
	xor rax, rax
	mov rax, rdi
	
index_loop:
	cmp byte [rax],0
	je  end_index_null
	cmp byte [rax],sil
	je  end_index_loop
	inc rax
	jmp index_loop

end_index_null:
	xor rax, rax
end_index_loop:
	ret

	;; strcspn
strcspn:
	xor rdx,rdx
	xor r8,r8
	cmp rdi,0
	je strcspn_index_end
	cmp rsi,0
	je strcspn_index_end
	xor rcx,rcx
	mov rcx,rdi
	xor rdi,rdi
	mov rdi,rsi
strcspn_index_loop:
	cmp byte [rcx+rdx],0
	je strcspn_index_end
	xor rsi,rsi
	mov sil,[rcx+rdx]
	call index
	cmp rax,0
	jne strcspn_index_end
	inc r8
	inc rdx
	jmp strcspn_index_loop
	
strcspn_index_end:
	xor rax,rax
	mov rax,r8
	ret

	;; write

write:
	xor rax,rax
	mov rax,1
	syscall
	ret

	;; read
read:
	xor rax,rax
	syscall
	ret
