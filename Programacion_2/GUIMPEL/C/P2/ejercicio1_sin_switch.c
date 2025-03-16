// Ejercicio 1: Escriba un programa que pida por teclado el resultado obtenido al lanzar un dado de seis caras y que muestre por pantalla el número en letras de la cara opuesta al resultado obtenido. 
// En caso que el valor ingresado no sea válido para las caras de un dado, se debe mostrar el mensaje: "Número incorrecto"

#include <stdio.h>

int calcular_op(int dado){
    if(dado<1 || dado>6){
    return -1;
    }

    int op=0;
    for(int x=1;x<=6;x++){
        if(x==dado){
            op=7-x;
            break;  //* op= 6 --> 7-1=6 where x=dado=1 so op of 1 == 6 ;
        }
    }
    return op;
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