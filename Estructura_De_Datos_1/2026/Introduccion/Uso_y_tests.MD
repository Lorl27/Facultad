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

## ERRORES TIPICOS:
### SEGMENTION FAULT:
- Mal tipo al pedir espacio
- Mal casteo
- Malloc retorna NULL 

### DANGLING REFERENCE
- Perdemos referencia al bloque memoria
- Nos olvidamos del free.
- Referenciamos un espacio YA liberado

// seguir p.26/51...