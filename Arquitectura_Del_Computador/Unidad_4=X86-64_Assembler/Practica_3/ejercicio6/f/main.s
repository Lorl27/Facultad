# 11111111 11111111 11111110 11111111 == -1 & (~(1 << 8))

.data
.text
.global main
main:
    pushq %rbp
    movq %rsp, %rbp

    movl $1, %eax
    shll $8, %eax

    notl %eax

    andl $-1 , %eax

    movq %rbp, %rsp
    popq %rbp
    ret 