# 19) Dado el siguiente código en lenguaje C:
# #include <stdio.h>
# #include <stdint.h>uint32_t a = 0x7fffffff;
# uint32_t b = 1;
# uint32_t foo1(){
# printf("Ejecutando foo1...\n");
# a = a + (1U << 31);
# printf("0x %x\n", a);
# return a;
# }
# uint32_t foo2(){
# printf("Ejecutando foo2...\n");
# a = a + b;
# printf("0x %x\n", a);
# return a;
# }
# int main(){
# uint32_t r1 = foo1();
# uint32_t r2 = foo2();
# printf("0x %x 0x %x\n", r1, r2);
# return 0;
# }
# a) Indicar lo que se imprime en pantalla al ser ejecutado. Explicar.
# b) Indicar el valor de la variable a y de las banderas CF y OF luego de realizarse cada una de
# las sumas.
# c) Escribir un código equivalente en Assembler x86-64.
# d) Dibujar un esquema que muestre la evolución de la pila.
# Ayuda: Utilizar GDB.

Ejecutando foo1...
0x ffffffff
Ejecutando foo2...
0x 0
0x ffffffff 0x 0