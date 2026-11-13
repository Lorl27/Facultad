.data
format:    .asciz " %ld\n"
i:         .quad 0xDEADBEEF

# Cadenas de formato adicionales
fmt_a:     .asciz "a) Valor de rsp: %p\n"
fmt_b:     .asciz "b) Dirección de format (decimal): %lu\n"
fmt_c:     .asciz "c) Dirección de format (hexadecimal): %p\n"
fmt_d:     .asciz "d) Quad en el tope de la pila (%rsp): 0x%lx\n"
fmt_e:     .asciz "e) Quad en rsp + 8: 0x%lx\n"

.text
.global main
main:
    # Prólogo y alineación de la pila a 16 bytes
    pushq %rbp
    movq %rsp, %rbp
    subq $8, %rsp               # Reserva espacio local y mantiene la pila alineada a 16 bytes

    # Llamada original del ejemplo
    movq $format, %rdi
    movq $1234, %rsi
    xorq %rax, %rax
    call printf

    # -------------------------------------------------------------
    # a) Imprimir el valor del registro rsp
    # -------------------------------------------------------------
    movq $fmt_a, %rdi
    movq %rsp, %rsi             # Copia la dirección contenida en %rsp
    xorq %rax, %rax
    call printf

    # -------------------------------------------------------------
    # b) Imprimir la dirección de la cadena 'format' (en decimal)
    # -------------------------------------------------------------
    movq $fmt_b, %rdi
    movq $format, %rsi          # Pasa la dirección de 'format' como entero
    xorq %rax, %rax
    call printf

    # -------------------------------------------------------------
    # c) Imprimir la dirección de la cadena 'format' (en hexadecimal)
    # -------------------------------------------------------------
    movq $fmt_c, %rdi
    movq $format, %rsi          # Pasa la dirección de 'format' (impreso con %p)
    xorq %rax, %rax
    call printf

    # -------------------------------------------------------------
    # d) Imprimir el quad en el tope de la pila: (%rsp)
    # -------------------------------------------------------------
    movq $fmt_d, %rdi
    movq (%rsp), %rsi           # Desreferencia el valor de 64 bits en el tope de la pila
    xorq %rax, %rax
    call printf

    # -------------------------------------------------------------
    # e) Imprimir el quad ubicado en la dirección rsp + 8
    # -------------------------------------------------------------
    movq $fmt_e, %rdi
    movq 8(%rsp), %rsi          # Desreferencia el valor de 64 bits en la posición %rsp + 8
    xorq %rax, %rax
    call printf

    # Epílogo
    addq $8, %rsp
    movq %rbp, %rsp
    popq %rbp
    ret

    