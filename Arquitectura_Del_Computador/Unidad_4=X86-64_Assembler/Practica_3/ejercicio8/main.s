.data
.bss
.text
.global main

main:   
    movl $-1, %eax # Solo para este tama~no el mov pone en 0 la parte alta del registro.
    movl $2, %ecx
    imull %ecx
    # completar para que el resultado correcto como signed quede en rax
    # se  guarda en edx:eax --> lo convertimos
    cltq

    # ---------------
    xorq %rax, %rax  # pone en 0
    movw $-1, %ax
    movw $2, %cx
    mulw %cx
    # completar para que el resultado correcto como unsigned int quede en  eax
    # se guarda en dx:ax

    movl $0, %eax # limpieza
    movzwl $ax,  $eax
    movzwl $dx, $edx  # extiendo cmpletando con 0
    shll $16 , $edx  # desplao 16 a la izq
    orl $edx, $eax   # los combinos

    ret