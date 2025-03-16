// Ejercicio 5:  Leer la nota de un alumno (entera) y mostrar un mensaje diciendo si sacó insifuciente (2 a 5), aprobado (6), bueno (7), muy bueno (8), distinguido (9), sobresaliente (10).
// Se debe mostrar un mensaje si la nota es incorrecta. 
//Este programa debe hacerse de dos maneras diferentes con: if secuenciales y, con if-else anidados

#include <stdio.h>

//SECTION - IF SECUENCIAL:
void notas_1(const int nota){

    if(nota>=2&&nota<=5){
        printf("El alumno saco insuficiente. \n");
    }
    if(nota==6){
        printf("El alumno aprobo \n");
    }
    if(nota==7){
        printf("El alumno saco <<bueno>>. \n");
    }
    if(nota==8){
        printf("El alumno saco <<Muy Bueno>>. \n");
    }
    if(nota==9){
        printf("El alumno saco <<Distinguido>>. \n");
    }
    if(nota==10){
        printf("El alumno saco <<Sobresaliente>>. \n");
    }

}
//!SECTION 


//SECTION - IF-ELSE ANIDADO:


void notas_2(const int nota){
    if (nota>=2 && nota<=5) {
        printf("El alumno sacó insuficiente. \n");
    } else if (nota== 6) {
        printf("El alumno aprobó. \n");
    } else if (nota== 7) {
        printf("El alumno sacó <<bueno>>. \n");
    } else if (nota== 8) {
        printf("El alumno sacó <<Muy Bueno>>. \n");
    } else if (nota== 9) {
        printf("El alumno sacó <<Distinguido>>. \n");
    } else {
        printf("El alumno sacó <<Sobresaliente>>. \n");
    }
}

//!SECTION 

int verificar_rango(int nota){
    return nota >= 2 && nota <= 10; //** 1: T , 0:F */
}

int main(){
    int note;
    printf("Ingrese la nota del alumnx: \n");
    scanf("%d",&note);

    if(!verificar_rango(note)){
        printf("Nota FUERA del rango (2,10)");
        return 1;
    }

    notas_1(note);
    printf("--------------------\n");
    notas_2(note);

    return 0;
}