// 10. Analice el programa dado a continuaci ́on ¿Cu ́al es el resultado? ¿Hay errores en el manejo de
// memoria? ¿C ́omo solucionar ́ıa estos errores?

#include <stdio.h>
#include <stdlib.h>

char* copiar_cadena(char* cad , int longitud){
    char* a = malloc(sizeof(char) * longitud);
    a = cad;
    return a;   // acá está el error - pisamos la memoria dinámica reservada. (Se genera memory leak, ya que la memoria reservada con malloc nunca se libera.)
}

int main(){
    char a[10] = "hola";
    char* b = copiar_cadena(a, 10);             //ahora tienen la == dir de memoria.
    printf("%s %s\n", a, b);    //hola hola
    b[0] = 's';
    printf("%s %s\n", a, b);  //sola sola
    return 0;
}

//* Se solucionaría con strcopy.