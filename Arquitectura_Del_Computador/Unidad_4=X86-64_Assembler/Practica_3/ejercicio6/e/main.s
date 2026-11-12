# 00000000 00000000 00000101 00000000 == 5 << 8

.data
.text
.global main

main:
    pushq %rbp
    movq %rsp , %rbp

    movl $5, %eax
    shll $8, %eax

    movq %rbp, %rsp
    popq %rbp
    ret 