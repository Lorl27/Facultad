#  11111111 11111111 11111111 00000000 == -1 & (~0xFF)

.data
.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl $0xFF , %eax
    notl %eax

    andl $-1 , %eax

    movq %rbp, %rsp
    popq %rbp
    ret
    