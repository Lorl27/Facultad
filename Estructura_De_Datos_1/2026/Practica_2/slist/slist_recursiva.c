#include "slist.h"
#include <stdlib.h>

void slist_destruir(SList lista)
{
    // CASO BASE: Si la lista está vacía, no hay nada que destruir
    if (lista == NULL)
        return;

    // PASO RECURSIVO: Mandamos a destruir todo lo que hay después de mí
    slist_destruir(lista->sig);

    // Cuando esa llamada termine, el resto ya no existe. Ahora me libero yo.
    free(lista);
}

SList slist_insertar(SList lista, int dato, int pos)
{
    // Si llegamos al vacío antes de llegar a la posición, no hacemos nada.
    if (lista == NULL && pos > 0)
        return NULL;

    // CASO BASE: Llegamos a la posición deseada
    if (pos == 0)
    {
        SNodo *nuevo = malloc(sizeof(SNodo));
        nuevo->dato = dato;
        nuevo->sig = lista; // El nuevo se agarra a lo que sea que quede de lista
        return nuevo;       // El nuevo se convierte en la nueva "cabeza" de este tramo
    }

    // PASO RECURSIVO: Le paso el problema al siguiente nodo.
    // Lo que sea que me devuelva, lo engancho a mi flecha.
    lista->sig = slist_insertar(lista->sig, dato, pos - 1);

    // Yo sigo siendo la cabeza de mi propio tramo, me devuelvo intacto.
    return lista;
}

SList slist_eliminar(SList lista, int pos)
{
    // CASO BASE 1: Posición fuera de rango o lista vacía
    if (lista == NULL)
        return NULL;

    // CASO BASE 2: Soy yo el que debe ser eliminado
    if (pos == 0)
    {
        SList resto_de_la_lista = lista->sig; // Guardo a quién tengo detrás
        free(lista);                          // Me demuelo
        return resto_de_la_lista;             // Devuelvo el resto para que el anterior lo agarre
    }

    // PASO RECURSIVO: Yo no soy. Le paso la tarea al siguiente (pos - 1).
    // Y me aseguro de reconectar mi flecha por si mi siguiente se autodestruye.
    lista->sig = slist_eliminar(lista->sig, pos - 1);

    // Devuelvo mi propia dirección, porque yo sobreviví
    return lista;
}

int slist_longitud(SList lista)
{
    // CASO BASE: Llegamos al final (el vacío no mide nada)
    if (lista == NULL)
        return 0;

    // PASO RECURSIVO: Yo cuento como 1, más lo que mida el resto
    return 1 + slist_longitud(lista->sig);
}

void slist_recorrer(SList lista, FuncionVisitante visit)
{
    if (lista == NULL)
        return; // Si no hay nada, cortamos.

    visit(lista->dato);                // 1. Hago mi trabajo
    slist_recorrer(lista->sig, visit); // 2. Paso la pelota al siguiente
}

SList slist_reverso(SList lista)
{
    // CASO BASE: Si la lista está vacía, o solo tiene 1 nodo,
    // ya está al revés. La devolvemos como la nueva cabeza.
    if (lista == NULL || lista->sig == NULL)
    {
        return lista;
    }

    // PASO RECURSIVO: Revertimos todo el RESTO de la lista.
    // Esta llamada viajará hasta el final y nos devolverá el ÚLTIMO nodo
    // (que ahora será el primero de la lista invertida).
    SList resto_revertido = slist_reverso(lista->sig);

    // --- LA MAGIA DE DAR VUELTA LA FLECHA ---
    // En este momento, yo soy 'lista'. El nodo que me sigue es 'lista->sig'.
    // Le digo a ese nodo que me sigue, que su flecha apunte hacia MÍ.
    lista->sig->sig = lista;

    // Y yo, por las dudas (porque podría terminar siendo el último nodo),
    // apunto a NULL para no dejar la flecha suelta.
    lista->sig = NULL;

    // Devolvemos la nueva cabeza de la lista invertida para que viaje hacia arriba
    return resto_revertido;
}