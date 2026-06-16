#include <stdio.h>
#include <stdlib.h>



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