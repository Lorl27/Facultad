// 10) Ejecutar el siguiente programa y analizar lo que imprime por pantalla. Conviene
// usar GDB para observar el contenido de las variables.
// Ayuda: Para signed char se usa el modificador %hhd y para unsigned char el mo
// dificador %hhu.
// Repetir usando los modificadores %d y %u en lugar de %hhd y %hhu, respectivamente.

#include <stdio.h>

int main(){
    char a=127; //-128<=a<=127 - a= 0111 1111
    printf("%hhd %hhu\n",a,a); //127 127
    a=++a; //a=10000000 (a=a+1)
    printf("%hhd %hhu\n",a,a); //-128 128
    unsigned char b=128; // b=1000 0000
    printf("%hhd %hhu\n",b,b); //-128 128
    b=++b; // 1000 0001
    printf("%hhd %hhu\n",b,b); //! WARNING: overflow in implicit constant conversion [-Woverflow] -> -127 129
    
    /// --- convertir a signed char y unsigned char usando %d y %u
    char a=127;
    printf("%d %u\n",a,a); //-128 indefinido
    a=++a;
    printf("%d %u\n",a,a); //-127 indefinido
    unsigned char b=128;
    printf("%d %u\n",b,b); //128 indefinido
    b=++b;
    printf("%d %u\n",b,b); //129 indefinido
    
    return 0;
}