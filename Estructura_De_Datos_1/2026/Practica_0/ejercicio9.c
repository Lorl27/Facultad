#include <stdio.h>

int main_a()
{
    int *punt;
    int x = 7, y = 5;
    punt = &x;
    *punt = 4;
    printf("%d %d", x, y);
    return 0;
}


/* La salida serà 4,5. 
Ya que el puntero se asigno a la dir de memoria de la var x,
y  luego modificamos esa memoria para que su contenido valga 4.*/

//===============

int main_b()
{
    int *punt;
    int x = 7, y = 5;
    punt = &x;
    x = 4;
    punt = &y;
    printf("%d %d", *punt, x);
    return 0;
}

/* La salida serà 5,4
Porque el puntero cambia de apuntar a  x, a apuntar a y.
La modificacion de x=4 no interviene el puntero.*/

//============

int main_c()
{
    int *punt, i;
    int x[] = {1, 2, 3, 4, 5};
    punt = x;
    *punt = 9;
    for (i = 0; i < 5; i++)
        printf("%d, ", x[i]);
    return 0;
}

/* La salida sera 9,2,3,4,5
Ya que como el puntero apunta a la primer dir del array (internamente),
al hacer *punt=9 es como decir array[0]=9.*/

//=============
int main_d()
{
    int *punt, i;
    int x[5] = {1, 2, 3, 4, 5};
    punt = &x[0] + 3;  //a donde apunta: x[3]=4
    *(punt - 2) = 9;  //a donde modifiqa x[3-2=1]=x[1]=9 (era 2 antes)
    punt--; //a donde apunta: x[2]=3
    *(punt) = 7;  //modifico alli, x[2]=7
    punt[1] = 11;  //es como decir: *(punt +1)=x[3]=11
    punt = x;  // vuelvo a apuntar al inicio 
    for (i = 0; i < 5; i++)
        printf("%d, ", punt[i]);
    return 0;
}

/* La salida sera  1,9,7,11,5*/

//==============
void aumentar_punteros(int *x, int *y, int z)
{
    *x = *x + 2;
    *y = *y + 5;
    z = z + 4;
}

int main_e()
{
    int x, y, z;
    x = 3;
    y = 10;
    z = 15;
    aumentar_punteros(&x, &y, z);
    printf("%d %d %d", x, y, z);
    return 0;
}

/* La salida sera 5,15,15 .
Ya que las variables pasadas con dir de memoria, actuan como punteros y
permiten modificar su contenido en memoria mientras que, la z por ejemplo, solamnete
se va a modificar dentro de la funcion localmente.*/

//===============

int *direccion_local(int x)
{
    return &x;
}

int main_f()
{
    int *ptr = NULL;
    ptr = direccion_local(2);
    printf("%d\n", *ptr);
    return 0;
}

/* Esto dara ERROR. No podes asignar una direccion LOCAL a un puntero
La referencia se eliminara apenas termine la funcion. DANGLING POINTER*/

//============

int main_g()
{
    char textoA[30] = "Agarrate Catalina";
    char textoB[30] = "El Cuarteto de Nos";
    char *p = textoA;
    char *q = textoB;
    printf("textoA: %s\ntextoB: %s\n", textoA, textoB);
    while (*p++ = *q++)
        ;
    printf("while (*p++ = *q++);\n");
    printf("textoA: %s\ntextoB: %s\n", textoA, textoB);
    return 0;
}


/* primera salida: 'Agarrate Catalina' , 'El Cuarteto de Nos'
Luego, el while provoca que vayan aumentando las lugares donde apuntan los punteros, mientras que asigna a cada uno apuntando al mismo valor (=)
Es decir, toma el caracter al que apunta q, y lo copia en el que apunta p
Provocando que la sda salida sea: 'El Cuarteto de Nos,'El Cuarteto de Nos'
*/


//======= MAIN ===================

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
    case 3:
        main_c();
        break;
    case 4:
        main_d();
        break;
    case 5:
        main_e();
        break;
    case 6:
        main_f();
        break;
    case 7:
        main_g();
        break;

    default:
        printf("nro incorrecto.\n");
        break;
    }
}