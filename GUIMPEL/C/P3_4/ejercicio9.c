//? GESTIÓN DE LA MEMORIA.

//9 - ¿Cuál es la salida del sig. programa, que utiliza punteros?

#include <stdio.h>
#include <string.h>


int *fun0(int x) {
    return &x;   // puntero a funcion que devuelve la dir de la var pasada como párameto (local!)
}


int main(int argc , char *argv [])
{
    int *ptr = NULL;  //puntero vacio
    ptr = fun0 (2);  // aca se crea el puntero a la var 2 pero al terminar la linea, se elimina.
    printf(" %d\n", *ptr);  //SEGMENTION FAULT  , puntero no indica a nada.
    printf(" %d\n", *ptr);  
    return 0;
}


/* SE SOLUCIONA:
int *fun0(int x) {
    static int y;
    y = x;
    return &y;
}

---
int *fun0(int x) {
    int *ptr = malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = x;
    }
    return ptr;
}

int main() {
    int *ptr = fun0(2);
    if (ptr != NULL) {
        printf(" %d\n", *ptr);
        free(ptr);  // Liberamos la memoria
    }
    return 0;
}
*/