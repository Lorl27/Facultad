#include <stdio.h>
#include <stdlib.h>

int main(){
    int edades[15],edadP=0,edadT=0,edad60=0,edad18=0,cant=0;
    int largo=sizeof(edades)/sizeof(edades[0]);
    printf("Ingrese la edad de sus 15 pacientes a continuACION: \n");
    for(int x=0;x<largo;x++){
        printf("ingrese la edad del paciente nro: %d ", x+1);
        scanf("%d",&edades[x]);
        

        edadT+=edades[x];
        cant+=1;

        if (edades[x]>60){
        edad60+=1;}
        if (edades[x]<18){
        edad18+=1;}
    }
    edadP=edadT/cant;
    printf("La edad promedio de los pacientes es %d, \t los mayores de 60 son %d \n  y los menores a 18 son %d \t",edadP,edad60,edad18);

    return 0;
}
