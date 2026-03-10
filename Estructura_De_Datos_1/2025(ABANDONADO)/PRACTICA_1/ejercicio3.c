// 3. Considere arreglos de enteros definidos a trav ́es de una estructura que lleve registro de la capacidad:

typedef struct{
    int* direccion;
    int capacidad;
} ArregloEnteros;

#include <stdio.h>
#include <stdlib.h>

// Implemente las operaciones b ́asicas:
// a) ArregloEnteros* arreglo_enteros_crear(int capacidad);
ArregloEnteros* arreglo_enteros_crear(int capacidad){
    ArregloEnteros *array=malloc(sizeof(ArregloEnteros));
    if(array==NULL){
        printf("Fallo asignacion memoria.");
        return NULL;
    }

    array->capacidad=capacidad;
    array->direccion=malloc(sizeof(int)*capacidad);
    if(array->direccion==NULL){
        printf("fallo.");
        free(array);
        return NULL;
    }

    return array;
}
// b) void arreglo_enteros_destruir(ArregloEnteros* arreglo);
void arreglo_enteros_destruir(ArregloEnteros* arreglo){
    if(arreglo!=NULL){
        free(arreglo->direccion);
        free(arreglo);
    }
}
// c) int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos);
int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos){
    if(arreglo==NULL || pos<0 || pos>=arreglo->capacidad){
        return -1;
    }
    return arreglo->direccion[pos];
}

// d) void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato);
void arreglo_enteros_escribir(ArregloEnteros *arreglo, int pos, int dato){
    if(arreglo==NULL || pos<0 || pos>=arreglo->capacidad){
        exit(EXIT_FAILURE);
    }

    arreglo->direccion[pos]=dato;
}

// e) int arreglo_enteros_capacidad(ArregloEnteros* arreglo);
int arreglo_enteros_capacidad(ArregloEnteros *arreglo){
    if(arreglo==NULL){
        exit(EXIT_FAILURE);
    }

    return arreglo->capacidad;
}
// f) void arreglo_enteros_imprimir(ArregloEnteros* arreglo);
void arreglo_enteros_imprimir(ArregloEnteros *arreglo){
    if(arreglo==NULL){
        exit(EXIT_FAILURE);
    }

    // for(int x=0;x<arreglo->capacidad;x++){
    //     printf("[%d]",arreglo->direccion[x]);
    // }
    printf("[");
    for(int x=0;x<arreglo->capacidad;x++){
        printf("%d",arreglo->direccion[x]);
        if(x<arreglo->capacidad -1){
            printf(", ");
        }
    }
    printf("] \n");
}

// g) Si midi ́eramos el tiempo contando la cantidad de operaciones, como hicimos en el ejercicio 2.g),
// ¿cu ́al de ellas tardar ́ıa m ́as? ¿Para cu ́al de ellas su tiempo depende de la longitud del arreglo?

//* Para mí, tardaría más la de imprimir arreglos ya que recorre todo el array y jsutamente depende de su longitud. [es O(n)]


int main() {
    ArregloEnteros* array = arreglo_enteros_crear(5);

    int cap=arreglo_enteros_capacidad(array);
    printf("La capacidad de mi array es de: %d \n",cap);

    for (int x=0; x<cap;x++) {
        arreglo_enteros_escribir(array,x, x*10);
    }

    printf("Mi arreglo es:\t");
    arreglo_enteros_imprimir(array);

    printf("En la posición 3, se encuentra: %d\n", arreglo_enteros_leer(array, 3));

    arreglo_enteros_destruir(array);

    return 0;
}