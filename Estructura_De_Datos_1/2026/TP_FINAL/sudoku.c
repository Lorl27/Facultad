#include "sudoku.h"

int validar_filas(const Sudoku * sudoku){
    for(int fila=0;fila<MAX;fila++){
        int leidos[10]={0}; // Inicializado en 0.

        for(int columna=0;columna<MAX;columna++){
            int numero=sudoku->tablero[fila][columna];
            
            //si no es una casilla vacia...
            if(numero!=0){
                if(leidos[numero]!=1) leidos[numero]=1;
                else return 0; //ya lo habíamos leído antes.
            }
        }
    }

    return 1; // Paso todo y es válido.
}


int validar_columna(const Sudoku * sudoku){
    for(int columna=0;columna<MAX;columna++){
        int leidos[10]={0}; // Inicializado en 0.

        for(int fila=0;fila<MAX;fila++){
            int numero=sudoku->tablero[fila][columna];
            
            //si no es una casilla vacia...
            if(numero!=0){
                if(leidos[numero]!=1) leidos[numero]=1;
                else return 0; //ya lo habíamos leído antes.
            }
        }
    }

    return 1; // Paso todo y es válido.
}


int validar_casillas(const Sudoku * sudoku){
    //Fijamos el inicio respectivo de cada casilla
    for(int i_fila=0;i_fila<MAX;i_fila+=MAX_CASILLAS){
        for(int i_col=0;i_col<MAX;i_col+=MAX_CASILLAS){
            int leidos[10]={0};

            //La revisamos por dentro.
            for(int fila=0;fila<MAX_CASILLAS;fila++){
                for(int columna=0;columna<MAX_CASILLAS;columna++){
                    int numero= sudoku->tablero[i_fila+fila][i_col+columna];

                    //si no es una casilla vacia...
                    if(numero!=0){
                        if(leidos[numero]!=1) leidos[numero]=1;
                        else return 0; //ya lo habíamos leído antes.
                    }
                }
            }
        }
    }

    return 1; // Paso todo y es válido.
}


int es_valido(const Sudoku  * sudoku){
    //Idea: Guardamos en un array[10] los números leídos, si se repite -> No es válido.

    return validar_filas(sudoku) && validar_columna(sudoku) && validar_casillas(sudoku);
}

int es_movimiento_valido(const Sudoku * sudoku, int fila, int columna, int numero){

    //Verificamos la fila
    for(int col=0;col<MAX;col++){
        if(sudoku->tablero[fila][col]==numero) return 0;
    }

    //Verificamos la columna
    for(int f=0;f<MAX;f++){
        if(sudoku->tablero[f][columna]==numero) return 0;
    }

    //Verificamos la casilla 3x3:
    int i_fila= (fila/MAX_CASILLAS)*MAX_CASILLAS;
    int i_columna= (columna/MAX_CASILLAS)*MAX_CASILLAS;

    for(int f=0;f<MAX_CASILLAS;f++){
        for(int col=0;col<MAX_CASILLAS;col++){
            if(sudoku->tablero[i_fila+f][i_columna+col]==numero) return 0;
        }
    }

    return 1; // Paso todo: es válido.
}

int tiene_solucion_aux(Sudoku * sudoku){
    int fila=-1;
    int columna=-1;
    int hay_casilla_vacia=0;

    //Buscamos una casilla vacía (0)
    for(int f=0;f<MAX && !hay_casilla_vacia;f++){
        for(int col=0;col<MAX && !hay_casilla_vacia;col++){
            if(sudoku->tablero[f][col]==0){
                fila=f;
                columna=col;
                hay_casilla_vacia=1;
            }
        }
    }

    if(!hay_casilla_vacia) return 1; //Ya esta completo

    //Probamos números del 1 al 9:
    for(int x=1;x<=MAX;x++){
        if(es_movimiento_valido(sudoku,fila,columna,x)){
            sudoku->tablero[fila][columna]=x;

            //Resolvemos el resto del sudoku...
            //si tiene exito: sigue sirviendo el camino
            if(tiene_solucion_aux(sudoku)) return 1;

            //si no lo tiene, no sirve y limpiamos para pasar al sig. número:
            sudoku->tablero[fila][columna]=0;
        }
    }

    return 0; //Probamos todos y ninguno sirvio.
}


int tiene_solucion(Sudoku * sudoku){
    if(!es_valido(sudoku)) return 0;

    return tiene_solucion_aux(sudoku);
}


void imprimir_sudoku(const Sudoku * sudoku){
    for(int fila=0;fila<MAX;fila++){
        for(int columna=0;columna<MAX;columna++){
            int numero= sudoku->tablero[fila][columna];
            printf("%d ",numero);
        }
        printf("\n");
    }
    printf("\n");
}

int contar_soluciones(Sudoku * sudoku, int * contador){
    int fila=-1;
    int columna=-1;
    int hay_casilla_vacia=0;

    //Buscamos una casilla vacía (0)
    for(int f=0;f<MAX && !hay_casilla_vacia;f++){
        for(int col=0;col<MAX && !hay_casilla_vacia;col++){
            if(sudoku->tablero[f][col]==0){
                fila=f;
                columna=col;
                hay_casilla_vacia=1;
            }
        }
    }

    if(!hay_casilla_vacia){
        (*contador)++;
        return 1; // encontramos 1
    }

    //Probamos números del 1 al 9:
    for(int x=1;x<=MAX;x++){
        if(es_movimiento_valido(sudoku,fila,columna,x)){
            sudoku->tablero[fila][columna]=x;

            //Resolvemos el resto del sudoku...
            //si tiene exito: sigue sirviendo el camino
            contar_soluciones(sudoku,contador);

            //si no lo tiene, no sirve y limpiamos para pasar al sig. número:
            sudoku->tablero[fila][columna]=0;

            if(*contador>=2) return *contador;
        }
    }

    return *contador; //Probamos todos ya
}

int cantidad_soluciones(Sudoku * sudoku){
    int contador=0;
    Sudoku original = *sudoku;

    contar_soluciones(sudoku,&contador);

    *sudoku=original; //lo restauramos.

    if(contador==0) return 0;
    else tiene_solucion(sudoku);

    return contador;
    
}

Sudoku sudoku_crear(void){
    Sudoku sudo;
    for(int fila=0;fila<MAX;fila++){
        for(int columna=0;columna<MAX;columna++){
            sudo.tablero[fila][columna]=0;
        }
    }
    return sudo;
}

Sudoku sudoku_aleatorio(void){
    Sudoku sudo;
    int resuelto=0;
    //srand(time(NULL));  NOTA: Para evitar que rand dé el mismo número en intervalos cortos, lo mejor es ponerlo en main.c

    while(!resuelto){
        sudo = sudoku_crear();

        //Llenamos celdas aleatorias
        int puestos=0;
        while(puestos<6){
            int fila= rand() % MAX;
            int columna = rand() % MAX;
            int numero= (rand()%MAX)+1 ; //1-9

            if(sudo.tablero[fila][columna]==0 && es_movimiento_valido(&sudo,fila,columna,numero)){
                sudo.tablero[fila][columna]=numero;
                puestos++;
            }
        }

        if(tiene_solucion(&sudo)) resuelto=1; 
    }
    return sudo;
}

Sudoku sudoku_con_unica_solucion(void){
    Sudoku aleatorio=sudoku_aleatorio();

    //Idea: el aleatorio ir podandolo hasta tener una única sol. válida
    int celdas_a_borrar=MAX_BORRAR;
    int intentos= 0;
    while(celdas_a_borrar>0 && intentos<MAX_INTENTOS){
        int fila_r=rand()%MAX;
        int col_r=rand()%MAX;

        //si no es vacia...
        if(aleatorio.tablero[fila_r][col_r]!=0){
            int tmp = aleatorio.tablero[fila_r][col_r];

            //Borramos el elemento.
            aleatorio.tablero[fila_r][col_r]=0;

            Sudoku copia = aleatorio; //Creamos una copia porque cant. soluciones afecta al original (Nos borra los borrados)

            //Si no tiene única sol al borrarlo, reestauramos
            if(cantidad_soluciones(&copia)!=1) aleatorio.tablero[fila_r][col_r]=tmp;
            else celdas_a_borrar--; //Si sigue teniendo, lo borramos.
        }

        intentos++;
    }

    return aleatorio;
}
