.data
a: .double 50.0
b: .double 30.0

msg_gt:  .asciz "a > b\n"
msg_lt:  .asciz "a < b\n"
msg_eq:  .asciz "a = b\n"
msg_nan: .asciz "Comparacion no ordenada (NaN)\n"

.text
.global main
main:
    pushq %rbp
    movq %rsp, %rbp

# Cargar valores en registros XMM
    movsd a, %xmm0
    movsd b, %xmm1

# Comparar a con b
    ucomisd %xmm1, %xmm0

# Evaluar las banderas
    jp   no_ordenados    # Alguno es NaN
    ja   mayor           # a > b
    jb   menor           # a < b
    je   iguales         # a == b

mayor:
    leaq msg_gt, %rdi
    jmp imprimir

menor:
    leaq msg_lt, %rdi
    jmp imprimir

iguales:
    leaq msg_eq, %rdi
    jmp imprimir

no_ordenados:
    leaq msg_nan, %rdi

imprimir:
    xorl %eax, %eax
    call printf

# Epílogo
    xorl %eax, %eax
    movq %rbp, %rsp
    popq %rbp
    ret