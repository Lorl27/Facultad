// Ejercicio 1. Definir una función llamada esTriRectangulo que tome tres enteros y devuelva 1 
//si los números que se le pasan pueden ser los lados de un triángulo rectángulo, y 0 en caso contrario.
// Sugerencia:
// Una manera validar que se trata de un triángulo rectángulo sería verificar si el cuadrado del lado
// mayor es igual la suma de los cuadrados de los otros dos lados.

// Sin embargo existe otra manera utilizando sólo una vez la función max3, que devuelve el máximo
// entre tres enteros dados.

// Se pide entonces: definir ambas versiones de la función esTriRectangulo funciones que determinan si un
// triángulo es rectángulo y testear el código de las mismas con las entradas (3, 5, 4), (5, 13, 12) y (7, 3, 5)

#include <stdio.h>
#include <assert.h>
#include <math.h>

/*DISEÑO DE DATOS:
lado:int , número entero

signatura:
verificar_lado:int-> int
próposito: Devuelve 1 si el número ingresado es dde un formato válido para un lado de un triángulo y, 0 en caso xontrario.
EJEMPLOS:
verificar_lado(3) == 1
verificar_lado(-9) == 0
verificar_lado(0) == 0 */ 
int verificar_lado(int lado){
    return lado>0;
}
//TEST:
void test_verificar_lado() {
    assert(verificar_lado(3) == 1);
    assert(verificar_lado(-9) == 0);
    assert(verificar_lado(0) == 0);
}



/*DISEÑO DE DATOS:
a:int , número entero
b:int, número entero

signatura:
max:int int -> int
próposito: Devuelve el número máximo de 2 enteros
EJEMPLOS:
max(3,5)==5
max(5,12)==12 */ 
int max(int a,int b){
    return (a > b) ? a : b;}

//TEST:
void test_max() {
    assert(max(3, 5) == 5);
    assert(max(5, 12) == 12);
}

/*DISEÑO DE DATOS:
a:int , número entero
b:int, número entero
c:int, número entero

signatura:
max3:int int  int-> int
próposito: Devuelve el número máximo de 3 enteros
EJEMPLOS:
max(5,4,7)==7
max(1,6,2)==6
max(50,4,0)==50 */ 
int max3(int a, int b, int c){
    return max(max(a, b), c);
}

//TEST:
void test_max3() {
    assert(max3(5, 4,7) == 7);
    assert(max3(1,6, 2) == 6);
    assert(max3(50,4, 0) == 50);
}

/*DISEÑO DE DATOS:
a:int , número entero
b:int, número entero
c:int, número entero

signatura:
esTriRectangulo:int int int-> int
próposito: Devuelve 1 si la tupla(a,b,c) conforma a un triángulo rectángulo y 0, en caso contrario.
EJEMPLOS:
esTriRectangulo_FORMA1(3, 5, 4) == 1
esTriRectangulo_FORMA1(5, 12, 13) == 1
esTriRectangulo_FORMA1(3, 5, 7) == 0 */ 
int esTriRectangulo_FORMA1(int a, int b, int c){ //si es true, retorna 1.
    if (a>b && a>c){ 
        return pow(a,2)==pow(b,2)+pow(c,2);
    }
    else if (b>a && b>c){
        return pow(b,2)==pow(a,2)+pow(c,2);
    }
    else{
        return pow(c,2)==pow(b,2)+pow(a,2);
    }
}

int esTriRectangulo_FORMA2(int a,int b,int c){
    int mayor = max3(a, b, c);
    if (mayor == a) {
        return pow(a, 2) == pow(b, 2) + pow(c, 2);
    } else if (mayor == b) {
        return pow(b, 2) == pow(a, 2) + pow(c, 2);
    } else {
        return pow(c, 2) == pow(b, 2) + pow(a, 2);
    }
}

//TEST:
void test_esTriRectangulo() {
    assert(esTriRectangulo_FORMA1(3, 5, 4) == 1);//1=si ; 0=no
    assert(esTriRectangulo_FORMA1(5, 12, 13) == 1);
    assert(esTriRectangulo_FORMA1(3, 5, 7) == 0);
    assert(esTriRectangulo_FORMA2(3, 5, 4) == 1);
    assert(esTriRectangulo_FORMA2(5, 12, 13) == 1);
    assert(esTriRectangulo_FORMA2(3, 5, 7) == 0);
}


int main(void){
    int numero1,numero2,numero3;
    printf("La siguiente función le permitirá conocer si 3 lados dados, conforman a un triángulo entero \n");
    printf("Ingresé los lados:");
    scanf("%d%d%d",&numero1,&numero2,&numero3);

    if(verificar_lado(numero1)&&verificar_lado(numero2)&&verificar_lado(numero3)){//verificación de que son positivos

        if (esTriRectangulo_FORMA1(numero1,numero2,numero3)){
            printf("Es un triángulo rectángulo");}
        else{printf("NO lo es.");}
        
        if (esTriRectangulo_FORMA2(numero1,numero2,numero3)){
            printf("Es un triángulo rectángulo");}
        else{printf("NO lo es.");}
    }else{printf("Los lados no son enteros. ERROR");} //mensaje de error.

    test_esTriRectangulo(); //para testear.
    return 0;
}



