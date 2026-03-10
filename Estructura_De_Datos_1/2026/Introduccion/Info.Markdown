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