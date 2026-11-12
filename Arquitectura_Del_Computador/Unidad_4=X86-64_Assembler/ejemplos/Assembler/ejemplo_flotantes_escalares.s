.data
f: .float 1.0, 2.0, 3.0, 4.0, 5.0
g: .double 3.1415
str1: .asciz "%f\n"
str2: .asciz "%f %f %f\n"


.text
.global main
main:
	pushq %rbp
	
	movl $0x40000000, %eax
	movq %rax, %xmm0
	leaq str1, %rdi         # Primer argumento
	cvtss2sd %xmm0, %xmm0   # Segundo argumento
	movl $1, %eax           # Cantidad de argumentos vectoriales
	call printf
	
	leaq str2, %rdi         # Primer argumento
	movss f, %xmm0
	cvtss2sd %xmm0, %xmm0   # Segundo argumento 
	movss f+4, %xmm1
	cvtss2sd %xmm1, %xmm1   # Tercer argumento 
	movsd g, %xmm2
	movl $3, %eax           # Cantidad de argumentos vectoriales
	call printf
	
	xor	%eax, %eax
	popq %rbp
	ret