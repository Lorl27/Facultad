# Ejercicio 1

## Secuencia de inserciones y reequilibrios en un AVL

1. Insertar 10
   - Se convierte en la raíz.
   - Estado: balanceado.

2. Insertar 20
   - Va a la derecha de 10.
   - Estado: balanceado.

3. Insertar 15
   - Va a la izquierda de 20.
   - Después de la inserción, el nodo 10 tiene altura 2 en su subárbol derecho y 0 en el izquierdo.
   - Desbalance en 10: caso Derecha-Izquierda.
   - Rotación doble (derecha-izquierda): 15 sube, 10 queda a la izquierda y 20 a la derecha.
   - Árbol resultante:
     - Raíz: 15
     - Izquierda: 10
     - Derecha: 20

4. Insertar 25
   - Va a la derecha de 20.
   - Estado: balanceado.

5. Insertar 30
   - Va a la derecha de 25.
   - Desbalance en 20: caso Derecha-Derecha.
   - Rotación simple a la izquierda sobre 20.
   - El 25 sube.
   - Árbol resultante:
     - Raíz: 15
     - Izquierda: 10
     - Derecha: 25
       - Izquierda de 25: 20
       - Derecha de 25: 30

6. Insertar 16
   - Va a la izquierda de 20.
   - Después de la inserción, la raíz 15 queda con altura 1 a la izquierda y 3 a la derecha.
   - Desbalance en 15: caso Derecha-Izquierda.
   - Rotación doble (derecha-izquierda): 20 sube a la raíz principal.
   - Árbol resultante:
     - Raíz: 20
     - Izquierda: 15
       - Izquierda de 15: 10
       - Derecha de 15: 16
     - Derecha: 25
       - Derecha de 25: 30

7. Insertar 18
   - Va a la derecha de 16.
   - Estado: balanceado.

8. Insertar 19
   - Va a la derecha de 18.
   - Desbalance en 16: caso Derecha-Derecha.
   - Rotación simple a la izquierda sobre 16.
   - El 18 sube.

## Árbol final
- Raíz: 20
- Subárbol izquierdo de la raíz:
  - 15
    - Izquierda: 10
    - Derecha: 18
      - Izquierda de 18: 16
      - Derecha de 18: 19
- Subárbol derecho de la raíz:
  - 25
    - Derecha: 30


## Eliminando el 30
El Árbol antes de eliminar




          20
         /  \
       15    25
      /  \     \
    10    18    30
         /  \
       16    19
**Paso 1: Eliminación normal**
El 30 es una hoja, así que la regla de eliminación de ABB nos dice que simplemente lo borramos. 
El árbol nos queda así:



          20
         /  \
       15    25
      /  \
    10    18
         /  \
       16    19
**Paso 2: Chequeo de Balance (¡Alerta!)**
Como estamos en un AVL, después de borrar tenemos que subir desde el padre del nodo borrado (el 25) hasta la raíz, chequeando los balances.

Revisamos el 25: No tiene hijos. Altura 1. Balance: 0. ¡Todo OK!

Revisamos el 20 (La Raíz):

Su rama derecha (solo el 25) tiene altura 1.

Su rama izquierda (15 -> 18 -> 16/19) tiene altura 3.

Diferencia de alturas: ¡2 niveles! ¡El 20 se desbalanceó gravemente hacia la izquierda!

**Paso 3: Identificar el caso**
El desbalance está en el 20 por culpa de su lado izquierdo (el 15).
Ahora miramos al 15 para ver de qué lado "pesa" más: el 15 tiene un hijo izquierdo de altura 1 (el 10) y un hijo derecho de altura 2 (el 18). Es decir, el 15 pesa hacia la derecha.

Como el problema general está a la Izquierda (del 20) pero el peso específico está a la Derecha (del 15), estamos ante un caso Izquierda-Derecha ("hacia adentro").
**Solución: Rotación Doble.**

**Paso 4: La Rotación Doble paso a paso**
1. Rotación Simple a la Izquierda sobre el 15 (el hijo):
El 18 sube y el 15 cae a su izquierda. El hijo izquierdo del 18 (el 16) se vuelve el huérfano y es adoptado como hijo derecho del 15.
El árbol intermedio queda así:

```console

          20
         /  \
       18    25
      /  \
    15    19
   /  \
 10    16
```


2. Rotación Simple a la Derecha sobre el 20 (la raíz desbalanceada):
El 18 sube a ser la nueva raíz principal, y el 20 cae a su derecha. El hijo derecho del 18 (el 19) se vuelve el huérfano y es adoptado como hijo izquierdo del 20.

El Árbol Final (AVL Completo con balance 0.) 



           18
         /    \
       15      20
      /  \    /  \
    10   16  19   25

## ABB sea AVL sin rotar

Para lograr que un ABB adquiera la forma exacta de un AVL final sin hacer ni una sola rotación, debes insertar los nodos leyendo el Árbol Final (el que armamos en el punto A) de arriba hacia abajo y de izquierda a derecha (Recorrido por Niveles).

20, 15, 25, 10, 18, 30, 16, 19

## AVL que requiere que tras eliminar, aplique màs de una rotaciòn.

Àrbol inicial:

Raíz: 50

Subárbol Izquierdo: 30 -> Hijos: 20 y 40. El 20 tiene hijo 10.

Subárbol Derecho: 80 -> Hijos: 70 y 90. El 70 tiene hijo 60.

La reacción en cadena:

Eliminamos el nodo 90.

Revisamos el 80: Su rama izq (70, 60) tiene altura 2. Su rama der (ahora vacía) tiene altura 0. ¡Desbalance!

Hacemos rotación derecha sobre el 80. El 70 sube y el 80 baja.

El efecto dominó: Antes de la rotación, el subárbol derecho completo de la raíz (50) tenía altura 3. Al rotar, ¡se achicó a altura 2!

Revisamos la raíz 50: Su rama izq (30...) tiene altura 4. Su nueva rama der (70...) tiene altura 2. Diferencia de 2. ¡Desbalance en la raíz principal!

Nos obliga a hacer una segunda rotación (Derecha) sobre el 50 para arreglarlo.

¡Dos rotaciones por eliminar un solo nodo!