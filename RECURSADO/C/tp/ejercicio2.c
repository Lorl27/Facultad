// Ejercicio 2. Dado el siguiente juego entre dos jugadores a los que llamaremos Ana y Beto: Ana piensa
// un número, el cual es secreto entre 0 y 500, y el mismo quedará fijo en un papel. Beto, deberá proponer
// números, para adivinar dicho valor, y en cada intento Ana responderá: “el número es mayor” o “el número
// es menor”, según corresponda. Los intentos de adividar quedan sujetos a las siguientes opciones:
// (a) Beto dispondrá como máximo de 15 intentos.
// (b) Beto jugará hasta que se canse, manifestando su voluntad en ese caso diciendo −1.
// (c) Beto retará a su oponente diciendo él mismo la cantidad de intentos que necesita para adivinar el
// número que Ana pensó.
// Se pide entonces: implemente en el lenguaje C el juego de adivinar un número secreto de Ana y Beto,
// con una de las opciones de intentos mostradas, y argumente con sus palabras, cómo resolvería las otras
// dos no implementadas modificando la versión que decidió implementar.

#include <stdio.h>
#include <assert.h>

#define MAGICO 142

/* diseño de datos:
numero:int , numero entero
signatura:
estado_del_numero:int->void
proposito: Se´gún el número ingresado, la funcion nos devolvera su relacion (menor/mayor) con el número mágico (142)
EJEMPLOS:
estado_del_numero(1)=="el número MÁGICO es mayor
estado_del_numero(-10)=="el número MÁGICO es mayor (a pesar de que el numero magico e [0,500], si beto dice uno negativo, simplemente pierde un intento x distraido.)
estado_del_numero(0)=="el número MÁGICO es mayor
estado_del_numero(142)=="" (no devuelve nada)
estado_del_numero(500)=="El número MÁGICO es menor*/
void estado_del_numero(int numero){
    if(numero<MAGICO){printf("El número MÁGICO es mayor");}

    if(numero>MAGICO){printf("El número MÁGICO es menor");}
}

//b:
/* diseño de datos:
numero:int , numero entero
signatura:
juego_de_Ana_y_Beto:int->int
proposito: La función les permité a Ana y Beto saber si el 2do adivino el número o no, y en cuántos intentos le tomo el acierto/error. 
Ana le dirá cada vez que Beto diga un número, el estado de éste en relación al número secreto.
EJEMPLOS:
INGRESO:7 8 9 -1 ; SALIDA: "El numero magico es mayor"*3 "Beto no ha podido adivinar el numero despues de 3 intento/s..."
INGRESO: 142 ; SALIDA: "¡Beto adivino el número!"
INGRESO: 500 0 3 145 3 -1; SALIDA: "El numero magico es menor" "El numero magico es mayor" "El numero magico es mayor" "El numero magico es menor" "El numero magico es mayor" "Beto no ha podido adivinar el numero despues de 5 intento/s..."
*/
int juego_de_Ana_y_Beto(){
    int numero,intentos=0;
    printf("Ana y Beto jugarán un juego de adivinanza,\n Beto deberá adivinar un número SECRETO entre 0 y 500:");
    
    
    
    do{
    printf("El número que Beto dijo es: ");
    scanf("%d",&numero);

    if(numero==-1){continue;}
estado_del_numero(numero);
intentos+=1;}while(numero!=-1 && numero!=MAGICO);

    if (numero==MAGICO){
    printf("¡Beto adivino el número!");}
    else{printf("Beto no ha podido adivinar el número después de %d intento/s...\n", intentos);}
    return 0;
}

//test:
void test_juego_de_Ana_y_Beto(void){
    // Prueba para verificar el comportamiento de la función main
    int numero, intentos = 0;

    // Simulamos la entrada del usuario
    numero = 7;
    estado_del_numero(numero); // Debería imprimir "El número MÁGICO es mayor"
    intentos++;

    numero = 8;
    estado_del_numero(numero); // Debería imprimir "El número MÁGICO es mayor"
    intentos++;

    numero = -1;
    state_del_numero(numero); // Debería saltarse esta iteración

    numero = 142;
    estado_del_numero(numero); // Debería imprimir "¡Beto adivino el número!"

    // Verificar el conteo de intentos
    assert(intentos == 3); // Solo contamos los intentos válidos
}