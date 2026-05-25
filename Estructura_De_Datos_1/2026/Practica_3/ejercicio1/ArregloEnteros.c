#include <stdio.h>
#include <stdlib.h>
#include "ArregloEnteros.h"

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

void arreglo_enteros_ajustar(ArregloEnteros *arreglo, int capacidad)
{
    if (arreglo != NULL && capacidad > 0)
    {
        int *nueva_direccion = realloc(arreglo->direccion, sizeof(int) * capacidad);
        if (nueva_direccion != NULL)
        {
            arreglo->direccion = nueva_direccion;
            arreglo->capacidad = capacidad;
        }
    }
}

void arreglo_enteros_insertar(ArregloEnteros *arreglo, int pos, int dato)
{
    if (arreglo != NULL && pos >= 0 && pos <= arreglo->capacidad)
    {
        arreglo_enteros_ajustar(arreglo, arreglo->capacidad + 1);
        //  Mudanza de atrás para adelante (d a i)
        // Empezamos en la ÚLTIMA posición disponible (capacidad - 1)
        // Y retrocedemos hasta llegar a la posición donde queremos insertar
        for (int i = arreglo->capacidad - 1; i > pos; i--)
        {
            arreglo->direccion[i] = arreglo->direccion[i - 1]; // Movemos a la derecha
        }
        arreglo->direccion[pos] = dato;
    }
}

void arreglo_enteros_eliminar(ArregloEnteros *arreglo, int pos)
{
    if (arreglo != NULL && pos >= 0 && pos < arreglo->capacidad)
    {

        /// LA MUDANZA (De izquierda a derecha)
        // Nos paramos en el hueco que queremos tapar (pos)
        // Y traemos al vecino de la derecha (x + 1) hacia nosotros (x)
        for (int x = pos; x < arreglo->capacidad - 1; x++)
        {
            arreglo->direccion[x] = arreglo->direccion[x + 1];
        }

        arreglo_enteros_ajustar(arreglo, arreglo->capacidad - 1);
    }
}

void arreglo_enteros_imprimir(ArregloEnteros *arreglo)
{
    if (arreglo == NULL)
        return;
    printf("[ ");
    for (int i = 0; i < arreglo->capacidad; i++)
    {
        printf("%d ", arreglo->direccion[i]);
    }
    printf("]\n");
}