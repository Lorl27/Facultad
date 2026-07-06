Una inversión es un par de índices (i,j) /
i<j
A[i]>A[j]

Es decir, dos elementos que están en el orden incorrecto.
---------

Sea k la cantidad inicial de inversiones del arreglo.

Bubble Sort únicamente intercambia dos elementos adyacentes cuando están invertidos, es decir, cuando A[i]>A[i+1].

Cada intercambio elimina exactamente esa inversión entre los elementos adyacentes. Además, el intercambio no crea nuevas inversiones con los demás elementos, ya que únicamente modifica el orden relativo entre esos dos elementos consecutivos.

Como cada swap reduce la cantidad de inversiones en exactamente una unidad y el algoritmo finaliza únicamente cuando el arreglo queda ordenado (es decir, cuando la cantidad de inversiones es 0), necesariamente el número total de swaps realizados es igual a la cantidad inicial de inversiones.