#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "node_id.h"
#include "server.h"
#include "cli.h"
#include "files.h"

char node_id[50];  // ID del nodo global

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <nombre_id_deseado> <puerto_tcp>\n", argv[0]);
        exit(1);
    }

    strcpy(node_id, argv[1]);
    int port = atoi(argv[2]);

    init_file_list();
    obtener_id_unico(node_id);

    pthread_t cli_thread;
    pthread_create(&cli_thread, NULL, cli_loop, NULL);

    start_tcp_server(port);

    pthread_join(cli_thread, NULL);

    return 0;
}