.data
a: .byte 0xAA

.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp

    movq $0, %rax
    movb a, %al

    shlq $24, %rax

    movq $0, %rbx
    movb a, %bl

    orq %rbx, %rax

    movq %rbp, %rsp
    popq %rbp
    ret
