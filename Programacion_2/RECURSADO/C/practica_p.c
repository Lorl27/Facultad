#include <stdio.h>

int main(void){

    int cosas[]={1,2,4,6,8,6};
    int longitud=sizeof(cosas)/sizeof(cosas[0]);


    if (longitud == 0) {
        printf("El arreglo está vacío.\n");
        return 1;
    }

    int max=cosas[0];
    int men=cosas[0];
    
    for(int x=0;x<longitud;x++){
        if(cosas[x]>max){
            max=cosas[x];
        }
        if(cosas[x]<men){
            men=cosas[x];
        }
    }

    printf("Valor máximo: %d\n", max);
    printf("Valor mínimo: %d\n", men);

    for(int x=0;x<longitud;x++){
        printf("%d \n",cosas[x]);
    }

    return 0;
}