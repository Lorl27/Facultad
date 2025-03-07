// 15: Considere el c ́odigo y luego explique si las expresiones, que se encuentran a continua-
// ci ́on, son correctas; en caso de serlo, d ́e el valor de las mismas.

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
    return 1;
}


// Expresion                           Correcta                                                                                     Valor    
// data1.c                              si                                                                                            30
// dataPtr->c                           si                                                                                            30
// dataPtr.c                            no (deberia ser *(dataPtr).c)
// data1.next->b                        si                                                                                            20
// dataPtr.next->b                      no, dataPtr apunta a struct pack1, no tiene next
// dataPtr.next.b                       no, no tiene acceso a next (mismo error que arriba)
// dataPtr->next.b                      no , como dataPtr->next apunta a struct pack 2, deberia ser dataPtr->next->b
// (*(dataPtr->next)).b                 si                                                                                             20
// data1.next->next->a                  si    (data1.next apunta a data2, data2.next apunta a data3, y data3.a es 10.)                 10
// dataPtr->next->next.a                no, a pertenece a *data 3, deberia ser como arriba.
// dataPtr->next->next->a               si                                                                                             10
// dataPtr->next->a                     no, a no pertenece a data 3.
// dataPtr->next->next->b               no, b no pertenece a data 3.                     



// DIAGRAMA:
// data1 (pack1)
//   ├── c = 30
//   ├── next → data2 (pack2)
//             ├── b = 20
//             ├── next → data3 (pack3)
//                       ├── a = 10
