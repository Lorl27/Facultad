# Ejercicio 5. Resuelva los siguientes ejercicios comparativamente, definiendo la versión recursiva e iterati-
# va, compare así cada una de las formas de resolución, evaluándolas en distintos valores, primero en valo-
# res menores para luego alcanzar valores naturales más grandes, como por ejemplo: 5,15,25,75,100,500,
# y 1000.
# (a) Diseñar una función que calcule e imprima el resultado de la suma de los primeros 50 números natu-
# rales usando una función recursiva.


# (b) Diseñar una función que calcule e imprima el resultado de la suma de los primeros n números naturales
# usando una función recursiva.

# (c) Diseñar una función que calcule e imprima el resultado de la suma de los números naturales mayores
# que n y menores que m usando una función recursiva.

# (d) Diseñar una función que calcule de forma recursiva los primeros n múltiplos de 3.

# (e) Diseñar una función que calcule de forma recursiva los primeros n múltiplos de k.


def suma_recursiva(n):
    if n == 0:
        return n
    elif n <= 50:
        return n + suma_recursiva(n - 1)


def suma_recursiva_natural(n, limite):
    if n == 0:
        return n
    elif n <= limite:
        return n + suma_recursiva_natural(n - 1)


def suma_mayor_recursiva(n, m):

    if n > m:
        return 0

    if m == 0:
        return m

    else:
        return n + 1 + suma_mayor_recursiva(n + 1, m - 1)


print(suma_mayor_recursiva(5, 9))  # 6-7-8
print(suma_mayor_recursiva(6, 9))  # 7-8


def n_multiplos_de_3(n: int, inicio=1):
    if n == 0:
        pass
    if n > 0:
        multiplo = inicio * 3
        print(multiplo)
        n_multiplos_de_3(n - 1, inicio + 1)


print(n_multiplos_de_3(5))


def n_multiplos_de_k(n: int, k, inicio=1):
    if n == 0:
        pass
    if n > 0:
        multiplo = inicio * k
        print(multiplo)
        n_multiplos_de_k(n - 1, k, inicio + 1)


print(n_multiplos_de_k(5, 3))
