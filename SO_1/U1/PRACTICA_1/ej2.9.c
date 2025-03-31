//  i) El comando de cambio de directorio cd suele ser un built-in de la shell. 
//Puede implementarse  mediante un programa al igual que, ej., ls?


// El comando cd (change directory) es un comando interno de las shells porque cambia el directorio de trabajo del proceso actual. Sin embargo, no puede ser implementado como un programa externo de la misma manera que otros comandos como ls, echo, etc. Esto es porque cd afecta el entorno del proceso actual (en este caso, la shell), y no puede modificar el directorio de trabajo del proceso padre desde un proceso hijo sin algún mecanismo de comunicación.


// INTENTO:

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <directorio>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Intentar cambiar al directorio proporcionado
    if (chdir(argv[1]) == -1) {
        perror("Error al cambiar de directorio");
        exit(EXIT_FAILURE);
    }

    // Si llega aquí, significa que el directorio se cambió correctamente
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Directorio actual: %s\n", cwd);
    } else {
        perror("getcwd error");
        exit(EXIT_FAILURE);
    }

    return 0;
}
