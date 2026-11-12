# Ejemplo FOR (usando la isntrucción específica LOOP)

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
    movq $10, %rcx

bucle:
    addq %rcx, %rax
    loop bucle
    
    ret