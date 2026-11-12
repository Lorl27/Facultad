# Ejemplo WHILE

.if 0
long i = 1;
long suma = 0;

while (i <= 10) {
    suma += i;
    i++;
}
.endif


.global main
main:
    movq $1, %rcx
    movq $0, %rax

while_1:
    cmpq $10, %rcx
    jg fin_while
    addq %rcx, %rax
    incq %rcx
    jmp while_1
fin_while:
    
    ret