// 18) Escriba en lenguaje C un programa que tome la entrada est´andar,
//  la codifique e imprima el resultado en salida est´andar.
// La codificaci´on deber´a ser hecha car´acter a car´acter,
//  utilizando el operador XOR y un c´odigo que se pase al programa como
//  argumento de l´ınea de comando.
// El c´odigo adicional para el operador XOR tambi´en se debe pasar 
// como argumento de l´ınea de comandos al programa.
//  Es decir, suponiendo que el ejecutable se llame prog, la
// l´ınea de comando para ejecutar el programa tendr´ıa el formato:
// $ ./prog <c´odigo> <cadena a codificar>

// Por ejemplo, se podr´ıa hacer:
// $ ./prog 12 Mensaje
// para codificar la cadena “Mensaje” con el c´odigo 12.

//  Pruebe el programa codificando con diferentes c´odigos, por ejemplo,
//  utilizando el c´odigo-98.
// ¿Qu´e modificaciones se tendr´ıan que hacer al programa para que 
// decodifique? ¿Se gana algo codificando m´as de una vez?

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc!=3) {
        printf("Error. formato esperado: ./Ej18 <codigo> <cadena a codificar>\n");
        return 1;
    }

    long codigo = strtol(argv[1], NULL, 10);

    for(int x=0;*argv[2][x]!='\0';x++){
        *argv[2][x]^=codigo;
    }

    printf("Resultado encriptado: %s\n", argv[2]);

    return 0;
}

/* Para decodificar, tendriamos que simplemente, aplicarle el XOR a la cadena codigicada con el
codigo codificador.

No,  el mensaje estaria n-veces encriptado pero por prop. distributiva es lo mismo desencriptarlo n veces que 1 vez.
*/