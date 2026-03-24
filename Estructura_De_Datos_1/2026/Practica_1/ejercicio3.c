#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* direccion;
    int capacidad;
} ArregloEnteros;

ArregloEnteros * arreglo_enteros_crear(int capacidad){
    ArregloEnteros * arreglo=malloc(sizeof(ArregloEnteros)); //ESTRUCTURA
    if (arreglo == NULL) return NULL;

    arreglo->direccion = malloc(sizeof(int) * capacidad); //ARRAY INTERNO
    if (arreglo->direccion == NULL) {
        free(arreglo); 
        return NULL;
    }

    arreglo->capacidad = capacidad;
    return arreglo;
}

void arreglo_enteros_destruir(ArregloEnteros * arreglo){
    if(arreglo!=NULL){
        free(arreglo->direccion);
        free(arreglo);
    }
}

int arreglo_enteros_leer(ArregloEnteros * arreglo, int pos){
    if(arreglo==NULL || pos < 0 || pos>= arreglo->capacidad) return -1;
    int posicion= arreglo->direccion[pos];
    printf("Arreglo[%d]=%d",pos,posicion);
    return posicion;
}

void arreglo_enteros_escribir(ArregloEnteros * arreglo, int pos, int dato){
    if(arreglo != NULL && pos >= 0 && pos < arreglo->capacidad) {
    arreglo->direccion[pos]=dato;
}
}

int arreglo_enteros_capacidad(ArregloEnteros  * arreglo){
    if (arreglo == NULL) return 0;
    return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros * arreglo){
    if (arreglo == NULL) return;

    for(int x=0;x<arreglo->capacidad;x++){
        printf("%d\n",arreglo->direccion[x]);
    }
}

//G:
/* Cuál de ellas tardaría más?
 La función arreglo_enteros_imprimir.
 
 ¿Para cuál de ellas su tiempo depende de la longitud del arreglo? 
 Solo para arreglo_enteros_imprimir, ya que tiene un bucle for 
 que recorre todo el arreglo. Su complejidad es O(N).
 
 Todas las demás (crear, destruir, leer, escribir, capacidad) son instantáneas.
 Su complejidad es O(1).
*/

int main(){
     // Crear un arreglo de 5 enteros
    ArregloEnteros *arr = arreglo_enteros_crear(5);
    if (arr == NULL) {
        printf("Error al crear el arreglo\n");
        return 1;
    }

    printf("Capacidad del arreglo: %d\n", arreglo_enteros_capacidad(arr));

    // Escribir valores en el arreglo
    for (int i = 0; i < arreglo_enteros_capacidad(arr); i++) {
        arreglo_enteros_escribir(arr, i, i * 10); // guarda 0,10,20,30,40
    }

    // Leer un par de posiciones
    arreglo_enteros_leer(arr, 0);
    printf("\n");
    arreglo_enteros_leer(arr, 3);
    printf("\n");

    // Imprimir todo el arreglo
    printf("Contenido completo del arreglo:\n");
    arreglo_enteros_imprimir(arr);

    // Destruir el arreglo
    arreglo_enteros_destruir(arr);
    return 0;
}