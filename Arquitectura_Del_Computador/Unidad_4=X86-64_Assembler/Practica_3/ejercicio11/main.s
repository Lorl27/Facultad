# 11) Implementar un programa en Assembler para invertir un arreglo de bytes de longitud
# conocida usando el stack.
# Ayuda: Esto puede ser logrado “apilando” los valores de a uno en el stack y luego ir “des-
# apilando” en sentido inverso.

.data
a: .byte 1 2 3 4
len: .byte 4
.text
.bss
.global main

main:
    pushq %rbp
    movq %rsp,%rbp

    xorb %rcx, %rcx
    xorb %rbx, %rbx

    movb len,%cl

    apilar:
        pushb (a,%bx), -1(%rbp,,%bx)
        incb %bx
        loop apilar 

    xorb %rcx, %rcx
    movb len,%cl

    desapilar:
        pushb -1(%rbp,,%bx),%rax
        decb %bx
        popb 1(%rbp,,%bx)
        loop desapilar
    
    movq %rbp,%rsp
    popq %rbp
    ret
