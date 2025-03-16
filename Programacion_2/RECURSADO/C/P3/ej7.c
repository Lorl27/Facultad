// 3. Problemas mas Complejos

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOPRAND 12 //Tope de aleatoridad.

// Ejercicio 7. Las Cartas

// 1. Proponga una representación con estructuras para las cartas de la baraja española.

// Definición de un enum para los palos de la baraja española
typedef enum palos{
    Oro,
    Copa,
    Basto,
    Espada,

} Palo;


// Definición de una estructura para una carta
typedef struct baraja_esp{
    Palo palo;
    int valor;
} Carta;

// 2. Escriba una función de creación de un elemento del tipo Carta, la cual tome dos datos, el valor y
// el palo de una carta, y retorne un elemento de tipo Carta válido.

Carta crear_Carta(int value, Palo palito){
    Carta card;
    card.palo=palito;
    card.valor=value;
    return card;
}

// 3. Escriba una función barajar la cual no recibe argumentos, pero entrega una carta válida de la baraja
// española. Utilizar alguna función de aleatoriedad para asignar el número y el palo de la carta.

Carta entregar_Carta(void){

    Carta c;

    int valor_r=rand()%TOPRAND +1; //evitamos c=0. RANGO [1-12]

    Palo palos[] = {Oro, Copa, Basto, Espada};
    Palo palo_r = palos[rand() % 4]; // Seleccionar un palo aleatorio

    return crear_Carta(valor_r,palo_r);
}

// 4. Escriba las siguientes funciones:

// es_igualPalo: Carta → Carta → Int, la cual determina si dos cartas tienen igual palo.

int es_igualPalo(Carta c1,Carta c2){
    return (c1.palo==c2.palo);
}

// es_igualNumero: Carta → Carta → Int, la cual determina si dos cartas tienen el mismo
// número.

int es_igualNumero(Carta c1,Carta c2){
    return (c1.valor==c2.valor);
}

// es_igual, : Carta → Carta → Int, la cual determina si dos cartas son iguales o no.

int es_igual(Carta c1, Carta c2){
    return (es_igualPalo(c1,c2) && es_igualNumero(c1,c2));
}

// es_full: Carta → Carta → Cartas → Cartas → Int, determina si las cartas pasadas forman
// un full, dos pares de cartas de igual número y distinto palo. Utilizar las funciones anteriormente
// definidas.

int es_full(Carta c1,Carta c2,Carta c3,Carta c4){
    return((!es_igualPalo(c1,c2) && es_igualNumero(c1,c2)) || (!es_igualPalo(c1,c3) && es_igualNumero(c1,c3)) || (!es_igualPalo(c1,c4) && es_igualNumero(c1,c4)) || (!es_igualPalo(c2,c3) && es_igualNumero(c2,c3)) || (!es_igualPalo(c4,c2) && es_igualNumero(c4,c2)) || (!es_igualPalo(c3,c4) && es_igualNumero(c3,c4)) );
}

// es_poker: Carta → Carta → Cartas → Cartas → Int, determina si las cartas pasadas
// forman un poker, igual número distinto palo. Utilizar las funciones anteriormente definidas.

int es_poker(Carta c1,Carta c2,Carta c3,Carta c4){
    return((es_igualPalo(c1,c2) && !es_igualNumero(c1,c2)) || (es_igualPalo(c1,c3) && !es_igualNumero(c1,c3)) || (es_igualPalo(c1,c4) && !es_igualNumero(c1,c4)) || (es_igualPalo(c2,c3) && !es_igualNumero(c2,c3)) || (es_igualPalo(c4,c2) && !es_igualNumero(c4,c2)) || (es_igualPalo(c3,c4) && !es_igualNumero(c3,c4)) );
}

// es_escalera: Carta → Carta → Cartas → Int, la cual determina si las cartas pasadas como
// argumento forman una:
    // • escalera verdadera: números consecutivos e igual palo. El orden de las cartas, para un
    // mazo de 48 cartas, es: 1, 2, 3, 4, 5, 6, 7, 8, 9, sota, caballo, rey.
    // • escalera falsa: números consecutivos pero distinto palo;
    // • escalera real: números consecutivos e igual palo, pero admite circularidad: luego del rey
    // puede seguir el 1, y así sucesivamente, formando así una escalera, como por ejemplo, con
    // la siguiente tirada de cartas: rey-1-2, o caballo, rey, 1, etc.

int es_escalera(Carta c1, Carta c2, Carta c3){

    //REVISIÓN ESCALERA VERDADERA:-------------
    if (es_igualPalo(c1, c2) && es_igualPalo(c1, c3)) {
        int max = c1.valor > c2.valor ? (c1.valor > c3.valor ? c1.valor : c3.valor) : (c2.valor > c3.valor ? c2.valor : c3.valor);
        int min = c1.valor < c2.valor ? (c1.valor < c3.valor ? c1.valor : c3.valor) : (c2.valor < c3.valor ? c2.valor : c3.valor);
        int mid = c1.valor + c2.valor + c3.valor - max - min;

        if (max == mid + 1 && mid == min + 1) {
            return 1; // Escalera verdadera
        }
    }

    //REVISIÓN ESCALERA FALSA:-------------
    if (!es_igualPalo(c1, c2) || !es_igualPalo(c1, c3) || !es_igualPalo(c2,c3)) {
        int max = c1.valor > c2.valor ? (c1.valor > c3.valor ? c1.valor : c3.valor) : (c2.valor > c3.valor ? c2.valor : c3.valor);
        int min = c1.valor < c2.valor ? (c1.valor < c3.valor ? c1.valor : c3.valor) : (c2.valor < c3.valor ? c2.valor : c3.valor);
        int mid = c1.valor + c2.valor + c3.valor - max - min;

        if (max == mid + 1 && mid == min + 1) {
            return 2; // Escalera Falsa
        }
    }

    //REVISIÓN ESCALERA REAL:-------------
    if (es_igualPalo(c1, c2) && es_igualPalo(c1, c3)) {
        int valores[] = {c1.valor, c2.valor, c3.valor};
        
        if ((valores[0] == 12 && valores[1] == 1 && valores[2] == 2) ||
            (valores[0] == 12 && valores[1] == 11 && valores[2] == 1) ||
            (valores[0] == 11 && valores[1] == 12 && valores[2] == 1)) {
            return 3; // Escalera real
        }
    }

    return 0; //NO es una escalera de ningún tipo.
}

// 5. Escriba un programa que luego de barajar, y obtener tres cartas aleatoriamente, determine que
// forman las mismas, empleando las funciones anteriormente definidas. Luego muestre por pantalla
// lo obtenido y clasificado, y por último que ofrezca al usuario la posibilidad de volver a barajar, o
// terminar. No llevamos ningún tipo de registro de cartas que salieron, cuando decimos barajar, nos
// referimos a obtener una carta aleatoriamente. ¿Como implementaría además un sistema de puntaje
// para este juego?


//---------

void imprimir_Carta(Carta c){
    char *palos[]={"Oro","Copa","Basto","Espada"};
    printf("Carta: %d de %s\n", c.valor, palos[c.palo]);
}

//-----

void barajar(){
    int opcion;
    int puntaje = 0;

    do {
        // Barajar y obtener tres cartas aleatorias
        Carta carta1 = entregar_Carta();
        Carta carta2 = entregar_Carta();
        Carta carta3 = entregar_Carta();
        Carta carta4 = entregar_Carta();

        // Mostrar las cartas obtenidas
        printf("Carta 1: ");
        imprimir_Carta(carta1);
        printf("Carta 2: ");
        imprimir_Carta(carta2);
        printf("Carta 3: ");
        imprimir_Carta(carta3);
        printf("Carta 4: ");
        imprimir_Carta(carta4);

        // Determinar la combinación de cartas
        if (es_full(carta1, carta2, carta3,carta4)) {
            printf("Tienes un Full!\n");
            puntaje += 10; // Asignar puntaje para un Full
        } else if (es_poker(carta1, carta2, carta3,carta4)) {
            printf("Tienes un Poker!\n");
            puntaje += 15; // Asignar puntaje para un Poker
        } else if (es_escalera(carta1, carta2, carta3)) {
            printf("Tienes una Escalera!\n");
            puntaje += 8; // Asignar puntaje para una Escalera
        } else {
            printf("No tienes ninguna combinación especial.\n");
        }

        // Mostrar el puntaje acumulado
        printf("Puntaje actual: %d\n", puntaje);

        // Preguntar al usuario si desea volver a barajar
        printf("¿Quieres volver a barajar? (1 = Sí, 0 = No): ");
        scanf("%d", &opcion);

        // Limpiar el buffer del teclado
        while (getchar() != '\n');

    } while (opcion != 0);

    printf("Juego terminado. Puntaje final: %d\n", puntaje);
}

//----------------

int main(void) {
    srand(time(NULL)); //aleatoriedad

    barajar(); // Iniciar el juego de cartas
    return 0;
}