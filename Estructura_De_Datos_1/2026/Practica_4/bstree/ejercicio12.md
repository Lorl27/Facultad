Secuencia de ejemplo: 4, 6, 7, 8, 9

Cuando un àrbol està desbalanceado, es el peor escenario posible.

## Árbol como lista (desbalanceado)

- Si buscas el 9 en tu secuencia ordenada, la computadora debe explorar:
  1. 4
  2. 6
  3. 7
  4. 8
  5. 9
- Exploró los 5 nodos.
- El tiempo de búsqueda es proporcional al total de elementos: $O(n)$.
- Se pierde la ventaja de la búsqueda binaria.

## Árbol completo (balanceado)

- Si los 5 nodos estuvieran balanceados, el árbol sería:
  - raíz: 7
  - izquierda: 4 y 6
  - derecha: 8 y 9
- Para encontrar el 9 solo visitas:
  1. 7
  2. 8
  3. 9
- Exploraste 3 nodos.
- El tiempo de búsqueda es $O(\log n)$.
