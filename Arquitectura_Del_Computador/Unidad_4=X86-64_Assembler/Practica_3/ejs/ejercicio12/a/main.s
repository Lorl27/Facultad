# 12) Dadas la siguiente declaración de variables:
# a)
# Implementar un programa en Assembler x86-64 para sumar el arreglo de números
# mostrado en la declaración de variables.


.data
list: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
length: .byte 10

.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp

    movzbq length, %rcx       # %rcx = 10 (contador de iteraciones)
    xorq %rbx, %rbx           # %rbx = 0 (índice i)
    xorl %eax, %eax           # %eax = 0 (acumulador de la suma)

    loop_suma:
        addl list(,%rbx,4), %eax  # Suma list[i] de 32 bits a %eax
        incq %rbx                 # i++
        loop loop_suma

    # Al finalizar, %eax contiene la suma (550)
    movq %rbp, %rsp
    popq %rbp
    ret