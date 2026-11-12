.data
.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp

    rolq $32, %rax

    movq %rbp, %rsp
    popq %rbp
    ret



