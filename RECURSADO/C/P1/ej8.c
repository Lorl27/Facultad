// Ejercicio 8. Simplificar la siguiente selección de forma que sean necesarias menos comparaciones.
// if (Edad > 64) printf ("Seguridad Social");
// if (Edad < 18) printf ("Exento");
// if ((Edad >= 18) && (Edad < 65)) printf ("Imposible");

#include <stdio.h>
#include <assert.h>

void ComprobacionEdad(int edad){
    if (edad<18){ printf("Exento");}
    else if(edad <65){printf("Imposible");}
    else{printf("Seguridad Social");}
}

int main(){
    int edad=0;
    printf("Ingrese su edad: \n");
    scanf("%d",&edad);
    ComprobacionEdad(edad);
    return 0;
}