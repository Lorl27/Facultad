
// XOR TABLA VERDAD
// A  B   C
// 0  0   0
// 0  1   1
// 1  0   1
// 1  1   0

// VERDADERO <-> A!=B


// El operador XOR tiene dos propiedades:
// -Cualquier cosa XOR sí misma da cero: A⊕A=0
// -Cualquier cosa XOR cero da la misma cosa: A⊕0=A


/*

En una lista doble normal, el nodo B (que está entre A y C) tiene dos punteros: ant = A y sig = C.
En una Lista XOR, el nodo B tiene un solo puntero, al que llamamos npx (Next-Prev-XOR).
Adentro guardamos la mezcla de los dos: npx = A ⊕ C.


Para recorrer una lista XOR... :
Supongamos que estamos recorriendo hacia adelante. 
Estamos parados en B, y venimos de A. Queremos saber quién es el siguiente (C).
Lo que hacemos es tomar nuestro nodo anterior (A) y hacerle XOR con el npx de B:
Siguiente = A ⊕ (A ⊕ C) = 0 ⊕ C = C

Si viniéramos en reversa (parados en B, viniendo de C), haríamos:
Anterior = C ⊕(A ⊕ C)= 0 ⊕ A = A
*/

#include <stdint.h>

typedef struct _DNodo{
    uintptr_t npx; //xor ant y sig.
    int dato;
} DNodo;


/* VENTAJAS Y DESVENTAJAS:

Ventajas de la lista XOR:
- Ahorro de memoria: cada nodo usa un solo puntero npx en lugar de dos punteros ant y sig. En sistemas de 64 bits, esto equivale a ahorrar 8 bytes por nodo.
- Escritura compacta: la lista simula una doblemente enlazada manteniendo un tamaño similar al de una lista simplemente enlazada.
- Ejercicio práctico: entender y manipular XOR de punteros fortalece el razonamiento sobre estructuras de datos y memoria.

Desventajas y limitaciones:
- No puedes avanzar sin saber el nodo anterior: para calcular el siguiente nodo necesitas el puntero anterior. Si te entregan un nodo aislado en el medio, no puedes recorrer la lista desde allí.
- Depuración difícil: herramientas como Valgrind o GDB no muestran la estructura de la lista claramente, porque los punteros almacenados están "encriptados" con XOR.
- Código más complejo: inserciones y borrados requieren actualizar npx de varios nodos y manejar cuidadosamente los XOR de punteros, lo que aumenta el riesgo de errores.
- Incompatible con algunos recolectores de basura y sistemas de rastreo de punteros: los nodos pueden parecer no referenciados porque sus punteros no son direcciones directas.

*/




