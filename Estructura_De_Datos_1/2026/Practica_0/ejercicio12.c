#include <stdio.h>

typedef struct {
    float x;
    float y;
} Punto ;


Punto calcular_medio(Punto punto1, Punto punto2){
    Punto medio;
    medio.x = (punto1.x + punto2.x) / 2.0;
    medio.y = (punto1.y + punto2.y) / 2.0;
    return medio;

}


int main(){
    Punto a={5,4};
    Punto b;
    b.x=4 ; b.y=10;
    Punto resultado = calcular_medio(a, b);
    
    printf("El punto medio es: (%.2f, %.2f)\n", resultado.x, resultado.y);
    return 0;
}