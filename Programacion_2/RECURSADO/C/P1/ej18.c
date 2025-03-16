// Ejercicio 18. La fecha del domingo de Pascua corresponde al primer domingo después de
// la primera luna llena que sigue al equinoccio de primavera. Dado un año, los cálculos que
// permiten conocer esta fecha son:
// A = año
// B = año
// C = año
// D = (19 * A + 24)
// E = (2 * B + 4 * C + 6 * D + 5)
// N = (22 + D + E)
// Donde N indica el número del día del mes de marzo (o abril si N es superior a 31) correspondiente al domingo de Pascua. Escribir un programa que lea un año y muestre el día y el mes
// en el que se celebró o se celebrará el domingo de Pascua ese año.Utilizar una función a la que
// se le pase como parámetro el año y retorne el valor de N. El programa principal realiza el resto
// del proceso.

#include <stdio.h>
#include <assert.h>

int domingoPascua(int anio){
    int a,b,c,d,e,n;
    a=b=c=anio;
    d=19*a+24;
    e=2*b+4*c+6*d+5;
    n=22+d+e;
    return n;
}

void test_domingoPascua(void){
    assert(domingoPascua(2022)==417); // 17 de abril
    assert(domingoPascua(2023) == 409); // 9 de abril
    assert(domingoPascua(2024) == 331); // 31 de marzo
}

int main(void){
    //test_domingoPascua(); //TEST

    int anio,resultado=0;

    printf("Ingrese el anio al cual quieras consultar cuando se celebro/ celebrara el Domingo de Pascua: \n");
    scanf("%d",&anio);
    resultado=domingoPascua(anio);

    (resultado>31)?printf("El Domingo de Pascua fue el %d de Abril.\n", (resultado%31)):(printf("El Domingo de Pascua fue el %d de marzo.\n", resultado));

    return 0;
}


//NOTE: anda mal. :(