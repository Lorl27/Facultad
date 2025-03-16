// Ejercicio 14. Los pacientes con síntomas de una cierta enfermedad son ingresados en el
// hospital si tienen un valor superior a 0.6 en la medición de un determinado índice, y son operados si el 
//valor es superior a 0.9. 
//Escribir un programa en C que lea desde teclado el número
// de pacientes seguido de la edad y el índice de cada paciente, y calcule la edad media de los
// pacientes analizados así como la edad media de los ingresados y la edad media de los operados.

#include <stdio.h>
#include <assert.h>

void analizadorPaciente(int edad, float indicePaciente, int *pacientesOperados, int *pacientesIngresados,int *edadOperados,int *edadIngresados){

    if(indicePaciente>0.9){
        (*pacientesOperados)+=1;
        (*edadOperados)+=edad;
    }else if(indicePaciente>0.6){
        (*pacientesIngresados)+=1;
        (*edadIngresados)+=edad;
    }
}

void test_analizadorPaciente(void) {
    int pacientesIngresados=0, pacientesOperados=0, edadIngresados=0, edadOperados=0;

    // Caso 1: paciente con índice mayor a 0.9
    analizadorPaciente(30, 0.95, &pacientesOperados, &pacientesIngresados,&edadOperados,&edadIngresados);
    assert(pacientesOperados == 1);
    assert(edadOperados == 30);
    assert(pacientesIngresados == 0);
    assert(edadIngresados == 0);

    // Caso 2: paciente con índice entre 0.6 y 0.9
    pacientesIngresados = 0;
    pacientesOperados = 0;
    edadIngresados = 0;
    edadOperados = 0;
    analizadorPaciente(25, 0.75, &pacientesOperados, &pacientesIngresados,&edadOperados,&edadIngresados);
    assert(pacientesOperados == 0);
    assert(edadOperados == 0);
    assert(pacientesIngresados == 1);
    assert(edadIngresados == 25);

    // Caso 3: paciente con índice menor o igual a 0.6
    pacientesIngresados = 0;
    pacientesOperados = 0;
    edadIngresados = 0;
    edadOperados = 0;
    analizadorPaciente(40, 0.5, &pacientesOperados, &pacientesIngresados,&edadOperados,&edadIngresados);
    assert(pacientesOperados == 0);
    assert(edadOperados == 0);
    assert(pacientesIngresados == 0);
    assert(edadIngresados == 0);
}


float edadMedia(int edadTotal, int cantidadPaciente){
    if(cantidadPaciente==0){return 0;}
    return (float)edadTotal/cantidadPaciente;
}

void test_edadMedia(void){
    assert(edadMedia(5,2)==2.5);
    assert(edadMedia(5,1)==5);
    assert(edadMedia(10,0)==0);
}

int main(void){
    test_edadMedia(); //    TEST
    test_analizadorPaciente(); //TEST

    int pacientes=0,edad=0,edadTotal=0,pacientesIngresados=0,pacientesOperados=0,edadIngresados=0,edadOperados=0;
    float indicePaciente=0;

    printf("Ingrese la cantidad de pacientes a analizar:\n");
    scanf("%d",&pacientes);

    for(int x=0;x<pacientes;x++){
        printf("Ingrese la edad del paciente nro %d y su indice",x+1);
        scanf("%d%f",&edad,&indicePaciente);
        edadTotal+=edad;

        analizadorPaciente(edad,indicePaciente,&pacientesOperados,&pacientesIngresados,&edadIngresados,&edadIngresados);
    }
        
        float edadMediaAnalizados= edadMedia(edadTotal,pacientes);
        float edadMediaOperados=edadMedia(edadOperados,pacientesOperados);
        float edadMediaIngresados=edadMedia(edadIngresados,pacientesIngresados);

        printf("Los pacientes analizados en total fueron %d, su edad media es: %.2f",pacientes,edadMediaAnalizados);
        printf("Los pacientes operados en total fueron %d, su edad media es: %.2f",pacientesOperados,edadMediaOperados);
        printf("Los pacientes ingresados en total fueron %d, su edad media es: %.2f",pacientesIngresados,edadMediaIngresados);
        
        return 0;


}