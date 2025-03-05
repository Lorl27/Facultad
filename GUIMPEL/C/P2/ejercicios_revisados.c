// // Revisión de ejercicios más "complicados":
// // 7-13-14-21


//SECTION - EJERCICIO 7:
// Mediante una única instrucción for y un printf genere la siguiente salida. 
//Emplee variables para la cadena de texto, un entero y un char:
// b 5 T   ---
// bu 4 s
// buc 3 R
// bucl 2 q
// bucle 1 P

#include <stdio.h>

int ej7(){
    char palabra[]="bucle";
    char letras[]="TsRqP";;
    for(int x=5;x>0;x--){
        palabra[x]='\0';
        printf("%s %d %c \n\n", palabra, x, letras[5-x]);
    }
}


//!SECTION

//SECTION - EJERCICIO 13:
// Escriba un programa que lea un entero n entre 5 y 100 y luego solicite al usuario el ingreso de n enteros, los guarde a todos en un arreglo, y finalmente determine si la suma de los elementos del arreglo es mayor a 30.
// Si el usuario ingresa un número n menor a 5 o mayor a 100, entonces se deberá imprimir un mensaje de Error y el ingreso del arreglo y el análisis de su contenido no se realizará.

int ej13(){
    int n, array[101],suma=0;
    printf("Ingrese un nro entre 5 y 100: \n");
    scanf("%d",&n);
    if(n<5 || n>100){ 
        printf("ERROR. Nro fuera del rango!\n\n");
        return 1;
    }

    for(int x=0;x<n;x++){
        int nro=0;
        printf("Ingrese el elemento nro %d del array:", x+1);
        scanf("%d",&nro);
        array[x]=nro;
        suma+=nro;
    }

    if(suma>30){
        printf("Los arreglos suman 30!\n\n");
    
    } else{
        printf("No suman 30 :(  \n\n");
    }

    return 0;

}

//!SECTION


//  SECTION - EJERCICIO 14:
// Escriba un programa que lea enteros hasta que se ingrese un número negativo, y posteriormente, imprimir qué valor entre 0 y 99 fue el máximo

int ej14(){
    int entero=0,max=0;
    while(entero>=0){
        printf("Ingrese un nro, negativo para terminar.\n");
        scanf("%d",&entero);
        if(entero>max){
            max=entero;
        }
    }

    printf("El nro max fue: %d", max);
    return 0;
}

//!SECTION

// // -



int main(){
    
    ej7();
    ej13();
    ej14();

    return 0;
}