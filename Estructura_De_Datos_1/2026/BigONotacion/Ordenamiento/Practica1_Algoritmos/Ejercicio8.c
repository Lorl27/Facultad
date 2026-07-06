// Idea: BACKTRACKING.
// Sigo una posibilidad, si en algùn momento NO es valida: vuelvo atràs y pruebo otra
// EN este formato: eligo una columna, pruebo todas las filas: 
//si ninguna es valida -> me voy a otra clumna.
// Si alguna es valida -> me voy a la sig. fila.

#define N 8

//A:

// Puedo poner una reina?
int esValida(int tablero[], int fila, int columna){

    for(int i=0;i<fila;i++){
        if(tablero[i]==columna) return 0; //col1==col2

        if(abs(i-fila)==abs(tablero[i]-columna)) return 0; //fila1-fila2 == col1 - col2  (es una diagnonal)
    }

    return 1; //La puedo poner.
}

// Tiempo : O(n!)
// Memoria : O(n)
int resolver(int tablero[N], int fila){

    if(fila==N){ //yA colocamos todas las reinas.
        imprimir(tablero);
        return 1;
    }

    int soluciones = 0;

    for(int col=0;col<N;col++){
        if(esValida(tablero,fila,col)){
            tablero[fila]=col;
            soluciones += resolver(tablero,fila+1);
        }
    }

    return soluciones;
}

//B:
void imprimir(int tablero[N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(tablero[i]==j) printf("R ");
            else printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}
