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

//a/b.
int myisnan(float f){
    return f==NAN;
}

//c. No, serìa INF a menos que sea INF-INF  ò 0XINF que son NAN

//d. Se vuelve INF(+/-)