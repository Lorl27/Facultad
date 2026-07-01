#include "sudoku.h"

#define MAX_BUFFER 100
#define MAX_ALEATORIOS 3

//Permite testear el algoritmo a partir de un archivo de entrada
int main(int argc, char *argv[]) {
    srand(time(NULL));

    // Ejercicio 3 - Testeo de archivos :
    if(argc == 2){
        FILE * archivo;
        archivo = fopen(argv[1],"r"); //Abrir en modo lectura

        if(archivo==NULL){
            printf("[WARNING] Error al abrir el archivo %s .\n",argv[1]);
            exit(EXIT_FAILURE);
        }

        //Guardamos los datos (la cadena) en un buffer
        char buffer[MAX_BUFFER];
        if(!fgets(buffer,MAX_BUFFER,archivo)){
            printf("[WARNING] Error al leer el archivo %s .\n",argv[1]);
            fclose(archivo);
            exit(EXIT_FAILURE);
        }

        fclose(archivo); //Lo cerramos porque ya no lo necesitamos más.

        // Cargamos los datos del buffer en el Sudoku, para luego poder testear.

        Sudoku sudo;
        int x=0;
        for(int fila=0;fila<MAX;fila++){
            for(int columna=0;columna<MAX;columna++){
                int entero=buffer[x]-'0';
                sudo.tablero[fila][columna]=entero;
                x++;
            }
        }

        printf("[MAIN] Iniciando testeo del algoritmo con Sudoku:\n");
        imprimir_sudoku(&sudo);

        int resultado= tiene_solucion(&sudo);
        if(!resultado) printf("[MAIN] El sudoku pasado NO tiene solución.\n");
        else{
            printf("[MAIN] El sudoku pasado tiene solución y es: \n");
            imprimir_sudoku(&sudo);
        }
    }
    // Ejercicio 6: Obtener solución única para 3 tableros de solución única distintos
    // Por lo menos 1/3 debe ser generado por sudoku_con_unica_solucion
    else if(argc==1){
        
        // NOTA: Si se desea testear con uno ya existente, llamar ./testeador CasosDePrueba/nombre_archivo.txt
        // y alterar MAX_ALEATORIOS a la cantidad deseada.

        for(int x= 1;x<=MAX_ALEATORIOS; x++) {
            printf("[MAIN] Generando un tablero aleatorio nro %d con solución única (Puede tardar).\n", x);

            Sudoku random = sudoku_con_unica_solucion();
            printf("[MAIN] Tablero nro %d generado:\n",x);
            imprimir_sudoku(&random);

            Sudoku copia = random;

            printf("[MAIN] Resolviendo el tablero nro %d generado... \n",x);
            
            if(tiene_solucion(&copia)){
                printf("[MAIN] La solución del tablero nro %d aleatorio es: \n",x);
                imprimir_sudoku(&copia);
            }else printf("[MAIN] Ocurrio un error, el tablero nro %d no cuenta con solución.\n",x); //NO debería nunca llegar acá, pero lo pongo por seguridad.

        }
        
    }
    else{
        printf("[WARNING] Sobran parámetros.\n");
        printf("[WARNING] Uso para testear: %s <archivo_entrada.txt>  \n", argv[0]);
        printf("[WARNING] Uso para generar aleatorio: %s \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}