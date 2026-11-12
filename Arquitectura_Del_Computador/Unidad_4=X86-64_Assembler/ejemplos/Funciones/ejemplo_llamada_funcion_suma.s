.data
str: .asciz "%d + %d = %d\n"

.text
.global main
main:
    pushq %rbp          # Prologo de main
    movq %rsp, %rbp
    subq  $16, %rsp     # Reservar 16 bytes para variables locales
    
	movq $1, -8(%rbp)   # Variable local 1 en main
	movq $2, -16(%rbp)  # Variable local 2 en main
	
	movq -8(%rbp), %rdi     # Primer argumento de suma
	movq -16(%rbp), %rsi    # Segundo argumento de suma
	
	call suma
	
	movq $str, %rdi         # Primer argumento de printf
	movq -8(%rbp), %rsi     # Segundo argumento de printf
	movq -16(%rbp), %rdx    # Tercer argumento de printf
	movq %rax, %rcx         # Cuarto argumento de printf
	xor	%eax, %eax          # Cantidad de argumentos de punto flotante
	call printf
	xor	%eax, %eax
	
	movq %rbp, %rsp     # Epilogo de main
	popq %rbp
	ret
	
suma:
    pushq %rbp          # Prologo de suma
    movq %rsp, %rbp
    subq $16, %rsp      # Espacio local
    
    movq %rdi, -8(%rsp)     # Variable local 1 en suma        
    movq %rsi, -16(%rsp)    # Variable local 2 en suma
    
    movq -8(%rsp), %rax
    addq -16(%rsp), %rax
    
    movq %rbp, %rsp     # Epilogo de suma
	popq %rbp
    ret