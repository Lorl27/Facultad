// Ejercicio 2. ¿Qué problema existe en las siguientes declaraciones de estructuras?


//A:

//struct point (double x, y)
// PROBLEMA: no se usa bien la sintaxis de estructura, las declaraciones de las variables
// están incompletas y deben ser separadas por ';'.

//B:

// struct point{double x, double y};
//PROBLEMA: las declaraciones deben ser separadas por ';'

//C:

//struct point{double x; double y}
//PROBLEMA: a la última declaración le falta ';' , además de que no se respeta
// la sintaxis de struct, ésta lleva ';' al final de la declaración.

//D:

struct point{double x; double y;}; //ES LA ÚNICA CORRECTA. SIN ERRORES

//E:

// struct point {double x; double y;}
//PROBLEMA: no se respeta
// la sintaxis de struct, ésta lleva ';' al final de la declaración.