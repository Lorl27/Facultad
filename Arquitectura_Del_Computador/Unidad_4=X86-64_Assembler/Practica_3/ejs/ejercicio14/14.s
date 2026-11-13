# 14) Realizar un programa en Assembler x86-64 que sume una cantidad variable de argumentos
# de entrada elevados al cuadrado y muestre el resultado por pantalla: S = a21 + a22 + · · · + a2n .
# Además, debe imprimir la cantidad de argumentos ingresados (n). Por ejemplo, si se ejecuta de
# la siguiente manera:
# ./suma 1 2 3 4
# debe imprimir  "Cantidad de argumentos ingresados: 4. La suma es 30."
# Por el contrario, si no se ingresan argumentos debe imprimir el mensaje
# "Ingrese al menos un argumento"
# Ayuda: Se puede usar la función int atoi(const char *str) que devuelve el argumento de
# entrada de tipo cadena de caracteres convertido en un valor tipo entero

.data
msg_no_args: .asciz "Ingrese al menos un argumento\n"
msg_result:  .asciz "Cantidad de argumentos ingresados: %d. La suma es %d.\n"

.text
.global main

main:
    # -------------------------------------------------------------
    # 1. Prólogo y preservación de registros Callee-Saved
    # -------------------------------------------------------------
    pushq %rbp
    movq %rsp, %rbp

    # Apilamos 4 registros callee-saved (4 * 8 = 32 bytes)
    # Esto mantiene %rsp perfectamente alineado a 16 bytes.
    pushq %rbx            # Acumulador de la suma
    pushq %r12            # Almacena argc
    pushq %r13            # Almacena argv
    pushq %r14            # Índice de iteración (i)

    # -------------------------------------------------------------
    # 2. Validación de argumentos (argc > 1)
    # -------------------------------------------------------------
    cmpl $1, %edi
    jle .Lno_args         # Si argc <= 1, no se ingresaron argumentos

    movl %edi, %r12d      # Guardamos argc en %r12d
    movq %rsi, %r13       # Guardamos el puntero argv en %r13

    xorl %ebx, %ebx       # ebx = 0 (suma de cuadrados)
    movl $1, %r14d        # r14d = 1 (empezamos en argv[1])

    # -------------------------------------------------------------
    # 3. Bucle para procesar cada argumento
    # -------------------------------------------------------------
.Lloop:
    cmpl %r12d, %r14d     # ¿i == argc?
    jge .Lprint_result    # Si ya procesamos todos, vamos a imprimir

    # Cargar el puntero argv[i]: dirección base + (i * 8 bytes)
    movq (%r13, %r14, 8), %rdi

    # Convertir cadena a entero: eax = atoi(argv[i])
    call atoi

    # Elevar al cuadrado: eax = eax * eax
    imull %eax, %eax

    # Acumular en la suma: ebx += eax
    addl %eax, %ebx

    incq %r14             # i++
    jmp .Lloop

    # -------------------------------------------------------------
    # 4. Imprimir Resultado
    # -------------------------------------------------------------
.Lprint_result:
    # n = argc - 1
    movl %r12d, %esi
    decl %esi             # %esi = n (cantidad de argumentos)
    movl %ebx, %edx       # %edx = suma acumulada

    leaq msg_result(%rip), %rdi # %rdi = cadena de formato
    xorl %eax, %eax       # 0 argumentos flotantes en %xmm
    call printf
    jmp .Lepilogue

    # -------------------------------------------------------------
    # 5. Caso Sin Argumentos
    # -------------------------------------------------------------
.Lno_args:
    leaq msg_no_args(%rip), %rdi
    xorl %eax, %eax
    call printf

    # -------------------------------------------------------------
    # 6. Epílogo y Restauración
    # -------------------------------------------------------------
.Lepilogue:
    xorl %eax, %eax       # Valor de retorno 0 desde main

    popq %r14
    popq %r13
    popq %r12
    popq %rbx
    popq %rbp
    ret