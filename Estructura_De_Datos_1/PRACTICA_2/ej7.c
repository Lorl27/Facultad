// 7. Filtrando los elementos de una lista.
// a) Agregue a la implementaci´on anterior una funci´on
// GList glist_filtrar(GList lista, FuncionCopia c, Predicado p);
// que dada una lista general, retorne una nueva lista con los elementos que cumplen con el predicado.
// El tipo de la funci´on p est´a declarado como typedef int (*Predicado) (void *dato), y retorna
// 1 cuando el dato cumple con el predicado y 0 en caso contrario.

// b) Utilice esta funci´on en main.c para filtrar todos los contactos mayores a 60 a˜nos.