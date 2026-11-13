# 15) El programa que sigue, funcs, implementa void (*funcs[])() = {f1, f2, f3}. Compléte-
# lo para que la lı́nea con el comentario corresponda a funcs[entero]() de manera que si se
# ingresa un 0 por teclado imprime un cero, si se ingresa un 1 imprime un 1 y si se ingresa un 2
# imprime un dos. Use el código más eficiente.
.data
fmt: .string " %d"
entero: .long -100
funcs: .quad f1
    .quad f2
    .quad f3
.text
f1: movl $0, %esi; movq $fmt, %rdi; call printf; jmp fin
f2: movl $1, %esi; movq $fmt, %rdi; call printf; jmp fin
f3: movl $1, %esi; movq $fmt, %rdi; call printf; jmp fin

.global main

main:
    pushq %rbp
    movq %rsp, %rbp
    # Leemos el entero.
    movq $entero, %rsi
    movq $fmt, %rdi
    xorq %rax, %rax
    call scanf
    xorq %rax, %rax
    # COMPLETE CON DOS INSTRUCCIONES.
    movl entero, %eax
    movq funcs(,%rax,8), %rdx

    jmp * %rdx
    fin:
        movq %rbp, %rsp
        popq %rbp
        ret