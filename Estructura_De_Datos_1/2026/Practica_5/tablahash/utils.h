#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 * 
 * Si la cadena es "abc": hashval = 0 (inicial).
'a' (97 en ASCII): 97+31⋅0=97.
'b' (98): 98+31⋅97=98+3007=3105.
'c' (99): 99+31⋅3105=99+96255=96354.
Resultado: 96354.
Este valor puede luego reducirse con un módulo (por ejemplo, hashval % tamaño_tabla)
 para ubicar la cadena en una posición dentro de una tabla hash.
 */
unsigned KRHash(char *s);

#endif /** __UTILS_H__ */