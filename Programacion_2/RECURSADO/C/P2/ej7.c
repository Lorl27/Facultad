// Ejercicio 7. Mediante una única instrucción for y un printf genere la siguiente salida. Emplee
// variables para la cadena de texto, un entero y un char:
// b 5 T
// bu 4 s
// buc 3 R
// bucl 2 q
// bucle 1 P

#include <stdio.h>

int main(void){
    char array[]="bucle";
    int length=5;
    char letra[]="TsRqP";

    //FORMA 1:
    for(int entero = length;entero>=1;entero--){
        printf("%.*s %d %c\n",entero,array,entero,letra[length - entero]);
    }

    printf("FORMA 2: \n");

    //FORMA 2:
    for(int entero = length;entero>=1;entero--){
        for(int x=0;x<entero;x++){
            printf("%c",array[x]);
        }
        
        printf(" %d %c\n",entero,letra[length - entero]);
    }

    printf("FORMA 3: \n");

    //FORMA 3:
    char copia_array[6];
    for(int entero = 0;entero<5;entero++){
        copia_array[entero]=array[entero];
        copia_array[entero+1]='\0';
        printf("%s %d %c\n",copia_array,length-entero,letra[entero]);
    }
    return 0;
}