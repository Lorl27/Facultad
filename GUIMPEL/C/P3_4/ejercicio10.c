//10: Analice los programas dados a continuaci ́on y, escriba todos los errores en el manejo
// de memoria que considere que se est ́an realizando, explique cu ́al ser ́ıa la salida por
// pantalla del programa

#include <stdio.h>

int main() {
    char textoA [30] = "Agarrate Catalina";
    char textoB [30] = "El Cuarteto de Nos";
    char* p= textoA;
    char* q= textoB;
    printf("textoA: %s\ntextoB: %s\n", textoA , textoB);
    while(*p++ = *q++);  //while(...) se ejecuta hasta que *q==´\0´ - basicamente copia todo lo de *p en *q (va parte x parte- se incrmeentan al unísono) ===que strcopy(*p,*q)
    printf("while(*p++ = *q++);\n");
    printf("textoA: %s\ntextoB: %s\n", textoA , textoB); //acá entonces los 2 txt serán iguales!
    return 1;
}