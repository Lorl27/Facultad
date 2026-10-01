/*
6) El siguiente programa muestra algunas cualidades de los n ́umeros NaN (Not A Number ) y
la funci on isnan de C, que indica si un flotante es NaN.

a) El programa muestra que comparar con NAN retorna siempre falso y para saber si
una operaci on dio NaN se puede usar isnan. 
Utilizando las funciones del ejercicio anterior, implemente una funci on myisnan que haga lo mismo que la funcion isnan de C.
b) Implemente otra funcion, myisnan2, que haga lo mismo pero utilizando solo una comparaci ́on y sin operaciones de bits.
c) ¿Ocurre lo mismo con +∞?
d) ¿Que pasa si se suma un valor a +∞?
*/

#include <stdio.h>
#include <math.h>

int main(void){
    float g = 0.0;
    float f = 0.0 / g;
    printf("f: %f\n", f);

    if (f == NAN) printf("Es NAN\n");
    if (isnan(f)) printf("isNaN dice que si\n");
    
    return 0;
}

//============

uint32_t significando_float(float num)   { return (*(uint32_t *)&num) & 0x7FFFFF; }
uint32_t exponente_float(float num)      { return (*(uint32_t *)&num >> 23) & 0xFF; }

//a.
int myisnan(float f){
    // Es NaN si el exponente es todo unos (0xFF) Y la fracción no es cero
    return (exponente_float(f) == 0xFF) && (significando_float(f) != 0);
}

//b.
int myisnan2(float f) return f!=f;

//c.No, si f=INFINITY, funciona perfectamente

//d. Se vuelve INF(+/-) a menos que hagamos INF-INF (obtendriamos NAN)