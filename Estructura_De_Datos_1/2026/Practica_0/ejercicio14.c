#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char * get_new_line(void){
    char *p = malloc(sizeof(char)*100);
    if(p==NULL) return NULL;
    printf("Ingrese linea aqui:\n");
    if (fgets(p, 100, stdin) == NULL) {
        free(p);
        return NULL;
    }
    return p;
}



typedef struct {
    char* nombre;
    char * nro;
    unsigned int edad;
} Contacto;


Contacto crear_contacto(){
    Contacto new; 
    printf("A continuaciòn, ingrese el nombre del contacto:\n");
    new.nombre=get_new_line();
    printf("A continuaciòn, ingrese el nro telefonico del contacto:\n");
    new.nro=get_new_line();
    printf("A continuaciòn, ingrese la edad del contacto:\n");
    scanf("%u",&new.edad);

    //! Después de un scanf, queda un '\n' trabado en el teclado.
    // Hay que limpiar el buffer para que el próximo get_new_line no falle.
    while(getchar() != '\n');

    return new;
}

//si, es necesario que sea puntero pq sino se actualizaria localmente
void actuazlizar_edad(Contacto * contacto){
    printf("\nIngrese el nombre del contacto a modificar: ");
    scanf("%u", &(contacto->edad));
    while(getchar() != '\n'); // Limpiamos el buffer de nuevo
}

typedef struct 
{
    Contacto contactos[MAX];
    int cantidad_contactos;
} Agenda;


void alta_contacto(Agenda * agenda){
    // Verificamos que haya espacio en el arreglo
    if (agenda->cantidad_contactos < MAX) {
        agenda->contactos[agenda->cantidad_contactos] = crear_contacto();
        agenda->cantidad_contactos++; 
        printf("Contacto guardado exitosamente.\n");
    } else {
        printf("Error: La agenda esta llena.\n");
    }
}


void modificar_edad_for(Agenda *agenda) {
    printf("\nIngrese el nombre del contacto a modificar: ");
    char *nombre_buscado = get_new_line();
    
    int encontrado = 0; // Bandera para saber si lo hallamos
    
    for (int i = 0; i < agenda->cantidad_contactos; i++) {
        if (strcmp(agenda->contactos[i].nombre, nombre_buscado) == 0) {
            actuazlizar_edad(&(agenda->contactos[i]));
            encontrado = 1;
            break; 
        }
    }
    
    if (encontrado == 0) {
        printf("Contacto no hallado.\n");
    }
    
    free(nombre_buscado); 
}

void modificar_edad(Agenda *agenda) {
    printf("\nIngrese el nombre del contacto a modificar: ");
    char *nombre_buscado = get_new_line();
    
    int i = 0;
    int encontrado = 0; 
    
    while (i < agenda->cantidad_contactos && encontrado == 0) {
        
        if (strcmp(agenda->contactos[i].nombre, nombre_buscado) == 0) {
            actuazlizar_edad(&(agenda->contactos[i]));
            
            encontrado = 1; 
        } else {
            i++; 
        }
    }
    
    if (encontrado == 0) {
        printf("Contacto no hallado.\n");
    }
    
    free(nombre_buscado); 
}


void imprimir_contactos(Agenda *agenda){
    printf("\n--- LISTA DE CONTACTOS (%d) ---\n", agenda->cantidad_contactos);
    for (int x= 0;x< agenda->cantidad_contactos; x++) {
        printf("Nombre: %s | Tel: %s | Edad: %u\n", 
               agenda->contactos[x].nombre, 
               agenda->contactos[x].nro, 
               agenda->contactos[x].edad);
    }
}

double promedio(Agenda *agenda){
    if (agenda->cantidad_contactos == 0) return 0.0;

    double suma=0;
    for (int i = 0; i < agenda->cantidad_contactos; i++) {
        suma += agenda->contactos[i].edad;
    }
    return suma/agenda->cantidad_contactos;
}



int main(){
    Agenda mi_agenda;
    mi_agenda.cantidad_contactos = 0;
    
    alta_contacto(&mi_agenda);
    alta_contacto(&mi_agenda); 
    
    imprimir_contactos(&mi_agenda);
    
    printf("\nEl promedio de edad es: %.2f\n", promedio(&mi_agenda));
    
    modificar_edad(&mi_agenda);
    
    imprimir_contactos(&mi_agenda);
    
    // --- LIMPIEZA FINAL  ---
    for (int i = 0; i < mi_agenda.cantidad_contactos; i++) {
        free(mi_agenda.contactos[i].nombre);
        free(mi_agenda.contactos[i].nro);
    }
    
    return 0;}
