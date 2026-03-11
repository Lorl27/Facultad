
#include <stdio.h>
#define SUMARRAY(array,nro) \
    do{ \
        int suma=0; \
        for(int x=0;x<(nro);x++){suma+=array[x];}    \
        printf("La suma es:%d",suma); \
    }while(0)

int main(){
    int arr[]={1,2,3};
    SUMARRAY(arr,3);
    return 0;
}