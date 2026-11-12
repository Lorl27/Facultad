# 10000000 00000000 00000000 00000000 == 1 <<31

.data
.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl $1 , %eax
    shll $31,%eax

    movq %rbp, %rsp
    popq %rbp
    ret