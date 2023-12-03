// Ejercicio 3. Dadas las siguientes declaraciones:
int * ip1 , ip2 ;
char ch , * cp ;

// ¿Cuáles de las siguientes asignaciones son violaciones de tipo? Explique el motivo.

// ip1 = "cadena de ejemplo"; ->ERROR. ip1 es de tipo puntero int!
//  cp = 0; -> bien (NULL/0)
//   ip1 = 0; ->bien.
// cp = &'a';  ->  bien. direccion del char a
// ip1 = ip2;  -> ERROR. Estás asignando un entero (int) a un puntero a entero (int*). No son tipos compatibles.
// cp = '\0'; ->ERROR
// ip1 = '\0'; ->ERROR. puntero tipo int!
//  cp = &ch; ->bien
//   *ip1 = ip2; -> ERROR