fmt_f: .asciz "f) Valor de i: 0x%lx\n"
fmt_g: .asciz "g) Dirección de i: %p\n"
# -------------------------------------------------------------
    # f) Imprimir el valor de i
    # -------------------------------------------------------------
    movq $fmt_f, %rdi
    movq i, %rsi                # Carga el valor contenido en 'i' (0xDEADBEEF)
    xorq %rax, %rax
    call printf

    # -------------------------------------------------------------
    # g) Imprimir la dirección de i
    # -------------------------------------------------------------
    movq $fmt_g, %rdi
    movq $i, %rsi               # Carga la dirección de memoria de la etiqueta 'i' (&i)
    xorq %rax, %rax
    call printf