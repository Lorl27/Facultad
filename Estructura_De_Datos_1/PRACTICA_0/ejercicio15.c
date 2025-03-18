// 15. Considere el c ́odigo y luego explique si las expresiones, que se encuentran a continuaci ́on, son
// correctas; en caso de serlo, d ́e el valor de las mismas.
#include <stdio.h>

struct pack3 {
    int a;
};

struct pack2 {
    int b;
    struct pack3 *next;
};

struct pack1 {
    int c;
    struct pack2 *next;
};

int main(){
    struct pack1 data1 , *dataPtr;
    struct pack2 data2;
    struct pack3 data3;
    data1.c = 30;
    data2.b = 20;
    data3.a = 10;
    dataPtr = &data1;
    data1.next = &data2;
    data2.next = &data3;
    return 0;
}

// Expresion                        Correcta                Valor
// data1.c                              sí                    30
// dataPtr→c                            sí                    30
// dataPtr.c                            no
// data1.next→b                         SI                     20
//! dataPtr→next→b                       SI                     20
// dataPtr.next.b                       no
// dataPtr→next.b                       si                    20
//! (*(dataPtr→next)).b                  SI                      20
// data1.next→next→a                    SI                      10
// dataPtr→next→next.a                  no                    
//! dataPtr→next→next→a                  SI                    10
// dataPtr→next→a                       no
// dataPtr→next→next→b                  NO                   
