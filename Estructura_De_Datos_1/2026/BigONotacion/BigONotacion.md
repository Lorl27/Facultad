# Big O Notation - Complejidad de Algoritmos

## 1. Constante: $O(1)$ - La bala de plata
El tiempo de ejecución es **siempre igual**, sin importar el tamaño de los datos.

**¿Cómo detectarlo?**
- No hay bucles (for ni while)
- Operaciones matemáticas simples, asignaciones o accesos directos

**Ejemplos:**
```
return arreglo[0];
int suma = a + b;
```

---

## 2. Lineal: $O(N)$ - El trabajador incansable
El tiempo crece **proporcionalmente** con la cantidad de datos.

**¿Cómo detectarlo?**
- Un solo bucle que recorre los datos de principio a fin

**Ejemplos:**
- `string_len()`
- `imprimir_contactos()`

---

## 3. Cuadrática: $O(N^2)$ - El bucle fatal
El tiempo de ejecución se **dispara drásticamente**. Datos × 2 = Tiempo × 4.

**¿Cómo detectarlo?**
- **Bucles anidados** donde ambos recorren los mismos datos

**Ejemplo:** Bubble sort
- 10 números → $10 \times 10 = 100$ operaciones
- 1000 números → $1000 \times 1000 = 1,000,000$ operaciones

---

## 4. Logarítmica: $O(\log N)$ - El Santo Grial
Crece tan lento que **parece magia**.

**¿Cómo detectarlo?**
- El algoritmo **descarta la mitad de los datos** en cada paso
- Divide y vencerás

**Ejemplo:** Buscar una palabra en el diccionario
- 1,000,000 datos: $O(N)$ tarda 1,000,000 pasos
- 1,000,000 datos: $O(\log N)$ tarda máximo 20 pasos


## 5. Log-Lineal: $O(N \log N)$ - El campeón de los ordenamientos

El "límite de velocidad" del universo para ordenar cosas. Matemáticamente está demostrado que no puedes ordenar más rápido que esto.

**¿Cómo detectarlo?**
- Combinación de dividir el problema a la mitad y recorrer los datos para unirlos

**Ejemplos:**
- Merge Sort, Quick Sort (mucho mejor que Bubble Sort $O(N^2)$)
- `ORDER BY` en SQL sin índice

---

## 6. Exponencial: $O(2^N)$ - El monstruo de la recursividad

Territorio peligroso: agregar 1 elemento duplica el tiempo de ejecución.

**¿Cómo detectarlo?**
- Función recursiva que se llama a sí misma **dos veces**

**Ejemplo:** Fibonacci ingenuo
- 10 elementos → 1 segundo
- 30 elementos → años

---

## 7. Factorial: $O(N!)$ - El colapso del universo

Si tu código llega aquí, algo salió mal. Con solo $N = 20$: $2,432,902,008,176,640,000$ operaciones.

**¿Cómo detectarlo?**
- Calcula **todas las combinaciones o permutaciones** posibles

**Ejemplo:** Problema del Viajante (TSP) - encontrar la ruta más corta entre todas las ciudades


---

## 📋 Resumen del "Ojo Clínico"

| Patrón | Complejidad |
|--------|-----------|
| Sin bucles | $O(1)$ |
| 1 bucle | $O(N)$ |
| 2 bucles anidados | $O(N^2)$ |
| Divide a la mitad | $O(\log N)$ |
