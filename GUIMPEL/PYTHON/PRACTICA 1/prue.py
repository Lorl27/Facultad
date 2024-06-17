def mayor(lista_n) -> int:
    if lista_n == []:
        print("la lista no posee elementos")
    mayor = lista_n[0]  # Initialize mayor with the first element of the list
    for elemento in lista_n:
        if elemento > mayor:
            mayor = elemento
    return mayor

print(mayor([1, 2, 3, 4]))    



def mayo2(lista_n):
    if lista_n == []:
        print("la lista no posee elementos")
        return None

    mayor = lista_n[0]

    while lista_n:
        if lista_n[0] > mayor:
            mayor = lista_n[0]
        lista_n = lista_n[1:]

    return mayor

print(mayo2([1, 3, 2, 4, 8]))  # resultado esperado: 8

def mayor2(lista_n):
    if not lista_n:
        print("La lista no posee elementos")
        return None  # Retorna None cuando la lista está vacía
    mayor = lista_n[0]  # Inicializa el mayor con el primer elemento
    index = 1
    while index < len(lista_n):
        if lista_n[index] > mayor:
            mayor = lista_n[index]
        index += 1
    return mayor

print(mayor2([1, 3, 2, 4, 8]))  # Resultado esperado: 8

def n_mayor(lista_n, n):
    if not lista_n:
        print("La lista no posee elementos")
        return None  # Retorna None cuando la lista está vacía
    if n <= 0:
        print("El valor de n debe ser mayor que cero")
        return None
    
    if n > len(lista_n):
        print(f"La lista tiene menos de {n} elementos")
        return None
    
    n_mayores = []  # Inicializamos una lista vacía para almacenar los n números más grandes
    
    for _ in range(n):
        max_numero = max(lista_n)  # Encuentra el número más grande en la lista actual
        n_mayores.append(max_numero)  # Agrega el número más grande a la lista de n números más grandes
        lista_n.remove(max_numero)  # Elimina el número más grande de la lista original
    
    return n_mayores[-1]  # Devuelve el n-ésimo número más grande

lista_numeros = [1, 3, 2, 4, 8]
n = 3  # Cambia este valor para buscar el tercer número más grande

resultado = n_mayor(lista_numeros, n)
if resultado is not None:
    print(f"El {n}-ésimo número más grande es: {resultado}")

def find_nth_largest(list, N):
    if len(list) < N:
        print("N is larger than the size of the list")
        return None

    largest_nums = []
    for num in list:
        if len(largest_nums) < N:
            largest_nums.append(num)
        else:
            min_num = min(largest_nums)
            if num > min_num:
                largest_nums.remove(min_num)
                largest_nums.append(num)

    return min(largest_nums)

list1 = [4, 5, 1, 2, 9]
N = 2
print(find_nth_largest(list1, N))  # Output: 5

list2 = [81, 52, 45, 10, 3, 2, 96]
N = 3
print(find_nth_largest(list2, N))  # Output: 52
