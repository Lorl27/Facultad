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


## Punteros
```c
tipoPuntero * puntero;
puntero =(tipoPuntero *) malloc (sizeof(tipoDato)*tam); //void *malloc(size_t tam)
```

* Un puntero puede almacenar la direcciòn (de memoria) de otro puntero
    **Ejemplo:**
    ```c
    int n; *j ; **p
    n=5; j=&n ; p=&j ;  //&n=0x1 &j= 0x4 &p=0x7

    p = 0x7        // *(*p) = 5 
    *p = j = 0x4  // *(j) = 5
    **p = *j = 5   //n = 5

    ```

* Un puntero puede almacenar la direcciòn (de memoria) de una funciòn
  
    *Un puntero a función es una variable que guarda la dirección de
    comienzo de la función* ~~(Puede considerarse como una especie de “alias”)~~

```c
    tipoRetorno (*pf) (tipoDato arg);

```
**EJEMPLOS:**
*Nota: Ver ejemplos más concretos en sección Ejemplos_Punteros*

```c
float (*(*pf)(char))(int);
// pf es un puntero a función que recibe un char como argumento y devuelve un puntero a función que recibe un int como argumento y devuelve un float.

float    (     *    (*pf)(char)     )  (int);
```

## EJEMPLOS PUNTEROS
* Puntero a función simple

```c
#include <stdio.h>

int cuadrado(int x){
    return x*x;
}

int main(){
    int (*pf)(int);

    pf = cuadrado;   // guardamos dirección de la función

    int r = pf(5);   // llamamos la función mediante el puntero

    printf("%d\n", r);   //25

    return 0;
}
```

* Puntero a función que devuelve puntero
```c
#include <stdio.h>

int* fun(int x){
    static int y;  //Se usa static porque devolver la dirección de una variable local genera dangling pointer.
    y = x*2;
    return &y;
}

int main(){

    int* (*pf)(int);

    pf = fun;

    int *p = pf(10);

    printf("%d\n", *p);  //20

    return 0;
}
```

* Función que recibe un puntero a función

```c
#include <stdio.h>

int doble(int x){
    return x*2;
}

void ejecutar(int (*pf)(int)){
    printf("%d\n", pf(5));
}

int main(){

    ejecutar(doble);  //10

    return 0;
}
```

* Array de punteros a función
```c
#include <stdio.h>

int f1(int x){ return x+1; }
int f2(int x){ return x+2; }
int f3(int x){ return x+3; }

int main(){

    int (*pf[3])(int);

    pf[0] = f1;
    pf[1] = f2;
    pf[2] = f3;

   //pf: llamar la función apuntada por pf[0] con argumento 10 -->f1(10)
   // pf <>   (*pf[0])(10)  solo que en compilador se simplificó...
    printf("%d\n", pf);  //11
    printf("%d\n", pf);  //12
    printf("%d\n", pf);   //13

}
```

* Función que devuelve puntero a función
```c
#include <stdio.h>

int suma1(int x){
    return x+1;
}

int suma2(int x){
    return x+2;
}

int (*selector(int x))(int){

    if(x==1)
        return suma1;
    else
        return suma2;
}

int main(){

    int (*pf)(int);

    pf = selector(1);

    printf("%d\n", pf(10)); //11

}
```

* Ejemplo Lectura anidada:

```c long (*(*fptr())())[5]  
// fptr es una funcion
// (*fptr()) devuelve puntero
// (*fptr())() a función
// (*fptr())()[5] que devuelve un array de tam 5
// long (* ... )()  de punteros a funciones que devuelven long
```
```c
float (*(*fptr)(char))(int)
//fptr
//→ puntero
//→ a función que recibe char
//→ devuelve puntero
//→ a función que recibe int
//→ devuelve float
```

```c
#include <stdio.h>

long f1(){ return 1; }
long f2(){ return 2; }
long f3(){ return 3; }
long f4(){ return 4; }
long f5(){ return 5; }

long (*arr[5])() = {f1,f2,f3,f4,f5};

long (*(*ret())[5])(){

    return &arr;
}

int main(){

    long (*(*p)[5])();

    p = ret();

    for(int i=0;i<5;i++){
        printf("%ld\n", (*p)[i]());   //1....5
    }

}
```

## ERRORES TIPICOS:

### SEGMENTION FAULT:
- Mal tipo al pedir espacio
- Mal casteo
- Malloc retorna NULL 

### DANGLING REFERENCE
- Perdemos referencia al bloque memoria
- Nos olvidamos del free.
- Referenciamos un espacio YA liberado

