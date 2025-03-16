// Ejercicio 2. En la siguiente tabla se muestra el número de camas de las habitaciones de una
// casa de campo y la planta donde está ubicada cada una de ellas:
// Se pide que escriba un programa que:
// 1. Muestre el listado de las habitaciones de la casa de campo.
// 2. Pida por teclado el número (dato entero) asociado a una habitación.
// 3. Muestre por pantalla la planta y el número de camas de la habitación seleccionada.
// Observación: Si el número introducido por el usuario, no está asociado a ninguna habitación,
// se mostrará el mensaje: "Número no asociado a habitación.".

#include <stdio.h>

void manejoCasaDeCampo(int habitacion){
    switch(habitacion){
        case 1:
            printf("Primera Planta. 2 camas.");
            break;
        case 2:
            printf("Primera Planta. 1 cama.");
            break;
        case 3:
            printf("Segunda Planta. 3 camas.");
            break;
        case 4:
            printf("Segunda Planta. 2 camas.");
            break;
        case 5:
            printf("Tercera Planta. 1 cama.");
            break;
        default:
                printf("Número no asociado a ninguna habitación");
                break;                
    }
}

int main(void){
    int num_hab;
    printf("Las habitaciones disponibles son: \n");
    printf("1. Azul \n 2.Roja \n 3.Verde \n 4.Rosa \n 5.Gris\n"); 

    printf("Ingrese cuál habitacion prefiere: ");
    scanf("%d",&num_hab);

    manejoCasaDeCampo(num_hab);

    return 0;
}