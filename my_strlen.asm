global strlen:function
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
