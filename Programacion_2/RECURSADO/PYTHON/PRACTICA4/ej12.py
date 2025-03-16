# Ejercicio 12. Potencias de dos
# a) Escribir una función es_potencia_de_dos que reciba como parámetro un número natural, y devuelva
# True si el número es una potencia de 2, y False en caso contrario.
# b) Escribir una función que, dados dos números naturales pasados como parámetros, devuelva la suma
# de todas las potencias de 2 que hay en el rango formado por esos números (0 si no hay ninguna
# potencia de 2 entre los dos). Utilizar la función es_potencia_de_dos, descripta en el punto anterior.

def es_potencia_de_dos(n):
    if n == 0:
        return False
    while n != 1:
        if n % 2 != 0:
            return False
        n = n // 2
    return True

def potencias(a,b):
    suma=0
    for x  in range(a,b+1):
        if es_potencia_de_dos(x):
            suma+=x
    return suma

print(potencias(2,12))