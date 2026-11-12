.text
.global main

main:
    # 1. Prólogo estándar
    pushq %rbp
    movq %rsp, %rbp

    # 2. Preservar los registros callee-saved que vas a usar
    pushq %rbx            #  %rbx se guarda en -8(%rbp)
    # pushq %r12            # Si también vas a usar %r12, lo guardás acá
    # si hacemos llamada a call :
    subq $8, %rsp       # Padding manual de 8 bytes para restaurar alineación a 16
    # -------------------------------------------------------------
    # Cuerpo de la función (acá podés usar %rbx / %ebx libremente)
    # -------------------------------------------------------------
    movl $0xAA, %ebx      # Modificás %ebx sin miedo a romper la convención
    shll $24, %ebx

    # --- Variables Locales ---
    movl $42, -16(%rbp) # Tu 1.ª variable local (int) va en -16(%rbp)

    # 3. Epílogo: Restaurar en orden INVERSO (LIFO)
    # popq %r12             # Primero se restaura el último que se apiló (%r12)
    addq $8, %rsp       # Liberás el padding
    popq %rbx             # Después se restaura %rbx

    # Restaurar marco de pila y retornar
    movq %rbp, %rsp
    popq %rbp
    ret