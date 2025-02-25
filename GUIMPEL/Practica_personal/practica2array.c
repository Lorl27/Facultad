#include <stdio.h>
#include <stdlib.h>

int main(){
    int array[10];
    printf("Ingrese el contenido del array:\n");
    int max=0;
    
    int largo=sizeof(array)/sizeof(array[0]);

    for(int x=0;x<largo;x++){
        printf("Ingrese el contenido del nro: %d\n", x+1);
        scanf("%d",&array[x]);
        if (array[x]>max){
            max=array[x];
        }
    }
    printf("\n\nel nro max es: %d",max);
    return 0;
}