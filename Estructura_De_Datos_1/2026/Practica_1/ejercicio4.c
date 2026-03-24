#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *direccion;
    int capacidad;
} ArregloEnteros;

void arreglo_enteros_ajustar(ArregloEnteros *arreglo, int capacidad)
{
    if (arreglo != NULL && capacidad > 0)
    {
        int *nueva_direccion = realloc(arreglo->direccion, sizeof(int) * capacidad);
        if (nueva_direccion != NULL)
        {
            arreglo->direccion = nueva_direccion;
            arreglo->capacidad = capacidad;
        }
    }
}

void arreglo_enteros_insertar(ArregloEnteros *arreglo, int pos, int dato)
{
    if (arreglo != NULL && pos >= 0 && pos <= arreglo->capacidad)
    {
        arreglo_enteros_ajustar(arreglo, arreglo->capacidad + 1);
        //  Mudanza de atrás para adelante (d a i)
        // Empezamos en la ÚLTIMA posición disponible (capacidad - 1)
        // Y retrocedemos hasta llegar a la posición donde queremos insertar
        for (int i = arreglo->capacidad - 1; i > pos; i--)
        {
            arreglo->direccion[i] = arreglo->direccion[i - 1]; // Movemos a la derecha
        }
        arreglo->direccion[pos] = dato;
    }
}

void arreglo_enteros_eliminar(ArregloEnteros *arreglo, int pos)
{
    if (arreglo != NULL && pos >= 0 && pos < arreglo->capacidad)
    {

        /// LA MUDANZA (De izquierda a derecha)
        // Nos paramos en el hueco que queremos tapar (pos)
        // Y traemos al vecino de la derecha (x + 1) hacia nosotros (x)
        for (int x = pos; x < arreglo->capacidad - 1; x++)
        {
            arreglo->direccion[x] = arreglo->direccion[x + 1];
        }

        arreglo_enteros_ajustar(arreglo, arreglo->capacidad - 1);
    }
}

void arreglo_enteros_imprimir(ArregloEnteros *arreglo)
{
    if (arreglo == NULL)
        return;
    printf("[ ");
    for (int i = 0; i < arreglo->capacidad; i++)
    {
        printf("%d ", arreglo->direccion[i]);
    }
    printf("]\n");
}

int main()
{
    // Crear arreglo inicial con capacidad 5
    ArregloEnteros *arr = malloc(sizeof(ArregloEnteros));
    arr->direccion = malloc(sizeof(int) * 5);
    arr->capacidad = 5;

    // Inicializar con valores
    for (int i = 0; i < arr->capacidad; i++)
    {
        arr->direccion[i] = i + 1; // 1,2,3,4,5
    }

    printf("Arreglo inicial: ");
    arreglo_enteros_imprimir(arr);

    // Insertar un valor en posición 2
    arreglo_enteros_insertar(arr, 2, 99);
    printf("Después de insertar 99 en posición 2: ");
    arreglo_enteros_imprimir(arr);

    // Insertar al final
    arreglo_enteros_insertar(arr, arr->capacidad, 77);
    printf("Después de insertar 77 al final: ");
    arreglo_enteros_imprimir(arr);

    // Eliminar posición 3
    arreglo_enteros_eliminar(arr, 3);
    printf("Después de eliminar posición 3: ");
    arreglo_enteros_imprimir(arr);

    // Eliminar primera posición
    arreglo_enteros_eliminar(arr, 0);
    printf("Después de eliminar primera posición: ");
    arreglo_enteros_imprimir(arr);

    // Liberar memoria
    free(arr->direccion);
    free(arr);

    return 0;
}