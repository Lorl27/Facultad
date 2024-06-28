// 1. Switch
// Ejercicio 1. Escriba un programa que pida por teclado el resultado obtenido al lanzar un dado
// de seis caras y que muestre por pantalla el número en letras de la cara opuesta al resultado
// obtenido. En caso que el valor ingresado no sea válido para las caras de un dado, se debe
// mostrar el mensaje: "Número incorrecto".

// caras opuestas: 1->6 ; 2-> 5; 3-> 4; 4->3; 5->2; 6->1

#include <stdio.h>
#include <assert.h>

int caraOp(int dado){
    switch (dado)
    {
    case 1:
        return 6;
    case 2:
        return 5;
    case 3:
        return 4;
    case 4:
        return 3;
    case 5:
        return 2;
    case 6:
        return 1;
    default:
        return -1; // Para indicar error
    }
}

void test_caraOp(void){
    assert(caraOp(1) == 6);
    assert(caraOp(2) == 5);
    assert(caraOp(3) == 4);
    assert(caraOp(4) == 3);
    assert(caraOp(5) == 2);
    assert(caraOp(6) == 1);
    assert(caraOp(0) == -1); // error
    assert(caraOp(7) == -1); // error
}

int main(void){
    test_caraOp(); //TEST

    int numero,resultado=0;
    printf("Ingrese el numero que le ha salido en el dado: \n");
    scanf("%d",&numero);

    resultado=caraOp(numero);

    (resultado!=-1)?printf("El numero opuesto es: %d", resultado):(printf("Número incorrecto... No válido\n"));

    return 0;
}