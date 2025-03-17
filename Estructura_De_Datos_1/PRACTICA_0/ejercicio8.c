// 8. Implemente las siguientes funciones que reciben como argumento punteros a funci ́on:
// a) int apply(int (*)(int), int) que toma un puntero a funci ́on, y un entero, y aplica la funci ́on al
// entero y retorna el valor dado.
// b) void apply in(int (*)(int), int*) que toma un puntero a funci ́on, un puntero a un entero, y
// reemplaza el entero apuntado por el valor de ejecutar la funci ́on apuntada sobre el valor apuntado.
// c) void recorre(VisitorFunc, int[], int) que toma un puntero a una funci ́on, un arreglo de enteros,
// y su longitud, y aplica la funci ́on a cada elemento del arreglo. VisitorFunc est ́a definido por
// typedef void (*VisitorFunc)(int).
// d) Pruebe las funciones anteriores pas ́andoles como par ́ametro las siguientes funciones:
// i. Para a y b:
// int sucesor (int n) {
// return n+1;
// }
// ii. Para c:
// void imprimir (int n) {
// printf("%d \n", n);
// }