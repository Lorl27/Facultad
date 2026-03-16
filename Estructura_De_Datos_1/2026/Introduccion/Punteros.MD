
# Punteros

```c
tipoPuntero * puntero;
puntero =(tipoPuntero *) malloc (sizeof(tipoDato)*tam); //void *malloc(size_t tam)
```

# Leer punteros creados para asociarles valores:
```c
char * get_new_line(void){
    char *p = malloc(sizeof(char)*100);
    if(p==NULL) return NULL;
    printf("Ingrese palabra aqui:\n");
    scanf("%s",p); //como p ya tiene la dir a memoria (puntero) no ahce falta & 
    return p;
}

char * get_new_line(void){
    char *p = malloc(sizeof(char) * 100);
    if(p == NULL) return NULL;
    printf("Ingrese linea aqui:\n");
    // fgets lee hasta el \n o hasta el limite (100).
    // Parámetros: dónde guardar (p), tamaño máximo (100), de dónde leer (stdin = teclado)
    if (fgets(p, 100, stdin) == NULL) {
        // Si fgets falla (ej: error de lectura), liberamos la memoria y retornamos NULL
        free(p);
        return NULL;
    }
    return p;
}
```

### Asociar punteros a variables comunes para pasarselas a funciones:

- **FORMA 1:**
```c
    //1. creamos var normales
    int val1 = 5;
    int val2 = 0;

    printf("Antes: val1 = %d, val2 = %d\n", val1, val2);

    // 2. Le pasamos a la función las direcciones de esas variables
    set_int(&val1);   //void set_int(int * nro)
    set_int(&val2);

    // 3. Imprimimos para verificar que se modificaron los originales
    printf("Despues: val1 = %d, val2 = %d\n", val1, val2);
```
- **FORMA 2:**
```c
#include <stdlib.h>


int * nro1 = malloc(sizeof(int)); // Pedimos espacio para un entero
*nro1 = 5;                        // Ahora SÍ podemos guardar el 5 adentro de ese espacio
set_int(nro1);                    // Lo pasamos a la función
free(nro1);                       // Y como usamos malloc, hay que liberar la memoria (¡Valgrind vigila!)
```



* Un puntero puede almacenar la direcciòn (de memoria) de otro puntero
    **Ejemplo:**
    ```c
    int n; *j ; **p
    n=5; j=&n ; p=&j ;  //&n=0x1 &j= 0x4 &p=0x7

    p = 0x7             // *(*p) = 5 
    *p = j = 0x4       // *(j) = 5
    **p = *j = 5      //n = 5

    ```

* Un puntero puede almacenar la direcciòn (de memoria) de una funciòn
  
    *Un puntero a función es una variable que guarda la dirección de
    comienzo de la función* ~~(Puede considerarse como una especie de “alias”)~~

    ```c
        tipoRetorno (*pf) (tipoDatoArg);
    ```

    **EJEMPLOS:**  
    *Nota: Ver ejemplos más concretos en sección Ejemplos Punteros*

    ```c
    float (*(*pf)(char))(int);
    // pf es un puntero a función que recibe un char como argumento y,
    //devuelve un puntero a función que recibe un int como argumento y devuelve un float.

    float    (     *    (*pf)(char)     )  (int);
    ```

    **Ejemplos en funciones:**
    ```c
    int apply(int (* funcion)(int) , int entero){
        return funcion(entero);
    }

    void apply_in(int (* funcion)(int), int * entero){
        *entero=funcion(*entero);
    }
    ```


##### Importancia de usar puntero a funciòn

Por ejemplo, tenemos la sig estructura:
```c
typedef struct
{
    int edad;
    int sexo;
    int numero;
} Esclavo;

int main() {
    Esclavo esclavos[20];
    int i = 0;
    for (i = 0; i < 20; i++) {
        srand(time(NULL) + i);
        esclavos[i].edad = rand() % 100 + 1;
        esclavos[i].sexo = rand() % 2 + 1;
        esclavos[i].numero = i;
    }
}
```
y queremos ordenarlos, en vez de hacer muchas funciones y repetir còdigo. Podrìamos usar un pf:
```c
void ordenar(Esclavo esclavos[ ], int n, int(*comparar)(Esclavo, Esclavo)) {
    int i = 0;
    int j = 0;
    Esclavo buffer;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (comparar(esclavos[i], esclavos[j])) {
                buffer = esclavos[j];
                esclavos[j] = esclavos[i];
                esclavos[i] = buffer;
            }
        }
    }
}
```
donde comparar, es nuestra funciòn por paràmetro, por ejemplo:
```c
int comparar_por_numero(Esclavo a, Esclavo b) {
    return a.numero < b.numero;
}

ordenar(esclavos, 20, comparar_por_edad); //llamado funciòn
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

```c
long (*(*fptr())())[5]  
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

