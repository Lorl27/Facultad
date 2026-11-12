.data
i: .space 8

.text
.global main
main:
    # Prólogo
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp              # Se reserva espacio en la pila    
    
    # Cuerpo de la función main
    movq $40, -8(%rbp)          # Variable local
    movq $45, -16(%rbp)         # Variable local
    movq -8(%rbp), %rdi         # Primer argumento en rdi
    movq -16(%rbp), %rsi        # Segundo argumento en rsi
    call suma                   # Guarda la dirección de retorno en pila y salta a "suma"
    movq %rax, i                # Aquí rax contiene el resultado (85)
    
    # Epílogo
    movq %rbp, %rsp
    popq %rbp
    ret

suma:
    # Prólogo
    pushq %rbp                  # Preserva el registro rbp
    movq %rsp, %rbp             # rbp "apunta" al inicio de la pila
    
    # Cuerpo de la función suma
    movq %rdi, -8(%rbp)         # Variable local
    movq %rsi, -16(%rbp)        # Variable local
    movq -8(%rbp), %rax     
    addq -16(%rbp), %rax        # Aquí el resultado ya está en rax
    movq %rax, -24(%rbp)        # Variable local
    
    # Epílogo
    movq %rbp, %rsp         # rsp "apunta" nuevamente al inicio de la pila
    popq %rbp               # Se restaura el registro rbp
    ret                     # Retorna de la función "suma" a "main"