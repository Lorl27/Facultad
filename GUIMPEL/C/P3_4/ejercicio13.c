//13: Para cada uno de los programas que se listan a continuaci ́on, elija la salida que supone
// que ocurrir ́a al ejecutarlo, luego compruebe si estaba en lo cierto. 
//¿Por qu ́e se obtuvo cada resultado?


#include <stdio.h>
#include <stdlib.h>


void foo(int* a){
    a = NULL;  //puntero vacío (LOCAL)
}

int main(){
    int a[67];
    a[0] = 123;  //a={123,....,..}
    printf(" %d\n", a[0]);   //123
    foo(a);   //a=NULL pero luego de la función desaparece , ergo: no cambia.
    printf(" %d\n", a[0]);  //123
}

// Resultado:
// a.       123
//          Segmentation fault

// b. 123   <---
//   123

// c.   123
//      ∗basura∗
// d. Segmentation fault

// e. Ninguna de las anteriores