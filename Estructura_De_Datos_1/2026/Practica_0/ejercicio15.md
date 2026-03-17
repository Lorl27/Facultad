```c
#include <stdio.h>
struct pack3
{
    int a;
};
struct pack2
{
    int b;
    struct pack3 *next;
};
struct pack1
{
    int c;
    struct pack2 *next;
};
int main()
{
    struct pack1 data1, *dataPtr;
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
```



| Expression | Status | Value/Note |
|---|---|---|
| `data1.c` | CORRECTA | 30 |
| `dataPtr→c` | CORRECTA | 30 |
| `dataPtr.c` | INCORRECTA | `dataPtr` es pointer, no struct |
| `data1.next→b` | CORRECTA | 20 |
| `dataPtr→next→b` | CORRECTA | 20 |
| `dataPtr.next.b` | INCORRECTA | `dataPtr` es pointer |
| `dataPtr→next.b` | INCORRECTA | `dataPtr→next` es pointer |
| `(*(dataPtr→next)).b` | CORRECTA | 20 |
| `data1.next→next→a` | CORRECTA | 10 |
| `dataPtr→next→next→a` | CORRECTA | 10 |
| `dataPtr→next→next.a` | INCORRECTA | `dataPtr→next→next` es pointer |
| `dataPtr→next→a` | INCORRECTA | `data2` no tiene `a` |
| `dataPtr→next→next→b` | INCORRECTA | `data3` no tiene `b` |
