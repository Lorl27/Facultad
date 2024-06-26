// Ejercicio 12. Escriba un programa que dado un número ingresado determine si el mismo es
// primo o no.

#include <stdio.h>
#include <assert.h>
#include <math.h>

int es_primo(int numero){
    if(numero<=1){return 0;}
    /*if(numero==2){return 1;} //primo
    if(numero%2==0){return 0;} // NO son primeos*/
    
    for(int x=2;x<=sqrt(numero);x++){
        if (numero%x==0){return 0;} //NO
    }
    return 1; //Si paso las verificaciones---> PRIMO
}

void test_es_primo(void) {
    assert(es_primo(2) == 1);
    assert(es_primo(3) == 1); //si
    assert(es_primo(4) == 0);
    assert(es_primo(5) == 1);
    assert(es_primo(9) == 0); //no
    assert(es_primo(13) == 1);
    assert(es_primo(1) == 0);
    assert(es_primo(0) == 0);
    assert(es_primo(-5) == 0);
}

int main(void){
    test_es_primo(); //tests

    int numero,resultado;
    printf("ingresa el numero para comprobar si es primo o no: \n");
    scanf("%d",&numero);
    resultado=es_primo(numero);

    if(resultado){printf("Es primo");}else{printf("NO es primo");}
    return 0;

}