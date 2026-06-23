#include <stdio.h>
#include <stdlib.h>

//1)


#define N 50
typedef struct _Cola{
    int datos[N];
    int posicionAAgregar;
    int posicionAEliminar;
}Cola;


//a.

int posicionAAgregar=0;
int posicionAEliminar=0;

//si posicionAAgregar==posicionAEliminar entonces la Cola esta vacia!

//b.

void enqueue(Cola *p, int datoAAgregar){
    if(p==NULL) return;

    //Calculamos cuál sería el próximo índice dando la vuelta circularmente
    int prox_pos = (p->posicionAAgregar+1) %N;

    if(prox_pos==p->posicionAEliminar) return; //si se pisa, esta lleno!

    p->datos[p->posicionAAgregar]=datoAAgregar;

    p->posicionAAgregar=prox_pos;

}

//c.

int dequeue(Cola *p){
    if(p==NULL || p->posicionAAgregar==p->posicionAEliminar) return -1;

    int dato_e=p->datos[p->posicionAEliminar];

    p->datos[p->posicionAEliminar]=-1;

    int prox_pos = (p->posicionAEliminar+1)%N;
    p->posicionAEliminar= prox_pos;

    return dato_e;

}

//2)

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

//a.
void * no_copiar(void * a){
    return a;
}

GList nodosI(GList lista, int i){
    if(lista==NULL) return NULL;

    GList nueva = glist_crear();
    int x=0;
    for(GNode  * tmp = lista; tmp!=NULL; tmp = tmp->next){
        if(x%i==0) nueva=glist_insertar_final(nueva,no_copiar);
        x++;
    }
    return nueva;

}

//b.

int main(){
    GList listaPersona ; //la lista de personas
    GList listaPersonasM3=nodosI(listaPersona,3);
}