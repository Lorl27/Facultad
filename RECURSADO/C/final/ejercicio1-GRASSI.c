#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>

//Própositos de las funciones:
double calcular_promedio(double array[],int tam);
double calcular_alturas(double array[],int tam);
void calculo_de_la_moda(double array[],int tam);

/*
    DISEÑO DE DATOS:

    promedio: double, variable para almacenar el promedio
    suma: double, variable para almacenar las sumas de las alturas

    Signatura: 
    calcular_promedio: double[] int ->double

    Próposito: Calcular el promedio de los elementos del array pasado por párametro. (La dimensión del mismo se daba pasar por párametro.)

    EJEMPLOS:
        sea array1[]={1,2,3,4,6}
        calcular_promedio(array1,5) <= 2+diferencia && calcular_promedio(array1,5)>=2-diferencia;

        sea array2[]={5.2,7.3,8.9,2};
        calcular_promedio(array2,4) <= 5.35+diferencia && calcular_promedio(array2,4)>=5.35-diferencia;

        sea array3[]={0};
        calcular_promedio(array3,1) <= 0.0+diferencia && calcular_promedio(array3,1)>=0.0-diferencia;

*/

double calcular_promedio(double array[],int tam){

    double promedio=0,suma=0;
    
    for(int x=0;x<tam-1;x++){
        suma+=array[x];
    }

    if(suma==0){
        return promedio;
    }

    promedio=(double)suma/tam;

    return promedio;
}

void test_calcular_promedio(void){

    double diferencia=0.0001; //Para poder encerrar en un rango el resultado y hacer un assert más preciso.

    double array1[]={1,2,3,4,6};
    assert(calcular_promedio(array1,5) <= 2+diferencia && calcular_promedio(array1,5)>=2-diferencia);

    double array2[]={5.2,7.3,8.9,2};
    assert(calcular_promedio(array2,4) <= 5.35+diferencia && calcular_promedio(array2,4)>=5.35-diferencia);

    double array3[]={0};
    assert(calcular_promedio(array3,1) <= 0.0+diferencia && calcular_promedio(array3,1)>=0.0-diferencia);
}

/*
    DISEÑO DE DATOS:

    maximo_valor: double, variable para almacenar el valor mayor de todo el array

    Signatura: 
    calcular_alturas: double[] int  ->double

    Próposito: Calcular la altura máxima, del array pasado por parámetro. (La dimensión del mismo se daba pasar por párametro.)

    EJEMPLOS:
        sea array1[]={1,2,3,4,6}
        calcular_alturas(array1,5)==6;

        sea array2[]={5.2,7.3,8.9,2};
        calcular_alturas(array2,4)==9.2;

        sea array3[]={0};
        calcular_alturas(array3,1)==0;

*/

double calcular_alturas(double array[],int tam){

    double maximo_valor=array[0];

    for(int x=0;x<tam;x++){
        if(maximo_valor<array[x]){
            maximo_valor=array[x];
        }
    }

    return maximo_valor;

}

void test_calcular_alturas(void){


    double array1[]={1,2,3,4,6};
    assert(calcular_alturas(array1,5)==6);

    double array2[]={5.2,7.3,8.9,2};
    assert(calcular_alturas(array2,4)==8.9);

    double array3[]={0};
    assert(calcular_alturas(array3,1)==0);

}

/* 
    DISEÑO DE DATOS:

    max_rep: int, indica la cantidad de repeticiones de cada elemento
    frecuencia: int[], indica la frecuencia del elemento

    Signatura:
    calculo_de_la_moda: double[] int -> void

    Proposito: Indica el valor que más se repite y lo catogariza en una Moda.

    EJEMPLOS:
        
        * sea double array1[] = {1, 2, 3, 4, 6, 6, 6};
        calculo_de_la_moda(array1, 7) -> Debería imprimir 6 con frecuencia 3

        * sea double array2[] = {5.2, 7.3, 8.9, 2, 7.3};
        calculo_de_la_moda(array2, 5); -> Debería imprimir 7.3 con frecuencia 2

        * sea double array3[] = {0, 0, 0};
        calculo_de_la_moda(array3, 3); -> Debería imprimir 0 con frecuencia 3

        * sea double array4[] = {1, 2, 3, 1, 2, 3};
        calculo_de_la_moda(array4, 6); -> Debería imprimir 1, 2 y 3 con frecuencia 2 cada uno

*/


void calculo_de_la_moda(double array[],int tam){

    int max_rep=0;
    int frecuencia[tam];

    // Inicializar el array de frecuencias a 0
    for (int x=0;x<tam;x++){
        frecuencia[x] = 0;
    }

    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            if(array[x]==array[y]){
                frecuencia[x]++;
            }
        }

        if(max_rep<array[x]){
            max_rep=array[x];
        }
    }


    // Imprimir todas las modas y su frecuencia
    printf("Las modas y sus frecuencias son:\n");
    for (int i = 0; i < tam; i++) {
        if (frecuencia[i] == max_rep) {
            printf("Valor: %f, Frecuencia: %d\n", array[i], frecuencia[i]);
        }
    }
}

int main(void){

    //TESTS:
    test_calcular_promedio();
    test_calcular_alturas();

    //Inicializamos los valores:
    double prom=0,altura_max=0,moda=0;

    double aAlturas[]={1.95,1.89,1.88,1.86,2.0,2.0,2.0,2.0,2.07,2.09,2.12}; //Historial de las alturas HIdrométricas de la Cuenca del Paraná

    int tam_array=11; // Variable quen almacena el tamaño del array 'aAlturas'

    prom=calcular_promedio(aAlturas,tam_array);

    if(prom==0){
        printf("No hay datos para calcular. \n");
    }else{
        printf("El promedio es: %.2lf\n\n",prom);
    }

    altura_max=calcular_alturas(aAlturas,tam_array);
    printf("La altura máxima de las alturas es: %.2lf\n\n",altura_max);

    //moda=calculo_de_la_moda(aAlturas);

    return 0;

}