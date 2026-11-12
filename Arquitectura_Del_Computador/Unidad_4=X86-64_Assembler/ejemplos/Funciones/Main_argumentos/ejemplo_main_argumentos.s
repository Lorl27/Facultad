.data
str_1: .asciz "Cantidad de argumentos: %d\n"
str_2: .asciz "Primer argumento: %s\n"

.text
.global main
main:
prologo:
        pushq %rbp              # Salvamos el registro rbp
        movq %rsp, %rbp         # Usamos el registro rbp como puntero a la base del pila
        subq $16, %rsp          # Reservamos espacio en la pila
        
        movq %rdi, -8(%rbp)     # Guardamos el registro rdi en la pila
        movq %rsi, -16(%rbp)    # Guardamos el registro rsi en la pila
imprime_cantidad:
        movq -8(%rbp), %rsi     # rsi es el segundo argumento para llamar a printf
        movq $str_1, %rdi       # rdi es el primer argumento para llamar a printf
        xorq %rax, %rax         # La cantidad de argumentos de tipo vectorial es cero
        call printf             # Llamamos a printf para imprimir el primer mensaje
        
        movq -16(%rbp), %rbx    # Ahora en rbx tenemos la dirección del arreglo de punteros
        movq -8(%rbp), %rcx     # Inicializamos el iterador
        movq $0, %r12           # Inicializamos el índice
imprime:
        movq (%rbx,%r12,8), %rsi    # dirección de argv[1]
        movq $str_2, %rdi           # rdi es el primer argumento para llamar a printf
        xorq %rax, %rax             # La cantidad de argumentos de tipo vectorial es cero
        pushq %rcx                  # Preservamos rcx
        pushq %rax                  # Dummy para alinear
        call printf                 # Volvemos a llamar a printf
        popq %rax                   # Restauramos rax
        popq %rcx                   # Restauramos rcx
        incq %r12                   # Incrementamos el índice
        loop imprime
epilogo:
        movq %rbp, %rsp         # Restauramos el valor de rsp
        pop %rbp                # Restauramos el valor de rbp
        ret                     # Finalmente retornamos
