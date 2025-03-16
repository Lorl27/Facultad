// 2. Definiendo Nuevas Estructuras

// Ejercicio 4. El Tiempo

// 1. Proponer una representación con estructuras para modelar el tiempo: hhhh:mm:ss. No impondremos
// ninguna restricción con respecto a la cantidad de horas almacenadas.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct time {
    int horas;
    int minutos;
    int segundos;
} Tiempo;

// 2. Escriba una función de creación de un elemento del tipo Tiempo, el cual tome tres datos, la hora,
// los minutos, y los segundos, y retorne un elemento de tipo Tiempo válido.

/* DISEÑO DE DATOS:
    t: elemento tipo Tiempo

    Signatura:
    Crear_Time: int int int -> Tiempo

    Próposito: Crear un elemento tipo Tiempo.
    -Si la hora es negativa, devolverá 0
    - Si los minutos/segundos no están en el rango [1-59] devolverán 0.

    EJEMPLOS:
        Crear_Time(2, 5, 7)==Tiempo{2, 5, 7}
        Crear_Time(2, 0, 60) == Tiempo{2,0,0} (debido a la validación).
        Crear_Time(-1, 61, -5)== Tiempo{0,0,0} (debido a la validación).


 */

Tiempo Crear_Time(int hora, int minuto, int segundo){
    if(minuto<0 || minuto>=60){minuto=0;}
    if(segundo<0 || segundo>=60){segundo=0;} //Validación minutos-segundos
    if(hora<0){hora=0;} // Sólo horas positivas

    Tiempo t={hora,minuto,segundo};
    return t;
}

void test_Crear_Time(void){
    Tiempo t1=Crear_Time(2,5,7);
    Tiempo t2=Crear_Time(2,0,60);
    Tiempo t3=Crear_Time(-1,61,-5);

    assert(t1.horas == 2 && t1.minutos == 5 && t1.segundos == 7);
    assert(t2.horas == 2 && t2.minutos == 0 && t2.segundos == 0);

    assert(t3.horas==0);
    assert(t3.minutos==0);
    assert(t3.segundos==0);
}
// 3. Escribir una función imprimir_Tiempo la cual recibe un dato de tipo Tiempo e imprime este con
// el siguiente formato: hh:mm:ss.

void imprimir_Tiempo(Tiempo t){
    printf("%d:%d:%d \n",t.horas,t.minutos,t.segundos);
}

// 4. Escribir una función suma_Tiempo que reciba dos tiempos dados y devuelva la suma de éstos.

/* DISEÑO DE DATOS:
    t1, t2: elementos tipo Tiempo
    sumaTotal: elemento tipo Tiempo

    Signatura:
    suma_Tiempo: Tiempo Tiempo -> Tiempo

    Próposito: Sumar dos tiempos dados y devolver el resultado

    EJEMPLOS:
        suma_Tiempo({2, 5, 7}, {1, 2, 30}) == Tiempo{3, 7, 37}
        suma_Tiempo({200, 50, 60}, {1, 20, 30}) == Tiempo{202, 1, 30}
*/

Tiempo suma_Tiempo(Tiempo t1, Tiempo t2){
    int suma_horas=0,suma_minutos=0,suma_segundos=0;

    suma_segundos=t1.segundos+t2.segundos;

    if(suma_segundos>=60){
        suma_minutos++;
        suma_segundos-=60;}

    suma_minutos=t1.minutos+t2.minutos;
    
    if(suma_minutos>=60){
        suma_horas++;
        suma_minutos-=60;}

    suma_horas=t1.horas+t2.horas;

    Tiempo sumaTotal=Crear_Time(suma_horas,suma_minutos,suma_segundos);

    return sumaTotal;

}

void test_suma_Tiempo(void){
    Tiempo t1=Crear_Time(2,5,7);
    Tiempo t2=Crear_Time(1,2,30);
    Tiempo t3=Crear_Time(200,50,60);//200-50-0
    Tiempo t4=Crear_Time(1,20,30);

    Tiempo r1_2=Crear_Time(3,7,37);
    Tiempo result1_2 = suma_Tiempo(t1, t2);

    assert(result1_2.horas == r1_2.horas);
    assert(result1_2.minutos == r1_2.minutos);
    assert(result1_2.segundos == r1_2.segundos);

    Tiempo r3_4=Crear_Time(201,10,30);
    Tiempo result3_4=suma_Tiempo(t3,t4);

    assert(r3_4.horas==result3_4.horas);
    assert(result3_4.minutos==r3_4.minutos);
    assert(result3_4.segundos==r3_4.segundos);
    
}

// 5. Escribir una función resta_Tiempo que reciba dos tiempos dados y devuelva la resta de éstos.

/* DISEÑO DE DATOS:
    t1, t2: elementos tipo Tiempo
    restaTotal: elemento tipo Tiempo

    Signatura:
    resta_Tiempo: Tiempo Tiempo -> Tiempo

    Próposito: Sumar dos tiempos dados y devolver el resultado

    EJEMPLOS:
        resta_Tiempo({2, 5, 7}, {1, 2, 30}) == Tiempo{1, 2, 27}
        resta_Tiempo({200, 50, 60}, {1, 20, 30}) == Tiempo{199, 30, 30}
*/

Tiempo resta_Tiempo(Tiempo t1, Tiempo t2){
    int resta_horas=0,resta_minutos=0,resta_segundos=0;

    resta_segundos=abs(t1.segundos-t2.segundos);
    
    resta_minutos=abs(t1.minutos-t2.minutos);
    
    resta_horas=abs(t1.horas-t2.horas);

    Tiempo restaTotal=Crear_Time(resta_horas,resta_minutos,resta_segundos);

    return restaTotal;

}

void test_resta_Tiempo(void){
    Tiempo t1=Crear_Time(2,5,7);
    Tiempo t2=Crear_Time(1,2,30);
    Tiempo t3=Crear_Time(200,50,60);
    Tiempo t4=Crear_Time(1,20,30);

    Tiempo r1_2=Crear_Time(1,3,23);
    Tiempo result1_2 = resta_Tiempo(t1, t2);

    assert(result1_2.horas == r1_2.horas);
    assert(result1_2.minutos == r1_2.minutos);
    assert(result1_2.segundos == r1_2.segundos);

    Tiempo r3_4=Crear_Time(199,30,30);
    Tiempo result3_4=resta_Tiempo(t3,t4);

    assert(r3_4.horas==result3_4.horas);
    assert(result3_4.minutos==r3_4.minutos);
    assert(result3_4.segundos==r3_4.segundos);
    
}

// 6. Escribir una función Tiempo_Dias que reciba un dato de tipo Tiempo, y devuelve la cantidad de
// días que representa. En el caso que la cantidad de horas sea menor a 24 devolverá cero, y si por
// el contrario la cantidad de horas superará los 365 días (8760 horas corresponden a un año), por
// ejemplo, si el dato ingresado fuera 8800 horas 15 min 30 seg, la función deberá retornar, entonces
// devolverá 1 año y 40 días.


/* DISEÑO DE DATOS:
    t: elemento tipo Tiempo
    years,days: int

    Signatura:
    Tiempo_Dias: Tiempo -> int

    Próposito: Devuelve la cantidad de días representada por el tiempo

    EJEMPLOS:
        Tiempo_Dias({10, 0, 0}) == 0
        Tiempo_Dias({50, 0, 0}) == 2
        Tiempo_Dias({8800, 0, 0}) == 405 (1 año y 40 dias)
*/

int Tiempo_Dias(Tiempo t){
    // Convertir todo a horas
    int total_horas = t.horas + t.minutos / 60 + t.segundos / 3600;
    
    // Si la cantidad de horas es menor a 24, devolver 0 días
    if (total_horas < 24) {
        printf("0 días..\n");
        return 0;
    }
    
    // Convertir horas a días
    int dias = total_horas / 24;
    
    // Si la cantidad de horas supera los 8760 (un año en horas), calcular años y días restantes
    if (total_horas >= 8760) {
        int anios = total_horas / 8760;
        int horas_restantes = total_horas % 8760;
        int dias_restantes = horas_restantes / 24;
        
        // Ajustar dias_restantes para incluir los dias completos y los dias parciales
        dias += dias_restantes;
        dias_restantes = 0;
        
        printf("%d año[s] y %d día[s]\n", anios, dias);
        return anios;
    }
    printf("%d día[s] \n",dias);
    return dias;
}

void test_Tiempo_Dias(void){
    Tiempo t1 = {8800, 15, 30}; ///No me dan los dias. corregir luego.
    Tiempo t2 = {23, 0, 0};
    
    // Ejemplo con assert para t1
    assert(Tiempo_Dias(t1) == 1); // Debe devolver 1 año y 40 días
    
    // Ejemplo con assert para t2
    assert(Tiempo_Dias(t2) == 0); // Debe devolver 0 días
}

//--------------------------

int main(void){
    //TESTS:
    test_Crear_Time();
    test_resta_Tiempo();
    test_suma_Tiempo();
    test_Tiempo_Dias();


    Tiempo t1,t2,sumaTotal,restaTotal;
    int horas,minutos,segundos;

    printf("Ingrese los datos para el tiempo nro 1: \n");

    printf("Ingrese la hora: \n");
    scanf("%d",&t1.horas);
    printf("Ingrese los minutos: \n");
    scanf("%d",&t1.minutos);
    printf("Ingrese los segundos: \n");
    scanf("%d",&t1.segundos);

    printf("Ingrese los datos para el tiempo nro 2: \n");
    
    printf("Ingrese la hora: \n");
    scanf("%d",&horas);
    printf("Ingrese los minutos: \n");
    scanf("%d",&minutos);
    printf("Ingrese los segundos: \n");
    scanf("%d",&segundos);

    t2=Crear_Time(horas,minutos,segundos);

    printf("T1=");
    imprimir_Tiempo(t1);
    printf("T2=");
    imprimir_Tiempo(t2);

    sumaTotal=suma_Tiempo(t1,t2);

    printf("La suma entre ambos es: %d hora[s] con %d minuto[s] y %d segundo[s] \n",sumaTotal.horas,sumaTotal.minutos,sumaTotal.segundos);

    restaTotal=resta_Tiempo(t1,t2);

    printf("La resta entre ambos es: %d hora[s] con %d minuto[s] y %d segundo[s] \n",restaTotal.horas,restaTotal.minutos,restaTotal.segundos);

    printf("El tiempo nro 1 equivale a: ");
    Tiempo_Dias(t1);

    printf("El tiempo nro 2 equivale a: ");
    Tiempo_Dias(t2);

    return 0;
}