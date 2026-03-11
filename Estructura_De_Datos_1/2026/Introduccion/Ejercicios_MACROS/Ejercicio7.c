
#include <stdio.h>


#define PRINTARRAY(array,nros) for(int x=0;x<nros;x++){printf("[%d]=%d\n",x,array[x]);}

//FORMA MA SEGURA
#define PRINTARRAY(array, nros) \
    do { \
        for(int x = 0; x < (nros); x++) { \
            printf("[%d]=%d\n", x, array[x]); \
        } \
    } while(0)


int main(){

    int arrar_Prueba[]={1,2,34,6};
    PRINTARRAY(arrar_Prueba,4);

    return 0;
}