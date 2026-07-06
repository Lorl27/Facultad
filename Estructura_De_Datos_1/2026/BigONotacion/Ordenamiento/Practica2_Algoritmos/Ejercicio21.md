### Caso 1: División 1/2 - 1/2
Es el caso ideal.


               n
           /       \
        n/2       n/2
       /  \       /  \
    n/4 n/4    n/4 n/4

Cada nivel cuesta recorrer todo el arreglo: O(n)

Tiempo Total: O(n*log(n))

### Caso 2: División 1/3 - 2/3

Ahora el árbol queda así:

                 n

          n/3        2n/3

      ...             ...

Cada nivel sigue costando O(n)

Porque n/2 + 2n/3 = n
Aunque tarda más en hacerse pequeña. 

Tiempo Total: O(n*log(n))  [Cambiar la base de un logaritmo solo cambia una constante.]
	​

### Caso 3: División 1/k - (k−1)/k

Ahora dividimos en
n/k

(k−1)n/k

¿Cuánto cuesta cada nivel? O(n) ya que:
n/k + (kn-n)/k = n

¿Y la altura? O(logn)

Tiempo Total: O(n*log(n)).

### ¿Cuándo deja de ser O(nlogn)?

Mientras las particiones sean en una proporción fija (1/2–1/2, 1/3–2/3, 1/10–9/10, 1/k–(k−1)/k, etc.), la altura del árbol sigue siendo proporcional a logn.

Solo empeora cuando las particiones se vuelven muy desbalanceadas, por ejemplo:

1

n−1

Entonces tiempo: O(n^2) ,que es justamente el peor caso de QuickSort.