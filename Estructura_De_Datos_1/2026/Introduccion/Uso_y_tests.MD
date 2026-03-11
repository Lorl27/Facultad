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
    tipoRetorno (*fptr) (tipoDato arg);

```
** EJEMPLOS:**

```c
float (*(*fptr)(char))(int);

// fptr es un puntero a función que recibe un char como argumento y devuelve un
// puntero a función que recibe un int como argumento y devuelve un float.
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

