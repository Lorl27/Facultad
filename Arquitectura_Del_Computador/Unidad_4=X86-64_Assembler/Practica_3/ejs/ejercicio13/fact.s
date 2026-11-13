# 13) La función factorial se puede escribir en lenguaje C con recursión:
# unsigned long fact1(unsigned long x){
# if (x <= 1) {
# return x;
# }
# return x * fact1(x - 1);
# }
# y también con un bucle:
# unsigned long fact2(unsigned long x)
# {
# unsigned long acc = 1;
# for (; x > 1; x--) {
# acc *= x;
# }
# return acc;
# }
# Implemente ambas versiones en ensamblador. Se sugiere empezar por fact2. Acompáñelas
# del siguiente archivo en C para probarlas:
# #include <stdio.h>
# unsigned long fact1(unsigned long);
# unsigned long fact2(unsigned long);
# int main(void){
# unsigned long x;
# scanf(" %lu", &x);
# printf("fact1: %lu\n", fact1(x));
# printf("fact2: %lu\n", fact2(x));
# return 0;
# }
# Deberá entonces mantener dos o más archivos separados: uno para la función main en C y
# uno o más para las funciones en ensamblador. Para generar el binario ejecutable, debe pasar los
# nombres de todos archivos de implementación como argumentos de gcc:
# $ gcc fact.s main.c


.text
.global fact1
.global fact2

# ==============================================================================
# unsigned long fact2(unsigned long x) - Versión Iterativa
# Entrada:  %rdi = x
# Salida:   %rax = resultado (factorial)
# ==============================================================================
fact2:
    movq $1, %rax           # acc = 1 (acumulador)

.Lloop_fact2:
    cmpq $1, %rdi           # Compara x con 1
    jbe .Ldone_fact2        # Si x <= 1, finaliza el bucle
    imulq %rdi, %rax        # acc *= x
    decq %rdi               # x--
    jmp .Lloop_fact2

.Ldone_fact2:
    ret                     # Retorna el acumulador en %rax


# ==============================================================================
# unsigned long fact1(unsigned long x) - Versión Recursiva
# Entrada:  %rdi = x
# Salida:   %rax = resultado (factorial)
# ==============================================================================
fact1:
    cmpq $1, %rdi           # Caso base: ¿x <= 1?
    jbe .Lbase_fact1

    # Caso recursivo (x > 1):
    pushq %rdi              # Preserva el 'x' actual en la pila (-8 bytes).
                            # Nota de alineación: al entrar a la función la pila 
                            # tenía (16n + 8) bytes por la dirección de retorno. 
                            # Al hacer pushq %rdi, %rsp queda perfectamente 
                            # alineado a 16 bytes antes de invocar 'call'.

    decq %rdi               # Prepara el argumento: (x - 1)
    call fact1              # Llamada recursiva: %rax = fact1(x - 1)

    popq %rdi               # Recupera el 'x' original de la pila
    imulq %rdi, %rax        # %rax = x * fact1(x - 1)
    ret                     # Retorna el resultado en %rax

.Lbase_fact1:
    movq %rdi, %rax         # return x (si x <= 1)
    ret