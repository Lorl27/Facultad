# Ejemplo FOR

.if 0
long suma = 0;

for (long i = 1;
     i <= 10; i++) {
    suma += i;
}
.endif


.global main
main:
    movq $0, %rax
    movq $1, %rcx

for_1:
    cmpq $10, %rcx
    jg fin_for
    addq %rcx, %rax
    incq %rcx
    jmp for_1
fin_for:
    
    ret