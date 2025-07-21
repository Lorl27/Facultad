#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "files.h"
extern char node_id[50];

void *cli_loop(void *arg) {
    char comando[100];

    while (1) {
        printf(">> ");
        fflush(stdout);
        fgets(comando, sizeof(comando), stdin);

        if (strncmp(comando, "id_nodo", 7) == 0) {
            printf("Mi ID: %s\n", node_id);
        } else if (strncmp(comando, "listar_mis_archivos", 19) == 0) {
            listar_archivos();
        } else if (strncmp(comando, "salir", 5) == 0) {
            printf("Finalizando...\n");
            exit(0);
        } else {
            printf("Comando desconocido.\n");
        }
    }
    return NULL;
}