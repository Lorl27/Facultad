.data
t: .double 1.0, 2.0
str: .asciz "Valor original: %f, valor convertido: %f\n"

.text
.global main
main: 
    pushq %rbp
 
    movsd t, %xmm0
    call convert
    movsd %xmm0, %xmm1
    movsd t, %xmm0
    leaq str, %rdi
    movb $2, %al
    call printf
    
    movsd t+8, %xmm0
    call convert
    movsd %xmm0, %xmm1
    movsd t, %xmm0
    leaq str, %rdi
    movb $2, %al
    call printf

    popq %rbp
    ret
