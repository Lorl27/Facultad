// d) 
#include <stdio.h>

int main() {
    int *punt , i;
    int x[5] = {1, 2, 3, 4, 5};
    punt = &x[0] + 3;  //ahora el puntero empieza en el nro 3, (elem: 4)
    *(punt - 2) = 9;  //nos vamos 2 atrás(SOLO PARA CAMBIAR),nro 1 (elem:2) y ahora lo cambiamos a 9  (1-9-3-4-5)
    punt --;  //retrocedemos uno: 3-1=2  nro 2
    *(punt) = 7;  // 1-9-7-4-5
    punt [1] = 11;  //, el punt[0] es 2(7) y punt[1]=2+1=3 (4-->11)  1-9-7-11-5   
    punt = x;  //reiniciamos al pricipio del bucle
    for(i = 0; i < 5; i++)
    printf("%d, ", punt[i]);
    return 0;
}