#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define CARPETA_COMPARTIDA "./compartida/"

void init_file_list() {
    printf("Escaneando carpeta compartida...\n");
    listar_archivos();
}

void listar_archivos() {
    DIR *d = opendir(CARPETA_COMPARTIDA);
    if (!d) {
        perror("No se pudo abrir la carpeta compartida");
        return;
    }

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG)
            printf("- %s\n", dir->d_name);
    }
    closedir(d);
}