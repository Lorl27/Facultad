.data
a: .quad 45
b: .quad 56

.text
.global main

main:
    movq a, %rdi    # Primer argumento
    movq b, %rsi    # Segundo argumento
    call suma
    
    
    ret
    
suma:
    # Prólogo
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    
    # Cuerpo de la función
    movq $99, -8(%rbp)      # Variable local
    movq %rdi, %rax
    addq %rsi, %rax
    addq -8(%rbp), %rax     # a+b+99
    
    # Epílogo
    movq %rbp, %rsp
    popq %rbp
    ret