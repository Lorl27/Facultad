# Uso de C y convenciòn de Còdigos - Uso de testings.

**Compilar:** `gcc -o mi_programa archivo.c`  

**Ejecutar:** `./mi_programa`

## TIPOS DATOS

| Tipo            | Printf                                 |
| --------------- | -------------------------------------- |
| int             | %d / %i                                |
| float           | %f (solo 2 decimales: %.2f)            |
| double          | %f -- SCANF: %lf                       |
| char            | %c                                     |
| string (char*)  | %s                                     |


## Receta y Testing en C

La receta que aplicamos consta de los siguientes
pasos:
1. Diseño de datos;
2. Signatura y declaración de proposito.
3. Ejemplos;
4. Definición de la función;
5. Evaluar el código de los ejemplos;
6. Realizar modificaciones en caso que el paso anterior genere errores

```c
#include <stdio.h>
#include <assert.h>
 // Representamos temperaturas mediante números enteros
 // farCel: int -> int
 // El parámetro representa una temperatura en Fahrenheit y,
 // se retorna su equivalente en Celsius.
 // entrada: 32, salida: 0
 // entrada: 212, salida: 100
 // entrada: -40, salida: -40
 int farCel(int f) {
    return (f-32)*5/9;
 }

 int main() {
    assert(farCel(32) == 0);
    assert(farCel(212) == 100);
    assert(farCel(-40) == -40);
    return 0;
 }
```

## Convenciòn de Còdigo:
- **Nombres de funciones:** void slist_append(...)
- **Nombres de variables:** camelCase
- **Nombres de constantes:** MAX_DATA
- **Nombres de nuevos tipos de datos y alias:** CamelCase

Con GNU Indent , llamar:  
```c
indent -bad -brf -br -bs somefile.c //(màs info en man indent)
```

## Uso de GDB (GNU Debugger) y Valgrind
**GDB** es un depurador paso a paso. Te permite detener la ejecución de tu programa en cualquier momento, mirar qué hay por dentro y avanzar línea por línea.  

**Valgrind** *(específicamente su herramienta Memcheck)* es un perfilador de memoria. Sirve para detectar accesos a memoria inválida y fugas de memoria (memory leaks). Te avisa si usaste un puntero que ya habías liberado, si te saliste del límite de un arreglo o si te olvidaste de liberar memoria.

**Flujo de trabajado idonèo:**

1. Escribes tu código.
2. **Pruebas con Valgrind:** Corres tu programa a través de Valgrind. Si te dice que hay memoria no liberada o errores de lectura/escritura, sabes que tienes un problema de punteros oculto.
3. **Investigas con GDB:** Si el programa se rompe (SegFault) o si la lógica no da el resultado esperado, abres GDB, pones un punto de interrupción (breakpoint) en la función problemática y avanzas línea por línea para ver en qué momento el puntero se fue a cualquier parte.

**Compilar**
```c
gcc -g -Wall prueba.c -o programa_prueba //-g: guarda info depuraciòn

valgrind --leak-check=full ./programa_prueba

gdb ./programa_prueba

//list - lista de programas
break main 
run //parametro1 parametro2
next //avanza linea x linea desde la funciòn main.
step //similar a next, pero entrando a funciones.
print arreglo[0] //ejemplo uso 
//print arr te dara la dir de memoria
x/5xb arr //Examina (5) elementos, en formato he(x)adecimal, de tamaño (b)yte (char), empezando en la dirección de (arr) (LO DE ADENTRO)
set arr[0] = 'A'  //entonces el de arriba dira A en hex y dsp basura
quit
//i b   - lista de breakpoints
//d 4  - eliminar el breakpoint 4


```
***Nota:** Para ejemplos ir a Ejemplos_Depuracion.*