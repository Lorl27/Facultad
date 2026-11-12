.data
str: .asciz "%d %d\n"

.text
.global main
main:
    pushq %rbp          # Prologo
    movq %rsp, %rbp
    subq  $24, %rsp     # Reservar 24 bytes: 16 para locals + 8 para alinear
    
	movq $1, -8(%rbp)   # Variable local 1
	movq $2, -16(%rbp)  # Variable local 2
	
	movq $str, %rdi         # Primer argumento
	movq -8(%rbp), %rsi     # Segundo argumento
	movq -16(%rbp), %rdx    # Tercer argumento
	xor	%eax, %eax          # Cantidad de argumentos de punto flotante
	call printf
	
	leaq -8(%rbp), %rdi     # Primer argumento
	leaq -16(%rbp), %rsi    # Segundo argumento
	
	call swap
	
	movq $str, %rdi         # Primer argumento
	movq -8(%rbp), %rsi     # Segundo argumento
	movq -16(%rbp), %rdx    # Tercer argumento
	xor	%eax, %eax          # Cantidad de argumentos de punto flotante
	call printf
	xor	%eax, %eax
	
	movq %rbp, %rsp     # Epilogo
	popq %rbp
	ret
	
swap:
    pushq %rbp          # Prologo
    movq %rsp, %rbp
    subq $16, %rsp      # Espacio local
    
    movq (%rdi), %rax          
    movq %rax, -8(%rsp)     # valor1 = *rdi         
    movq (%rsi), %rax          
    movq %rax, -16(%rsp)    # valor2 = *rsi
    
    movq -16(%rsp), %rax
    movq %rax, (%rdi)          # *rdi = valor2
    movq -8(%rsp), %rax
    movq %rax, (%rsi)          # *rsi = valor1
    
    movq %rbp, %rsp     # Epilogo
	popq %rbp
    ret