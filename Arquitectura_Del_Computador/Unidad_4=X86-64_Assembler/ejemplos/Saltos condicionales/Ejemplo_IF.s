# Ejemplo IF

.if 0
long n = 5;
long suma = 0;

if(n>0){
    suma += n;
}
.endif


.global main
main:
    movq $5, %rcx
    movq $0, %rax
    
    cmpq $0, %rcx
    jle fin_if
    addq %rcx, %rax
fin_if:
    
    ret