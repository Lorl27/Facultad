//14: Para cada uno de los programas que se listan a continuaci ́on, elija la salida que supone
// que ocurrir ́a al ejecutarlo, luego compruebe si estaba en lo cierto. 
//¿Por qu ́e se obtuvo cada resultado?


#include <stdio.h>
#include <stdlib.h>


int main(){
    char *ptr = "hola mundo"; //En C, se almacena en una var de SOLO LECTURA! (la dir de puntero sera incambiable.)
    ptr [0] = 's';
    printf(" %s\n", ptr);  //SEGMENTATION FAULT
}


// Resultado:
// a. hola mundo
// b. sola mundo
// c. Segmentation fault <--
// d. Ninguna de las anteriores

