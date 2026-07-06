
| Tipo de arreglo | Insertion Sort | QuickSort |
|---|---|---|
| Creciente [1 2 3 4 5 6] | Mejor caso: O(n). Cada elemento ya está en su lugar, solo se hacen comparaciones mínimas. | Peor caso: O(n^2). El pivote siempre queda al final, generando particiones desbalanceadas. |
| Aleatorio [1 4 3 6 5 2] | Peor caso: O(n^2). Cada inserción puede recorrer gran parte del arreglo. | Mejor caso promedio: O(n log n). El pivote divide bien los subarreglos. |
| Decreciente [6 5 4 3 2 1] | Peor caso: O(n^2). Cada nuevo elemento debe recorrer todo lo ya ordenado. | Peor caso: O(n^2). El pivote siempre queda en un extremo, generando particiones desbalanceadas. |