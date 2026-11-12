#10000000 00000000 10000000 00000000 (1 << 31) | (1 << 15)

.data
.text
.global main

    main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl $1 , -4(%rbp)
    movl -4(%rbp), %edi
    
    movl $1, %eax
    shll $31, %eax

    shll $15, %edi

    orl %edi, %eax
    

    movq %rbp, %rsp
    popq %rbp
    ret