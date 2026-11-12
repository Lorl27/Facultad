.text
.global suma
suma:
    # Prólogo
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    # Cuerpo de la función
    movl %edi, -4(%rbp)
    movl %esi, -8(%rbp)
    movl %edx, -12(%rbp)
    movl -4(%rbp), %edx
    movl -8(%rbp), %eax
    addl %edx, %eax
    movl -12(%rbp), %edx
    addl %edx, %eax
    # Epílogo
    movq %rbp, %rsp
    popq %rbp
    ret