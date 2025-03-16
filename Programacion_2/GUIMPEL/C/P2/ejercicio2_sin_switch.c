// Ejercicio 2: En la siguiente tabla se muestra el número de camas de las habitaciones de una
// casa de campo y la planta donde está ubicada cada una de ellas:
    // 1.azul , 2 camas, planta 1
    // 2. roja, 1 cama, planta 1
    // 3. verde , 3 cama, planta 2
    // 4. rosa, 2 camas, planta 2
    // 5. gris, 1 cama, planta 1
// Se pide que escriba un programa que:
// 1. Muestre el listado de las habitaciones de la casa de campo.
// 2. Pida por teclado el número (dato entero) asociado a una habitación.
// 3. Muestre por pantalla la planta y el número de camas de la habitación seleccionada.
// Observación: Si el número introducido por el usuario, no está asociado a ninguna habitación,se mostrará el mensaje: "Número no asociado a habitación."

#include <stdio.h>

//NOTE - Intentar sin switch !

#define HABS_TOT 5

void imprimir_habs(int habitaciones[HABS_TOT][3]){
    printf("Listado de las habitaciones disponibles: \n\n");

    for(int x=0;x<HABS_TOT;x++){ //recorre todas las habitaciones
        printf("Habitacion nro %d , ubicada en la planta: %d , cuenta con %d cama(s).\n",habitaciones[x][0],habitaciones[x][2], habitaciones[x][1]);
    }
}

void mostrar_hab_elegida(int habitaciones[HABS_TOT][3],int nro_hab){
    for(int x=0;x<HABS_TOT;x++){
        if(habitaciones[x][0]==nro_hab){
            printf("Habitación nro: %d , en planta: %d , con cama(s): %d", nro_hab,habitaciones[x][2],habitaciones[x][1] );
            return; //Hab ya encontrada
        }
    }

}

int main(){
    int habitaciones[HABS_TOT][3]={
        {1,2,1}, //habitacion 1, camas 2, planta 1
        {2,1,1},
        {3,3,2},
        {4,2,2},
        {5,1,3}
    }, hab_elegida=0;

    imprimir_habs(habitaciones);
    printf("Elige la habitación que desees: \n");
    scanf("%d",&hab_elegida);

    if(hab_elegida<1 || hab_elegida>HABS_TOT){ 
        printf("Nro no asociado a ninguna habitación");
        return 1;
    }

    mostrar_hab_elegida(habitaciones,hab_elegida);

    return 0;
}