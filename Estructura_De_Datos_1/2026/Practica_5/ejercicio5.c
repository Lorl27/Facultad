#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablahash.h"
#include "contacto.h"

// --- WRAPPERS ---
// Adaptadores para que las firmas coincidan perfectamente con el void* de la Tabla Hash
void destruir_wrapper(void *dato) {
    contacto_destruir((Contacto *)dato);
}

void *copiar_wrapper(void *dato) {
    return contacto_copia((Contacto *)dato);
}

int comparar_wrapper(void *dato1, void *dato2) {
    return contacto_comparar((Contacto *)dato1, (Contacto *)dato2);
}

unsigned hashear_wrapper(void *dato) {
    return contacto_heashear((Contacto *)dato);
}

int main() {
    // 1. Inicializamos la agenda
    TablaHash agenda = tablahash_crear(100, hashear_wrapper);

    char buffer[256];
    char comando[20];
    char resto[200];

    printf("Agenda Hash iniciada.\nComandos permitidos: insertar, buscar, eliminar (o 'salir').\n\n");

    // 2. Bucle infinito de lectura por consola
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        
        // Parseamos la primera palabra (comando) y el resto de la linea (argumentos)
        if (sscanf(buffer, "%19s %[^\n]", comando, resto) < 1) {
            continue; // Linea vacia
        }

        if (strcmp(comando, "salir") == 0) {
            break; // Cortamos la ejecucion
        }

        // --- COMANDO: INSERTAR ---
        if (strcmp(comando, "insertar") == 0) {
            char nombre[100];
            char telefono[50];
            unsigned int edad;

            // La magia de sscanf: "%[^,]" lee todo hasta encontrar una coma.
            // Los espacios extra despues de las comas son ignorados automaticamente.
            if (sscanf(resto, "%[^,], %[^,], %u", nombre, telefono, &edad) == 3) {
                
                Contacto *nuevo = contacto_crear(nombre, telefono, edad);
                
                tablahash_insertar(agenda, nuevo, destruir_wrapper, copiar_wrapper, comparar_wrapper);
                
                // ¡VITAL! Destruimos el original temporal porque la tabla ya hizo su propia copia
                contacto_destruir(nuevo); 
                
                printf("=> Contacto insertado/actualizado con exito.\n");
            } else {
                printf("=> Error: El formato debe ser 'insertar nombre, numero, edad'\n");
            }
        }
        
        // --- COMANDO: BUSCAR ---
        else if (strcmp(comando, "buscar") == 0) {
            // El patron "Dummy": Creamos un contacto vacio solo con el nombre a buscar
            Contacto *señuelo = contacto_crear(resto, "", 0);
            
            Contacto *encontrado = (Contacto *)tablahash_buscar(agenda, señuelo, comparar_wrapper);

            if (encontrado != NULL) {
                printf("=> Encontrado: ");
                contacto_imprimir(encontrado);
                printf("\n");
            } else {
                printf("=> Contacto no encontrado en la agenda.\n");
            }
            
            contacto_destruir(señuelo); // Destruimos el señuelo
        }
        
        // --- COMANDO: ELIMINAR ---
        else if (strcmp(comando, "eliminar") == 0) {
            Contacto *señuelo = contacto_crear(resto, "", 0);
            
            tablahash_eliminar(agenda, señuelo, comparar_wrapper, destruir_wrapper);
            
            contacto_destruir(señuelo);
            printf("=> Comando de eliminacion procesado.\n");
        }
        
        // --- COMANDO DESCONOCIDO ---
        else {
            printf("=> Comando '%s' no reconocido.\n", comando);
        }
    }

    // 3. Limpieza absoluta antes de cerrar el programa
    tablahash_destruir(agenda, destruir_wrapper);
    printf("Agenda destruida. Memoria liberada. ¡Adios!\n");
    
    return 0;
}