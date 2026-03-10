// a)
#include <stdio.h>


void nullify(int* a){
    a = NULL;
}
int main(){
    int a[67];
    a[0] = 123;
    printf("%d\n", a[0]);   //123
    nullify(a);             //No usa punteros (debería ser *a=NULL ), entonces a no cambia nada.
    printf("%d\n", a[0]);  //123
return 0;
}
// Resultado:
// i.       123
//          Segmentation fault

// ii.      123      <--- RTA
//          123

// iii.     123
//          ∗basura∗

// iv.      Segmentation fault

// v.       Ninguna de las anteriores