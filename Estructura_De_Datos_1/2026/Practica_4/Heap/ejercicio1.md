### Paso a paso inserciòn

1. Insertar 10: Queda como raíz.

Arreglo: [10]

2. Insertar 20: Entra a la izquierda del 10. Como 20 > 10, trepa (swap).

Arreglo: [20, 10]

3. Insertar 15: Entra a la derecha del 20. Como 15 < 20, se queda ahí.

Arreglo: [20, 10, 15]

4. Insertar 25: Entra como hijo izq del 10. Como 25 > 10, trepa. Compara con la raíz (20) y como 25 > 20, vuelve a trepar.

Arreglo: [25, 20, 15, 10]

5. Insertar 30: Entra como hijo der del 20. Como 30 > 20, trepa. Compara con la raíz (25) y como 30 > 25, trepa de nuevo.

Arreglo: [30, 25, 15, 10, 20]

6. Insertar 16: Entra como hijo izq del 15. Como 16 > 15, trepa. 16 < 30, se queda ahí.

Arreglo: [30, 25, 16, 10, 20, 15]

7. Insertar 18: Entra como hijo der del 16. Como 18 > 16, trepa. 18 < 30, se queda.

Arreglo: [30, 25, 18, 10, 20, 15, 16]

8. Insertar 19: Entra como hijo izq del 10 (al fondo a la izquierda). Como 19 > 10, trepa. Luego compara con su nuevo padre (25). Como 19 < 25, se queda ahí.

Arreglo final: [30, 25, 18, 19, 20, 15, 16, 10]

```console
            30
          /    \
        25      18
       /  \    /  \
     19   20  15   16
    /
  10
```


### Paso a paso de la extracción:

1. Quitar la raíz: Borramos el 30.

Rellenar el hueco: Agarramos al último elemento del arreglo (el 10 que está al fondo a la izquierda) y lo ponemos en la raíz.

Árbol temporal: La raíz ahora es 10.

2. Comienza el hundimiento (Sift-Down): El 10 mira a sus dos hijos (25 y 18).

El hijo mayor es 25. Como 10 < 25, se intercambian.

Árbol temporal: La raíz es 25. El 10 bajó a la izquierda.

3. El 10 (en su nueva posición) mira a sus nuevos hijos (19 y 20).

El hijo mayor es 20. Como 10 < 20, se intercambian.

Árbol temporal: El 20 subió. El 10 bajó a ser hijo derecho del 25.

4. El 10 mira hacia abajo, pero ya no tiene hijos (es una hoja). ¡Terminó de hundirse!


```console
            25
          /    \
        20      18
       /  \    /  \
     19   10  15   16
```