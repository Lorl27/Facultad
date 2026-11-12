
.text
.global main

funcion:
    incq %rdi               # Incrementa el argumento
    movq %rdi, %rax         # Valor de retorno

    # popq %rbx               # Recupera dirección de retorno
    # jmp *%rbx               # Retorna al llamador
    ret

main:
    movq $1, %rdi           # Argumento de la función

    # pushq $direccion_retorno # Apila dirección de retorno
    # jmp funcion             # Salta a la función
    call funcion

direccion_retorno:
    xorl %eax, %eax
    ret