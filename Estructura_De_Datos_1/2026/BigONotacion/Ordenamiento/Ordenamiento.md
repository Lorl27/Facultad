# Algoritmos de Ordenamiento
Entrada: array A de tipo T, longitud n
Salida: array A' de tipo T, longitud n / cumple : 
    - Ordenado: Para todo i,j / i<j => A[i]<=T(*) A[j]
    - Permutaciòn: A y A' tienen los mismos elementos en igual cantidad

(<=T) Es una comparaciòn arbitraria que cumple :
1. a <=T a
2. si a <=T b y b <=T c => a <=T c

Ejemplo: [1,3,2,1,4] -> [1,1,2,3,4]

## Motivaciòn para ordenar
Nos sirve para buscar en O(log(n))

```console
busqbin(A[N], lo, hi, v)
    if hi < lo ⇒
        return -1; // no est
    medio = (lo + hi) / 2
    if A[medio] = v ⇒
        return medio
    else if A[medio] < v ⇒
        return busqbin(A, medio+1, hi, v)
    else
        return busqbin(A, lo, medio-1, v)
```

## Estilos
1. **Basados en comparaciòn:** Sòlo podemos chequear con <=T
2. **Especializados al tipo:** Por ej, enteros.

### Basados en comparaciòn

#### Bubble Sort
Es muy malo, recorre todo el arreglo dando vuelta 'inversiones' adyacentes. Si en una vuelta no hicimos nada: terminamos.

- Primera pasada: El màximo queda al final
- Màximo pasadas: n
- Tiempo ejecuciòn: O(n^2)
- Memoria: O(1)


```console
bubble(A[N])
    hiceAlgo = true
    while hiceAlgo ⇒ (
        hiceAlgo = false
        for i in 0..N-2 ⇒
            if A[i] > A[i+1] ⇒
                A[i] ↔ A[i+1]
                hiceAlgo = true
    )
```

[ **4,2**,3,1]->[2, **4,3**,1]->[2,3, **4,1**]->[ *2,3*,1,4]->[2, **3,1**,4]->[2,1, *3,4*]->[ **2,1**,3,4]->[1, *2,3*,4]->[1,2, *3,4*]->[ *1,2*,3,4]->[1, *2,3*,4]->[1,2,*3,4* ]

#### Insertion Sort
Razonable para arreglos pequeños (N<=50), vamos llevando un prefijo ordenado y agregando elementos de a uno (N-1 veces)

 Tiempo ejecuciòn: O(n^2)
- Memoria: O(1)
