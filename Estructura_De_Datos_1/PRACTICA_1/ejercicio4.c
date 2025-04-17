//--------- ej 3:

typedef struct{
    int* direccion;
    int capacidad;
} ArregloEnteros;

#include <stdio.h>
#include <stdlib.h>

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

//--------------- ej 4:

// 4. Extienda la implementaci´on del ejercicio anterior con las siguientes funciones:
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

int main() {
    ArregloEnteros* arreglo = arreglo_enteros_crear(5);

    int cap=arreglo_enteros_capacidad(arreglo);
    printf("La capacidad de mi array es de: %d \n",cap);

    for (int x=0; x<cap;x++) {
        arreglo_enteros_escribir(arreglo,x, x*10);
    }

    arreglo_enteros_imprimir(arreglo);

    // AJUSTAR - ampliar a capacidad 7
    arreglo_enteros_ajustar(arreglo, 7);
    arreglo_enteros_escribir(arreglo, 5, 60);
    arreglo_enteros_escribir(arreglo, 6, 70);
    printf("\nTras ajustar a capacidad 7:\n");
    arreglo_enteros_imprimir(arreglo);

    // INSERTAR en posición 2 el dato 999
    arreglo_enteros_insertar(arreglo, 2, 999);
    printf("\nTras insertar 999 en posición 2:\n");
    arreglo_enteros_imprimir(arreglo);

    // ELIMINAR el dato en la posición 4
    arreglo_enteros_eliminar(arreglo, 4);
    printf("\nTras eliminar el elemento en posición 4:\n");
    arreglo_enteros_imprimir(arreglo);

    // Liberar memoria
    arreglo_enteros_destruir(arreglo);
    return 0;
}
