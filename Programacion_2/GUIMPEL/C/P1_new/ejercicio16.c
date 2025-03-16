// Ejercicio 16: Tres números positivos pueden ser la medida de los lados de un triángulo si y sólo si el mayor de ellos es menor que la suma de los otros dos.
// Escribir y probar una función ladosTriangulo que devuelva 1 si los tres números que se le pasan verifican esta condición, y 0 en caso contrario

#include <stdio.h>

int max_2(int a, int b){
    return a>b?a:b;
}

int max_3(int a,int b, int c){
    return max_2(max_2(a,b),c);
}

int ladosTriangulo(int a, int b, int c){
    if(max_3(a,b,c)==a){ return a<(b+c);}
    else if(max_3(a,b,c)==b){ return b<(a+c);}
    else{ return c<(a+b);}
}

int verificar_entrada(int a){
    return a>0;
}

int main(){
    int n1,n2,n3,rta;
    printf("Ingrse 3 nros positivos: \n");
    scanf("%d%d%d",&n1,&n2,&n3);
    if(!verificar_entrada(n1) ||!verificar_entrada(n2) || !verificar_entrada(n3)){
        printf("ERROR. Deben ser positivos");
        return 1;
    }

    rta=ladosTriangulo(n1,n2,n3);

    if(!rta){
        printf("No es un triángulo");
    }
    else{
        printf("Es un triángulo!");
    }

    return 0;
}
