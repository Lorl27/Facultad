# INFO
Uso de Valgrind y GDB (GNU Debugger)  

Convenciòn de còdigos.  

Tambièn , un repaso de las MACROS.  

### Ejemplo Constantes y Macros:

```c

#define PI 3.14159
#define NUM_ELEM 5

#define AREA(rad) PI*(rad)*(rad)
#define MAX(a,b) ((a)>(b)?(a):(b))

int main()
{
    int i;
    float vec[NUM_ELEM];
    for(i=0;i<NUM_ELEM;i++)
        vec[i]=MAX(i*5.2,AREA(i));
}
```

## Macros tìpicas:
__DATE__ Da fecha actual en formato "MMM DD YYYY"  

__TIME__ Da hora actual en formato "HH:MM:SS"  

__FILE__ Da nombre de archivo actual  

__LINE__ Da número de línea actual

## Inclusiòn de Librerìas - Archivos:

```c
#include <stdio.h> //Cabeceras del sistema.
#include “mis_func.h” //Ficheros de cabecera locales.
```

### Ejemplo de Rand():

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    
    // Número aleatorio entre 1 y 100
    int numero = rand() % 100 + 1;
    printf("Número aleatorio: %d\n", numero);
    
    // Simulación de dado (1-6)
    int dado = rand() % 6 + 1;
    printf("Dado: %d\n", dado);
    
    // Valor aleatorio en rango específico [min, max]
    int min = 10, max = 50;
    int valor = min + rand() % (max - min + 1);
    printf("Valor entre %d y %d: %d\n", min, max, valor);
    
    return 0;
}
```

**Nota:** `srand()` debe llamarse una sola vez al inicio del programa, no en cada iteración.


# Uso fgets:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

if (fgets(p, tam_max, stdin) == NULL) {
        free(p);
        return NULL;
    }
    
    // Buscamos el '\n' y lo pisamos con un '\0'
    p[strcspn(p, "\n")] = '\0';
```