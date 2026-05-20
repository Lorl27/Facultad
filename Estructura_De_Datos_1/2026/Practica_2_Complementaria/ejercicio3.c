#include "../Practica_2/glist/glist.h"
#include <stdio.h>
#include <stdlib.h>

//gcc ejercicio3.c ../Practica_2/glist/glist.c -o ej3


/// ------

GList glist_ordenar(GList lista, FuncionComparadora comp) {
    if (!lista) return lista;
    
    int hubo_cambios;
    do {
        hubo_cambios = 0;
        GNode *actual = lista;
        
        while (actual->next != NULL) {
            // Si el actual es MAYOR que el siguiente, los invertimos
            if (comp(actual->data, actual->next->data) > 0) {
                // Intercambiamos solo las 'cajas' de datos (void*)
                void *temporal = actual->data;
                actual->data = actual->next->data;
                actual->next->data = temporal;
                
                hubo_cambios = 1; // Anotamos que hicimos un cambio
            }
            actual = actual->next;
        }
    } while (hubo_cambios); // Repetimos hasta que la lista de una vuelta sin cambios
    
    return lista;
}


GList glist_concatenar(GList lista1, GList lista2, FuncionCopia copy) {
    GList nueva = glist_crear();
    
    for(GNode *tmp = lista1; tmp != NULL; tmp = tmp->next) {
        nueva = insertar_final(nueva, tmp->data, copy);
    }
    for(GNode *tmp = lista2; tmp != NULL; tmp = tmp->next) {
        nueva = insertar_final(nueva, tmp->data, copy);
    }
    
    return nueva;
}


GList glist_interseccion(GList lista1, GList lista2, FuncionCopia copy, FuncionComparadora comp) {
    GList nueva = glist_crear();
    
    for(GNode *tmp = lista1; tmp != NULL; tmp = tmp->next) {
        // Si el elemento de la lista 1 existe en la lista 2, lo copiamos a la nueva
        if (contiene(lista2, tmp->data, comp)) {
            nueva = insertar_final(nueva, tmp->data, copy);
        }
    }
    
    return nueva;
}

/// ------


//------ F. AUXS: --------

void destruir_enteros(void * entero){
    free((int*)entero);
}

void  imprimir_enteros(void * entero){
    printf("[%d]->",*((int*)entero));
}

void * copiar_enteros(void * entero){
    int * copia=malloc(sizeof(int));
    *copia=* (int*)entero;
    return copia;
}

int  comparar_enteros(void * a, void *b){
    int a_entero= * (int*) a;
    int b_entero= * (int*) b;

    if(a_entero<b_entero) return -1;
    if(a_entero>b_entero) return 1;
    return 0;
}


////------

void destruir_enterosV2(int * entero){
    free(entero);
}

void imprimir_enterosV2(int * entero){
    printf("%d", *entero);
}

int * copiar_enterosV2(int * a){
    int * copy = malloc(sizeof(int));
    *copy = *a;
    return copy;
}

int comparar_enterosV2(int * a, int * b){
    if(*a < *b) return -1;
    if(*a > *b) return 1;
    return 0;
}

///----

//---------------------------

void lista_comandos(int opcion, GList * mis_listas){
    int elemento;
    int posicion;
    int id;
    int id2;
    int id3;
    int indice_elemento;
    int longitud_lista;

    switch (opcion)
    {
    case 1:
        printf("[CREANDO UNA LISTA]\n");
        printf("Ingrese el id deseado (0-9) para la lista a crear: \n");
        scanf("%d",&id);
        mis_listas[id]=glist_crear();
        printf("Lista %d creada.\n", id);
        break;
    case 2:
        printf("[DESTRUYENDO UNA LISTA]\n");
        printf("Ingrese la lista (id) a destruir:\t");
        scanf("%d",&id);
        glist_destruir(mis_listas[id],destruir_enteros);
        mis_listas[id] = NULL;
        printf("Lista %d destruida.\n", id);
        break;
    case 3:
        printf("[IMPRIMIENDO UNA LISTA]\n");
        printf("Ingrese la lista(id) a imprimir:\t");
        scanf("%d",&id);
        glist_recorrer(mis_listas[id],imprimir_enteros);
        printf("Lista %d recorrida.\n", id);
        break;
    case 4:
        printf("[AGREGAR AL FINAL DE UNA LISTA]\n");
        printf("Ingrese la lista (id)a insertar un elemento:\t");
        scanf("%d",&id);
        printf("Ingrese el elemento para insertar:\t");
        scanf("%d",&elemento);
        mis_listas[id]=insertar_final(mis_listas[id],&elemento,(FuncionCopia)copiar_enterosV2);
        printf("Lista %d inserto correctamente.\n", id);
        break;
    case 5:
        printf("[AGREGAR AL INICIO DE UNA LISTA]\n");
        printf("Ingrese la lista(id) a insertar un elemento:\t");
        scanf("%d",&id);
        printf("Ingrese el elemento para insertar:\t");
        scanf("%d",&elemento);
        mis_listas[id]=insertar(mis_listas[id],&elemento,copiar_enteros,0);
        printf("Lista %d inserto correctamente.\n", id);
        break;
    case 6:
        printf("[AGREGAR EN POSICIÒN EN UNA LISTA]\n");
        printf("Ingrese la lista(id) a insertar un elemento:\t");
        scanf("%d",&id);
        printf("Ingrese el elemento para insertar:\t");
        scanf("%d",&elemento);
        printf("Ingrese la posiciòn para insertar:\t");
        scanf("%d",&posicion);
        mis_listas[id]=insertar(mis_listas[id],&elemento,copiar_enteros,posicion);
        printf("Lista %d inserto correctamente.\n", id);
        break;
    case 7:
        printf("[LONGITUD DE UNA LISTA]\n");
        printf("Ingrese la lista(id) para saber su longitud:\t");
        scanf("%d",&id);
        longitud_lista=longitud(mis_listas[id]);
        printf("Lista %d medida correctamente.\t", id);
        printf("LONGITUD: %d\n",longitud_lista);
        break;
    case 8:
        printf("[CONCATENANDO UNA LISTA CON OTRA]\n");
        printf("Ingrese la primer lista(id) a interseccionar\t");
        scanf("%d",&id);
        printf("Ingrese la segunda lista(id) a interseccionar\t");
        scanf("%d",&id2);
        printf("Ingrese donde se almacenara la interseccion (id lista)\t");
        scanf("%d",&id3);
        mis_listas[id3]=glist_concatenar(mis_listas[id],mis_listas[id2],copiar_enteros);
        printf("Listas %d y %d intersionadas correctamente.\n", id,id2);
        break;
    case 9:
        printf("[ELIMINA ELEMENTO DE UNA LISTA]\n");
        printf("Ingrese la lista (id):\t");
        scanf("%d",&id);
        printf("Ingrese el indice del elemento para eliminarlo:\t");
        scanf("%d",&indice_elemento);
        glist_eliminar_elemento_recursivamente(mis_listas[id],destruir_enteros,indice_elemento);
        printf("Lista %d elimino el dato correctamente.\n", id);
        break;
    case 10:
        printf("[¿CONTIENE ?? LA LISTA?]\n");
        printf("Ingrese la lista(id) a inspeccionar:\t");
        scanf("%d",&id);
        printf("Ingrese el elemento a buscar:\t");
        scanf("%d",&elemento);
        if(contiene(mis_listas[id],&elemento,comparar_enteros))
            printf("Resultado:SI\n");
        else 
            printf("Resultado:NO\n");     

        printf("Lista %d buscada correctamente.\n", id);
        break;
    case 11:
        printf("[BUSCANDO ELEMENTOS EN UNA LISTA]\n");
        printf("Ingrese la lista(id) a inspeccionar:\t");
        scanf("%d",&id);
        printf("Ingrese el elemento a buscar:\t");
        scanf("%d",&elemento);

        GNode *tmp = mis_listas[id];
        int contador = 0;
        int encontrados = 0;
        
        printf("El elemento %d esta en los indices: ", elemento);
        while(tmp != NULL){
            if(comparar_enteros(tmp->data, &elemento) == 0){
                printf("%d ", contador);
                encontrados = 1;
            }
            tmp = tmp->next;
            contador++;
        }
        
        if(!encontrados) printf("Ninguno (no esta).");
        printf("\nLista %d buscada con exito.\n", id);
        break;
    case 12:
        printf("[INTERSECCION DE UNA LISTA CON OTRA]\n");
        printf("Ingrese la primer lista(id) a interseccionar\t");
        scanf("%d",&id);
        printf("Ingrese la segunda lista(id) a interseccionar\t");
        scanf("%d",&id2);
        printf("Ingrese donde se almacenara la interseccion (id lista)\t");
        scanf("%d",&id3);
        mis_listas[id3]=glist_interseccion(mis_listas[id],mis_listas[id2],copiar_enteros,comparar_enteros);
        printf("Listas %d y %d intersionadas correctamente.\n", id,id2);
        break;
    case 13:
        printf("[ORDENANDO UNA LISTA]\n");
        printf("Ingrese la list(id) a a ordenar:\t");
        scanf("%d",&id);
        mis_listas[id] =glist_ordenar(mis_listas[id],comparar_enteros);        
        printf("Lista %d ordenada correctamente.\n", id);
        break;
    default:
    printf("[CANCELADO]\n");
        break;
    }
}


int main(void){
    int opcion=0;
    GList mis_listas[10] = {NULL};


    while(opcion!=-1){
        printf("Elige el comando que usted prefiera, porfavor...\n");
        printf("-----------------------------------\n");
        printf("1. Crear");        
        printf("\n----------------------------------\n");
        printf("2. Destruir");        
        printf("\n----------------------------------\n");
        printf("3. Imprimir");        
        printf("\n----------------------------------\n");
        printf("4. Agregar al final");        
        printf("\n----------------------------------\n");
        printf("5. Agregar al inicio");        
        printf("\n----------------------------------\n");
        printf("6. Agregar en posiciòn");        
        printf("\n----------------------------------\n");
        printf("7. Longitud");        
        printf("\n----------------------------------\n");
        printf("8. Concatenar");        
        printf("\n----------------------------------\n");
        printf("9. Eliminar");        
        printf("\n----------------------------------\n");
        printf("10. Contiene");
        printf("\n----------------------------------\n");
        printf("11. Indice");        
        printf("\n----------------------------------\n");
        printf("12. Intersecar");        
        printf("\n----------------------------------\n");
        printf("13. Ordenar");
        printf("\n----------------------------------\n");
        printf("-1. Cancelar\n\t");


        scanf("%d",&opcion);
        if(opcion == -1) break;
        lista_comandos(opcion,mis_listas);
    }

    // Limpieza final al salir
    for(int i=0; i<10; i++) {
        if(mis_listas[i] != NULL) {
            glist_destruir(mis_listas[i], destruir_enteros);
        }
    }
    printf("¡Adios y memoria liberada!\n");
    return 0;
}

/*  FORMA CORRECTA ESTRICTA:
int main(void) {
    GList mis_listas[10] = {NULL}; // Soportaremos hasta 10 listas (IDs 0 al 9)
    char comando[50];
    char subcomando[50];
    int id_lista, id_lista2, id_lista3, elemento, pos;

    printf("Iniciando interprete de comandos de listas...\n");

    while (1) {
        printf("> ");
        if (scanf("%49s", comando) != 1) break;

        // COMANDO: crear <id>
        if (strcmp(comando, "crear") == 0) {
            scanf("%d", &id_lista);
            mis_listas[id_lista] = glist_crear();
            printf("Lista %d creada.\n", id_lista);
        }
        // COMANDO: imprimir <id>
        else if (strcmp(comando, "imprimir") == 0) {
            scanf("%d", &id_lista);
            printf("Lista %d: ", id_lista);
            glist_recorrer(mis_listas[id_lista], imprimir_enteros);
            printf("NULL\n");
        }
        // COMANDO: agregar <inicio/final/pos> <id> <elem> [pos]
        else if (strcmp(comando, "agregar") == 0) {
            scanf("%49s", subcomando); // Leemos si es 'inicio', 'final' o 'pos'
            
            if (strcmp(subcomando, "final") == 0) {
                scanf("%d %d", &id_lista, &elemento);
                // Le pasamos la lista correcta sacandola de nuestro arreglo
                mis_listas[id_lista] = insertar_final(mis_listas[id_lista], &elemento, copiar_enteros);
            }
            // ... (aqui irian los if para 'inicio' y 'pos')
        }
        // COMANDO: concatenar <id1> <id2> <id3>
        else if (strcmp(comando, "concatenar") == 0) {
            scanf("%d %d %d", &id_lista, &id_lista2, &id_lista3);
            mis_listas[id_lista3] = glist_concatenar(mis_listas[id_lista], mis_listas[id_lista2], copiar_enteros);
            printf("Listas %d y %d concatenadas en lista %d.\n", id_lista, id_lista2, id_lista3);
        }
        else if (strcmp(comando, "salir") == 0) {
            break;
        }
        else {
            printf("Comando no reconocido.\n");
            while (getchar() != '\n'); // Limpiar basura
        }
    }

    // TODO: Hacer un for del 0 al 9 destruyendo todas las listas que no sean NULL
    return 0;
}
*/