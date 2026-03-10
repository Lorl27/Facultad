//? Estructuras y punteros

// 12. Defina una estructura para representar puntos en el plano, y una funci ́on medio que dados dos de
// estos puntos, calcule el punto medio

#include <stdio.h>
#include <math.h>


typedef struct plano{
    float x;
    float y; 
} Plano;

Plano medio( Plano punto1,  Plano punto2){
    Plano medio;
    float x1=punto1.x;
    float x2=punto2.x;

    float y1=punto1.y;
    float y2=punto2.y;

    medio.x=(x2+x1)/2;
    medio.y=(y2+y1)/2;

    return medio;
}


int main(){
    Plano a,b,c;

    printf("Ingrese los datos (x,y) del Punto nro 1: \n");
    scanf("%f%f",&a.x,&a.y);


    printf("Ingrese los datos (x,y) del Punto nro 2: \n");
    scanf("%f%f",&b.x,&b.y);


    c = medio(a,b);

    printf("El punto medio de los Puntos: P(%.2f,%.2f) y Q(%.2f,%.2f) es: M(%.2f,%.2f)\n",a.x,a.y,b.x,b.y,c.x,c.y);

    return 0;

}