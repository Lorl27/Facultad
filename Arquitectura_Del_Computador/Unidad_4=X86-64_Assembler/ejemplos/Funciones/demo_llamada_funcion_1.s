.text
.global main

funcion:
    incq %rdi               # Incrementa el argumento
    movq %rdi, %rax         # Valor de retorno

    jmp direccion_retorno   # Retorna a main

main:
    movq $1, %rdi           # Argumento de la función

    jmp funcion             # Salta a la función

direccion_retorno:
    xorl %eax, %eax
    ret
