#include <stdio.h>

int main()
{
    int var1;
    int var2 = 5;
    char var3;
    char arr[13];

    printf("var1:%p\n", &var1);
    printf("var2:%p\n", &var2);
    printf("var3:%p\n", &var3);
    
    printf("\n--- Verificando memoria contigua en el arreglo ---\n");
    printf("Direccion base de arr: %p\n", (void*)arr); 
    
    for(int i = 0; i < 5; i++) {
        printf("Direccion de arr[%d]: %p\n", i, (void*)&arr[i]);
    }

    return 0;

}