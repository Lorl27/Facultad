//g)
#include <stdio.h>

int main() {
    char textoA [30] = "Agarrate Catalina";
    char textoB [30] = "El Cuarteto de Nos";
    char* p = textoA;
    char* q = textoB;   //punteros a las cadenas 
    printf("textoA: %s\ntextoB: %s\n", textoA , textoB);  //textoA - textoB
    while(*p++ = *q++);  // igualamos cada valor del p1er puntero al sgundo (copia)
    printf("while (*p++ = *q++);\n");
    printf("textoA: %s\ntextoB: %s\n", textoA , textoB);  // textoA - textoA
    return 0;
}