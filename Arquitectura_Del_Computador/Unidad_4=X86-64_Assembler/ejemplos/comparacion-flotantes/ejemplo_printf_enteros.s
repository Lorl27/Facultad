.data
.align 16
a: .float 1.0, 2.0, 3.0, 4.0
b: .float 1.0, 2.0, 3.0, 4.0
c: .byte 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
d: .byte 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16

str_flotantes: .asciz "%f %f %f %f\n"
str_enteros: .asciz "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n"

.text
.global main
main:
    pushq %rbp
    movq %rsp, %rbp
    
    movq $a, %rdi                   # rdi apunta a "a"
    movq $b, %rsi                   # rsi apunta a "b"
    movaps (%rdi), %xmm0            # copia 4 floats  en xmm0
    movaps (%rsi), %xmm1            # copia 4 floats  en xmm1
    addps %xmm0, %xmm1              # suma los dos vectores 
    movaps %xmm1, (%rdi)            # guarda el resultado en "a"
    
    leaq str_flotantes, %rdi
    cvtss2sd a, %xmm0
    cvtss2sd a+4, %xmm1
    cvtss2sd a+8, %xmm2
    cvtss2sd a+12, %xmm3
    movb $4, %al
    call printf
    
#------------------------------------------------------------------------------------    
    movq $c, %rdi                   # rdi apunta a "c"
    movq $d, %rsi                   # rsi apunta a "d"
    movaps (%rdi), %xmm0            # copia 16 bytes  en xmm0
    movaps (%rsi), %xmm1            # copia 16 bytes  en xmm1
    paddb %xmm0, %xmm1              # suma los dos vectores 
    movaps %xmm1, (%rsi)            # guarda el resultado en "d"    
    
    leaq str_enteros, %rdi
    movzbl d, %esi
    movzbl d+1, %edx
    movzbl d+2, %ecx
    movzbl d+3, %r8d
    movzbl d+4, %r9d
    movzbl d+15, %r10d
    pushq %r10
    movzbl d+14, %r10d
    pushq %r10
    movzbl d+13, %r10d
    pushq %r10
    movzbl d+12, %r10d
    pushq %r10
    movzbl d+11, %r10d
    pushq %r10
    movzbl d+10, %r10d
    pushq %r10
    movzbl d+9, %r10d
    pushq %r10
    movzbl d+8, %r10d
    pushq %r10
    movzbl d+7, %r10d
    pushq %r10
    movzbl d+6, %r10d
    pushq %r10
    movzbl d+5, %r10d
    pushq %r10
    xorl %eax, %eax
    call printf

    xorl %eax, %eax
    movq %rbp, %rsp
    popq %rbp
    ret