//12: Para cada uno de los programas que se listan a continuaci ́on, elija la salida que supone
// que ocurrir ́a al ejecutarlo, luego compruebe si estaba en lo cierto. 
//¿Por qu ́e se obtuvo cada resultado?



#include <stdio.h>
#include <stdlib.h>

char* copiar_cadena(char* cad , int longitud){
    char* a = malloc(sizeof(char) * longitud);
    a = cad;
    return a;
}

int main(){
    char a[10] = "hola";
    char* b = copiar_cadena(a, 10);  //el puntero "b" apunta a  "a" ya que la funcion pierde la referenica al espacio reservado
    printf(" %s %s\n", a, b); // "hola" "hola"
    b[0] ='s' ; //a[0] y b[0] apuntan al mismo lugar - cambias 1, se cambia el otro
    printf(" %s %s\n", a, b); //"sola" "sola"
}

// Resultado:
// a.  hola hola
//     hola hola

// b. hola ∗basura∗
//    hola ∗basura∗

// c. Segmentation fault

// d. hola hola  
//    hola sola

// e. hola hola  <--
//    sola sola

// f. Ninguna de las anteriores