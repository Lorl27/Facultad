.data
a: .quad 0x11, 0x22, 0x33, 0x44, 0x55
b: .quad 0xaabbccddeeff

.text
.global main
main:
	movq a, %rax
	movq $a, %rbx
	leaq a, %rbx
	movq (%rbx), %rax
	movq 8(%rbx), %rax
	movq $3, %rcx 
	movq (%rbx, %rcx, 8), %rax
	movq 8(%rbx, %rcx, 8), %rax
	movq 16(%rbx, %rcx, 8), %rax
	xor	%eax, %eax
	ret