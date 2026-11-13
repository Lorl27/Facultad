# 11) Implementar un programa en Assembler para invertir un arreglo de bytes de longitud
# conocida usando el stack.
# Ayuda: Esto puede ser logrado “apilando” los valores de a uno en el stack y luego ir “des-
# apilando” en sentido inverso.

.data
a: .byte 1, 2, 3, 4       # Arreglo a invertir
len: .byte 4              # Longitud del arreglo

.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp

    # -------------------------------------------------------------
    # 1. BUCLE DE APILADO (Guardar a[0]...a[len-1] en la pila)
    # -------------------------------------------------------------
    xorq %rbx, %rbx       # %rbx = 0 (índice i para recorrer el arreglo)
    movzbq len, %rcx      # %rcx = len (contador para el loop)

    apilar:
        movzbq a(,%rbx,1), %rax   # Lee 1 byte a[i] y lo extiende a 64 bits en %rax
        pushq %rax                # Apila el registro de 64 bits
        incq %rbx                 # i++
        loop apilar

    # -------------------------------------------------------------
    # 2. BUCLE DE DESAPILADO (Escribir en a[0]...a[len-1] en orden inverso)
    # -------------------------------------------------------------
    xorq %rbx, %rbx       # Reiniciamos el índice i = 0
    movzbq len, %rcx      # Recargamos la longitud en %rcx para el segundo loop

    desapilar:
        popq %rax                 # Desapila el elemento (obtiene primero a[len-1])
        movb %al, a(,%rbx,1)      # Guarda el byte menos significativo (%al) en a[i]
        incq %rbx                 # i++
        loop desapilar

    # -------------------------------------------------------------
    # Epílogo
    # -------------------------------------------------------------
    movq %rbp, %rsp
    popq %rbp
    ret
