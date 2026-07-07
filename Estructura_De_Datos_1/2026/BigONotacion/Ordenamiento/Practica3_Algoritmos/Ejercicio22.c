/* Las diferencias provocan que el algorito se resulva con Greedy .

Queremos minimizar la sumatoria de pi*di desde i, donde
pi es la prob de buscar la clave i
di la profundidad e la hoja donde quedo.


entonces solo importa que probabilicades quedan mas arriba y, cuales mas abajo.

Estrategia Huffman:
Tomar las 2 probabilidades más pequeñas, unirlas bajo un nuebo nodo
el nuevo nodo tiene probailidad igual a al suma
repetir hasta que quede un solo arbol.

Complejidad: O(n*log(n))


crear min-heap

insertar todas las probabilidades

mientras heap tenga más de un nodo

    a = extraer mínimo

    b = extraer mínimo

    nuevo = a + b

    insertar nuevo

la raíz es el único nodo restante

*/