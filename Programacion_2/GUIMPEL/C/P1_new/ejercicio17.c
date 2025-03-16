// Ejercicio 17: Definir una función esRectangulo que tome tres enteros y devuelva 1 si los números que se le pasan pueden ser los lados de un triángulo rectángulo, y 0 en caso contrario. 
// Sugerencia: una manera sería verificar si el cuadrado del mayor es igual la suma de los cuadrados de los otros dos. Sin embargo existe otra manera utilizando solo una vez una fun-ción max3, que devuelve el máximo entre tres enteros dados. 
// Definir ambas funciones y probaresRectangulo con las entradas (3,5,4), (5,13,12) y (7,3,5).

#include <stdio.h>

int max_2(int a, int b){
    return a>b?a:b;
}

int max_3(int a,int b, int c){
    return max_2(max_2(a,b),c);
}

int esRectangulo(int a, int b, int c){
    if(max_3(a,b,c)==a){ return a*a == b*b + c*c ;}
    else if(max_3(a,b,c)==b){ return b*b == a*a + c*c ;}
    else{return c*c == a*a + b*b ;}
}

int main(){
    int n1,n2,n3,rta;
    printf("Ingrse 3 nros positivos: \n");
    scanf("%d%d%d",&n1,&n2,&n3);
    
    rta=esRectangulo(n1,n2,n3);

    if(!rta){
        printf("No es un rectangulo");
    }
    else{
        printf("Es un rectángulo!");
    }

    return 0;
}