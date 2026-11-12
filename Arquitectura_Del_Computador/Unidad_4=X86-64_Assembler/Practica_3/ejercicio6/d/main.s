# 10101010 00000000 00000000 10101010 == 0xAA << 24 | 0xAA

.data
.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp

    movl $0xAA, %eax
    shll $24, %eax

    movl $0xAA, %ecx
    orl %ecx, %eax


    movq %rbp, %rsp
    popq %rbp
    ret