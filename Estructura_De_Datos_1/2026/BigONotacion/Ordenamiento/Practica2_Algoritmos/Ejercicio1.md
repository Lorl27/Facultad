Si el arreglo ya esta ordenado , no hace falta recorrerlo entero. 

El máximo será el último, el mínimo el primero
y la mediana sera el medio. (n/2 : impar ; (n/2)-1 : par.)

Resultando en Tiempo: O(1) y Memoria: O(1)


Si no hubiera estado ordenado, en el peor casos se recorre todo el arreglo resultando en Tiempo: O(n).

Y en el caso de la Mediana, tendriamos que ordenar primero lo que resultaria en Tiempo: O(n * log(n)).