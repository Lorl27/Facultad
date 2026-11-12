.data

.text
.global main
main:
	movq $5, %rdi
	movq $15, %rsi
	call suma
	xor	%eax, %eax
	ret
	
suma:
    addq %rdi, %rsi
    movq %rsi, %rax
    ret