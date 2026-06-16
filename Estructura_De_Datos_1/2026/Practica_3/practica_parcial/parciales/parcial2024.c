
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

typedef void ** GArray;

typedef struct 
{
    char* nombre;
    char* direccion;
    char * dni;
    int edad;
} Persona;

typedef void *(*FuncionCopia)(void *dato);
typedef int (*Predicado) (void *dato); //0: false - 1:true

//1)

GArray listToArray(GList lista, FuncionCopia c){
    int n= longitud(lista);
    GArray array = malloc(sizeof(void*)*n);

    int x=0;
    for(GNode * tmp=lista; tmp!=NULL; tmp=tmp->next){
        array[x]=c(tmp->data);
        x++;
    }
    return array;
}

//2)

void * no_copiar(void * a){
    return a;
}

GArray listToArrayPersona(GList lista){
    if(lista==NULL) return NULL;
    GArray array = listToArray(lista,no_copiar);

    return array;
}

//3)


int f18masA(void * persona){
    Persona * p  = (Persona *) persona;
    return p->edad>18 && (strchr(p->direccion, 'a') != NULL || strchr(p->direccion, 'A') != NULL);
}

void * copiar_personas(void * persona){
    Persona * p = (Persona *) persona;
    Persona * copia= malloc(sizeof(Persona));
    copia->edad=p->edad;

    copia->direccion=malloc(sizeof(char)*(strlen(p->direccion)+1));
    strcpy(copia->direccion,p->direccion);

    copia->dni=malloc(sizeof(char)*(strlen(p->dni)+1));
    strcpy(copia->dni,p->dni);
    
    copia->nombre=malloc(sizeof(char)*(strlen(p->nombre)+1));
    strcpy(copia->nombre,p->nombre);

    return copia;
}

GList mayores18ConA(GList lista){
    GList nueva=glist_filtrar(lista,f18masA,copiar_personas);
    return nueva;
}
