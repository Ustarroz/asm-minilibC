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
	mov dl,[rdi+rcx]
	cmp byte [rsi+rcx],dl
	jne  end_strcmp_loop
	inc rcx
	jmp strcmp_loop
	
end_strcmp_loop:
	xor rdx,rdx
	mov dl,[rdi+rcx]
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
