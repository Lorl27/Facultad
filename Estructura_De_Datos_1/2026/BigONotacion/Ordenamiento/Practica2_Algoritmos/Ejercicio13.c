typedef struct persona {
    int grupo;
    char nombre[256];
    int pos_original;
} Persona;


// Tiempo: O(n*log(n))
// Memoria: O(1)
void ordenar_personas(int n, Persona personas[]){
    for(int x=0;x<n;x++){
        personas[x].pos_original=x;
    }

    qsort(personas,n,sizeof(Persona),comparar);
}

// Compara clasicamente, exceptuando que si son iguales: 
// Devuelve la menor posicion para que queden en el orden original.
int comparar(const void *a, const void *b){

    const struct persona *p1 = a;
    const struct persona *p2 = b;

    if(p1->grupo < p2->grupo) return -1;

    if(p1->grupo > p2->grupo) return 1;

    // Desempate
    return p1->pos_original - p2->pos_original;
}


/* ¿Por qué nos preocupamos por la estabilidad?

Como debímos modiifcar la estructura original, este cambio NO siempre se puede realizar.
Además ese campo puede estar limitado por la memoria o no poder existir
*/