.data
str: .asciz "%d %f\n"
a: .long 45
f: .double 3.14

.text
.global main
main:
    pushq %rbp           # Alineamos la pila a 16 bytes
    leaq  str, %rdi      # Le pasamos la direc. de la cadena de formato 
    movl a, %esi         # Le pasamos el segundo argumento
    movsd f, %xmm0       # le pasamos el tercer argumento
    movb $1, %al         # Cantidad de argumentos de punto flotante
    call printf          # Llamamos a la función printf
    popq %rbp            # Desapilamos para preservar el valor de rsp
    xorl %eax, %eax      # Retornamos cero
    ret