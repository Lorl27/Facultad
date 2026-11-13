# b) Actualice el programa de la pregunta anterior para encontrar el máximo, el mı́nimo y
# el promedio del arreglo de números.
# c) Imprimir los resultados de los ı́tems anteriores por pantalla.


.data
list: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
length: .byte 10
fmt: .asciz "Suma: %d\nMaximo: %d\nMinimo: %d\nPromedio: %d\n"

.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $8, %rsp             # Alineación de la pila a 16 bytes previa al call

    # Inicialización con el primer elemento list[0] (10)
    movl list, %r8d           # %r8d = Acumulador de Suma
    movl list, %r9d           # %r9d = Máximo actual
    movl list, %r10d          # %r10d = Mínimo actual

    movq $1, %rbx             # Índice i = 1
    movzbq length, %rcx       # Cantidad total de elementos = 10
    decq %rcx                 # Quedan 9 elementos por iterar

    loop_stats:
        movl list(,%rbx,4), %eax  # %eax = elemento actual list[i]

        # 1. Acumular Suma
        addl %eax, %r8d

        # 2. Evaluar Máximo
        cmpl %r9d, %eax           # Compara list[i] - max
        jle check_min
        movl %eax, %r9d           # Si list[i] > max, actualiza max

    check_min:
        # 3. Evaluar Mínimo
        cmpl %r10d, %eax          # Compara list[i] - min
        jge next_elem
        movl %eax, %r10d          # Si list[i] < min, actualiza min

    next_elem:
        incq %rbx                 # i++
        loop loop_stats

    # 4. Cálculo del Promedio (Suma / length)
    movl %r8d, %eax           # Carga la suma en %eax
    cltd                      # Extiende el signo de %eax a %edx:%eax
    movzbq length, %r11       # Divisor (10)
    idivl %r11d               # %eax = Suma / 10 (Promedio)

    # 5. Pasaje de parámetros a printf (System V ABI)
    leaq fmt, %rdi            # Arg 1: Cadena de formato
    movl %r8d, %esi           # Arg 2: Suma (550)
    movl %r9d, %edx           # Arg 3: Máximo (100)
    movl %r10d, %ecx          # Arg 4: Mínimo (10)
    movl %eax, %r8d           # Arg 5: Promedio (55)
    xorl %eax, %eax           # 0 argumentos en registros flotantes

    call printf

    addq $8, %rsp
    movq %rbp, %rsp
    popq %rbp
    ret