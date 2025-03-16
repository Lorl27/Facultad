//? 1. Switch
// Ejercicio 1: Escriba un programa que pida por teclado el resultado obtenido al lanzar un dado de seis caras y que muestre por pantalla el número en letras de la cara opuesta al resultado obtenido. 
// En caso que el valor ingresado no sea válido para las caras de un dado, se debe mostrar el mensaje: "Número incorrecto"

#include <stdio.h>

int calcular_op(int dado){
    switch (dado)
    {
    case  1:
        return 6;
        break;
    case  2:
        return 5;
        break;
    case  3:
        return 4;
        break;
    case  4:
        return 3;
        break;
    case  5:
        return 2;
        break;
    case  6:
        return 1;
        break;
    default:
        return -1;
        break;
    }
}


int main(){
    int nro,result;
    printf("Ingrese un nro del dado: \n");
    scanf("%d",&nro);
    
    result=calcular_op(nro);
    if(result<0){
        printf("Número incorrecto.");
        return 1;
    }
    printf("El opuesto de %d en el dado, es: %d",nro,result);

    return 0;
}