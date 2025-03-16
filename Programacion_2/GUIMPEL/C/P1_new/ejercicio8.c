// Ejercicio 8. Simplificar la siguiente selección de forma que sean necesarias menos comparaciones.
// if (Edad > 64) printf ("Seguridad Social");
// if (Edad < 18) printf ("Exento");
// if ((Edad >= 18) && (Edad < 65)) printf ("Imposible");

#include <stdio.h>

void edades_rango(int edad){
    if(edad > 64){
        printf ("Seguridad Social");}
    else if(edad<18){
        printf("Exento");
    }else{
        printf("Imposible");}
}



int main(){
    int nro;

    printf("Ingrese la edad: \n");
    scanf("%d",&nro);

    edades_rango(nro);

    return 0;
}