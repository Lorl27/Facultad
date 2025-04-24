// 3. Considere arreglos de enteros definidos a trav ́es de una estructura que lleve registro de la capacidad:

#include "arregloEnteros.h"

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



// a) void arreglo enteros ajustar(ArregloEnteros* arreglo, int capacidad), que ajuste el
// tama˜no del arreglo. Si la nueva capacidad es menor, el contenido debe ser truncado.

void arreglo_enteros_ajustar(ArregloEnteros *arreglo, int capacidad){
    if(arreglo==NULL || capacidad<=0){
        exit(EXIT_FAILURE);
    }

    int *nueva_dir=realloc(arreglo->direccion,sizeof(int)*capacidad);

    if(nueva_dir==NULL){
        printf("Fallo realloc.");
        exit(EXIT_FAILURE);
    }
    
        arreglo->capacidad=capacidad;
        arreglo->direccion=nueva_dir;

}

// b) void arreglo enteros insertar(ArregloEnteros* arreglo, int pos, int dato), que
// inserte el dato en la posici´on dada, moviendo todos los elementos desde esa posici´on un lugar a la
// derecha (tendr´a que incrementar el tama˜no del arreglo).
void arreglo_enteros_insertar(ArregloEnteros *arreglo, int pos, int dato){
    if (arreglo == NULL || pos < 0 || pos > arreglo->capacidad) {
        exit(EXIT_FAILURE);
    }

    int cap=arreglo->capacidad;

    arreglo_enteros_ajustar(arreglo,cap+1);
    
    //movemos elementos a al derecha , desde el final hasta pos.
    for(int x=cap;x>pos;x--){
        arreglo->direccion[x]=arreglo->direccion[x-1];
    }

    arreglo->direccion[pos]=dato;
}


// c) void arreglo enteros eliminar(ArregloEnteros* arreglo, int pos), que elimine el dato en
// la posici´on dada, moviendo todos los elementos posteriores un lugar a la izquierda (tendr´a que
// reducir el tama˜no del arreglo).
void arreglo_enteros_eliminar(ArregloEnteros *arreglo, int pos){
    if (arreglo == NULL || pos < 0 || pos >= arreglo->capacidad) {
        exit(EXIT_FAILURE);
    }

    for(int x=pos;x<arreglo->capacidad-1;x++){
        arreglo->direccion[x]=arreglo->direccion[x+1];
        
    }

    arreglo_enteros_ajustar(arreglo,arreglo->capacidad-1);
}