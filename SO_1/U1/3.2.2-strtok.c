#include <stdio.h>
#include <string.h>

int main() {
    char texto[] = "Hola thor? Domingo.";
    char *token = strtok(texto, " ,?");  // Usa espacios, comas y '?' como delimitadores

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, " ,?");  // Obtiene el siguiente token
    }

    return 0;
}
