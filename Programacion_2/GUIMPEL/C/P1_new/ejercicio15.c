//? 4. Funciones
// Ejercicio 15: Escribir una función maximo que tome como parámetro dos enteros y devuelva el máximo entre ellos. Utilizar esa función para calcular el máximo entre 4 enteros que se le soliciten al usuario.

#include <stdio.h>

int max_2(int a, int b){
    return a>b?a:b;
}

int max_4(int a,int b, int c, int d){
    return max_2(max_2(a,b),max_2(c,d));
}

int main(){
    int n1,n2,n3,n4,rta;

    printf("Ingrese 4 nros,  y te diremos el mayor de ellos: \n");
    scanf("%d%d%d%d",&n1,&n2,&n3,&n4);

    rta=max_4(n1,n2,n3,n4);

    printf("El mayor entre %d\t%d\t%d\t%d\t es: %d\n",n1,n2,n3,n4,rta);

    return 0;
}