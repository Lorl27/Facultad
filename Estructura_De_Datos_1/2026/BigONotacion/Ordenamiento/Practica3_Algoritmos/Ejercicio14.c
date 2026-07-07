/*

COmo cada aula puede tener actividades que no se superpongan, cuando llega una nueva:
existe un aula libre -> usamos esa
ninguna libre -> hay que abrir otra uala

Ordenamos por hora inicio: si termino antes que la de actividad acutal: reuitilziamos el aula.

TIempo. O(n*log(n))
Memoria: O(n) peor caso.
*/
int asignarAulas(Actividad actividades[], int n) {
    // Ordenamos por inicio
    qsort(actividades, n, sizeof(Actividad), compararInicio);

    MinHeap *heap = crearHeap(n);

    for (int i = 0; i < n; i++) {
        if (heap->size > 0 && heapMin(heap) <= actividades[i].inicio) {
            heapPop(heap); // reutilizamos aula
        }
        heapPush(heap, actividades[i].fin); // ocupamos aula
    }

    int resultado = heap->size;
    free(heap->datos);
    free(heap);
    return resultado;
}


int compararInicio(const void *a, const void *b) {
    Actividad *act1 = (Actividad *)a;
    Actividad *act2 = (Actividad *)b;
    return act1->inicio - act2->inicio;
}

typedef struct {
    int inicio;
    int fin;
} Actividad;


int heapMin(MinHeap *h) {
    return h->datos[0];
}