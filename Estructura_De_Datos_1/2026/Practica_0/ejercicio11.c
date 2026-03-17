#include <stdio.h>

void nullify(int *a)
{
    a = NULL;
}

int main_a()
{
    int a[67];
    a[0] = 123; //123,.... basura
    printf("%d\n", a[0]);  //123
    nullify(a);  //SOLO afecto localmente
    printf("%d\n", a[0]);  //123
    return 0;
}

/* Para que nullify afecte:
void nullify(int **a) { *a = NULL; } y llamarla con nullify(&a)
*/

//===============0

int main_b()
{
    char *ptr = "hola mundo";
    ptr[0] = 's'; 
    printf("%s\n", ptr);  //segmention fault. no hicimos malloc no podemos modificar memoria de lectura!
    return 0;
}


//===== AMIN ===

int main()
{
    int eleccion;
    printf("elija el main entre 1:a-7:g\n");
    scanf("%d", &eleccion);
    switch (eleccion)
    {
    case 1:
        main_a();
        break;
    case 2:
        main_b();
        break;
    
    default:
        printf("nro incorrecto.\n");
        break;
    }
}