# d) Modificar el ı́tem b) usando instrucciones de movimiento de datos condicionales (familia
# de instrucciones CMOVcc, ver Manual de Intel)loop_stats:
    movl list(,%rbx,4), %eax  # %eax = elemento actual list[i]

    # Acumular Suma
    addl %eax, %r8d

    # Actualizar Máximo de forma condicional sin saltos
    cmpl %r9d, %eax           # Compara list[i] con el máximo actual (%r9d)
    cmovg %eax, %r9d          # Si list[i] > max (%r9d), copia %eax en %r9d

    # Actualizar Mínimo de forma condicional sin saltos
    cmpl %r10d, %eax          # Compara list[i] con el mínimo actual (%r10d)
    cmovl %eax, %r10d         # Si list[i] < min (%r10d), copia %eax en %r10d

    incq %rbx                 # i++
    loop loop_stats