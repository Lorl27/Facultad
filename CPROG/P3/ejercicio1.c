// 1. Estructuras
// Ejercicio 1. Considere la siguiente estructura que representa un punto en el plano.

#include <stdio.h>
#include <math.h>

struct punto
{
    double x;
    double y;
};

// Defina las siguientes funciones:
// //  Función proyección:
// Recibe un punto y devuelve la proyecci ó n sobre el eje
// que se pida ( ’ x ’ o ’y ’) . Cualquier otro valor debe ser
// invalidado

double proy(struct punto p, char eje)
{
    if(eje=='x'){
        return p.x;
    }
    else if(eje=='y'){
        return p.y;
    }
    else{
        return -1;
    }
}
// //  Función distancia:
// Devuelve la distancia entre los puntos recibidos

double dist ( struct punto punto1 , struct punto punto2 ) {
    return sqrt(  pow(punto2.x - punto1.x, 2) + pow(punto2.y - punto1.y, 2)  );
}
// //  Función pos:
// Devuelve ’1 ’ , ’2 ’ , ’3 ’ o ’4 ’ si el punto se encuentra
// estrictamente en un cuadrante , ’x ’ o ’y ’ si se encuentra
// en uno de los ejes u ’o ’ si es el origen de coordenadas

char pos ( struct punto p ) {
    if(p.x>0 && p.y>0){ return '1';}
    else if(p.x>0 && p.y<0){return '4';}
    else if(p.x<0 && p.y<0){return '3';}
    else if(p.x<0 && p.y>0){return '2';}
    else if(p.y==0 && p.x==0){return '0';}
    else if(p.x==0){return 'y';}
    else{return 'x';}
}

int main(){
    struct punto p={2,5};
    struct punto p1={1,8};
    struct punto punto2 = {-2, -7};
    struct punto punto3 = {0, 0};
    struct punto punto4 = {0, 5};
    struct punto punto5 = {-6, 0};
    struct punto punto6 = {7, 0};
    struct punto punto7 = {-4, 5};

    // Pruebas de proyección
    printf("Proyección en el eje x: %.2f\n", proy(p, 'x'));
    printf("Proyección en el eje y: %.2f\n", proy(p, 'y'));
    printf("Proyección en el eje z: %.2f\n", proy(p, 'z')); // Valor inválido

    //prueba de distancia:
    printf("distancia de p1 a p2 : %d\n",dist(p,p1));

    //prueba de pos:
    printf("La posicion de punto p es: %c\n",pos(p));
    printf("La posicion de punto p1 es: %c\n",pos(p1));
     printf("La posición de punto2 es: %c\n", pos(punto2)); // Cuadrante 3
    printf("La posición de punto3 es: %c\n", pos(punto3)); // Origen de coordenadas
    printf("La posición de punto4 es: %c\n", pos(punto4)); // Eje Y
    printf("La posición de punto5 es: %c\n", pos(punto5)); // Eje X
    printf("La posición de punto6 es: %c\n", pos(punto6)); // Eje X
    printf("La posición de punto7 es: %c\n", pos(punto7)); // Cuadrante 2
    return 0;
}