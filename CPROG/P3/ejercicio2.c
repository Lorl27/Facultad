// 2. Punteros
// Ejercicio 2. Dadas las siguientes declaraciones:
int vector[5] = {10, 20, 30, 40, 50};
int a = 3;
int *ptr = &a;
int *qtr = vector;
// Determinar el tipo y valor de:
// a  -> var int,3
// &a ->direccion de a; 
//  *a -> ERROR, a no es puntero!
//   ptr -> Es un puntero entero que apunta a la dirección de memoria de la variable a
//  &ptr  -> direccion del puntero
// *ptr -> va hacia el valor del puntero->valor de a->3
//  qtr -> puntero entero que apunta al array de enteros vector, concretamente a su 1er elemento
// &qtr -> direccion del puntero
//  *qtr  -> contiene el valor del puntero->valor del primer elemento del array->10
// vector -> un array de int
//  &vector  ->direccion del array
// *vector ->Error! no es un puntero
//  ++qtr -> incrementa la direccion -> 2do elemento -> 20
//  ++*qtr -> incrementa el valor del primer elemento +1->11(10+1)
// ++*vector  ->error
// *&ptr ->ptr->direccion de a