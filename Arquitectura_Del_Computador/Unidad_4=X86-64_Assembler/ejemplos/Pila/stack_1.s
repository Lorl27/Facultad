.text
.global main

main:
    movq $10, %rax
    movq $20, %r10
    
    pushq %rax          # Apila el valor 10
    pushq %r10          # Apila el valor 20
    
    popq %rcx           # Desapila 20 en rcx
    popq %rdx           # Desapila 10 en rdx
    
    xorl %eax, %eax     # Retorna 0
    ret