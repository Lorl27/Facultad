# PILA  (stack)
Es una lista de elementos, en la cuàl solo se puede extraer el ÙLTIMO elemento insertado . Llamado, **Tope** de la pila.

- LIFO (Last In - First Out)

**Operaciones de la PILA:**
- Push : apila(inserta) un elemento en el tope
- Pop : desapila (elimina) el elemento en el tope
- Top : Retorna el elemento en el tope
- isEmpty : retorna bool que determina si està vacìa o no.

```c
typedef struct _Pila {
    SNodo * inicio; //El tope
} * Pila ;
```

Entonces, usando SList, push = agregar_inicio y pop= eliminar_inicio

# COLA (queue)
Es una lista de elementos, en la cuàl se insertan nuevos al final y, se extraen desde el inicio

- FIFO (First In - First Out)

**Operaciones de la COLA:**
- Enqueue : encola(inserta) un elemento al final
- Dequeue : desencola (elimina) el elemento en el inicio
- isEmpty : retorna bool que determina si està vacìa o no.

```c
typedef struct _Cola {
    SNodo *inicio; // Por aquí salen (dequeue)
    SNodo *fin;    // Por aquí entran (enqueue)
} *Cola;
```
