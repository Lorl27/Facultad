//11: Analice los programas dados a continuaci ́on y, escriba todos los errores en el manejo
// de memoria que considere que se est ́an realizando, explique cu ́al ser ́ıa la salida por
// pantalla del programa

#include <stdio.h>


int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* ptr;
    ptr = array;
    printf("array[0]> %d; *ptr: %d\n", array [0], *ptr);  //1,1
    printf("array[1]> %d; *(ptr +1): %d\n", array [1], *(ptr +1)); //2-2
    ptr ++;
    printf("ptr ++; *ptr: %d\n", *ptr); //2 
    return 1;
}