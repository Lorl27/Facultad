# Bucles For:

# Ejercicio 1. Escriba un ciclo definido para imprimir por pantalla todos los números entre 10 y 20.

for x in range(10,21):
    print(x)

# Ejercicio 2. Escriba un programa que imprima por pantalla todas las fichas del dominó, una
# por línea y sin repetir.

def Domino():
    for ficha1 in range(7):
        for ficha2 in range(ficha1, 7):
            print(f"[{ficha1}|{ficha2}]")

Domino()
# Ejercicio 3. Modifique el programa anterior para que pueda generar fichas de un juego que
# puede tener números de 0 a n.

def JuegoAle(n):
    for ficha1 in range(0,n+1):
        for ficha2 in range(ficha1, n+1):
            print(f"||{ficha1}|{ficha2}||")

print(JuegoAle(2))
# Ejercicio 4. Escriba una función que tome una cantidad m de valores que serán ingresados
# por el usuario y, a medida que se ingresa cada número, muestre el factorial del mismo. El valor
# de m es ingresado inicialmente por el usuario.

import math


def FactoPerso():
    m = int(input("Ingrese un número,para saber su factorial: "))
    print(math.factorial(m))

FactoPerso()

def F(m):
    for x in range (m+1):
        print(f"El factorial de {x} es: ",math.factorial(x))

F(5)

# Ejercicio 5. Usando la función dada como ejemplo en la presentación de La Receta en Python
# para convertir una temperatura de Fahrenheit a Celsius, genere una tabla de conversión de
# temperaturas, desde 0◦F hasta 120◦F , de 10 en 10.

def FtoC(f):
    return (f-32)/ 1.8

def FahToCel():
    for x in range(0,121,10):
        print(f"{x}°F equivale a: {FtoC(x)}°C , {(FtoC(x)):.3} Cel")

FahToCel()

# Ejercicio 6. Escriba una función que reciba un número n como parámetro e imprima los pri-
# meros n números triangulares, junto con sus respectivos índices. El número triangular n se
# obtiene mediante la suma de los números naturales desde 1 hasta n. Es decir, si se piden los
# primeros 5 números triangulares, el programa debería imprimir:
# 1= 1 - 1
# 2= 2 - 3
# 3= 3 - 6
# 4= 4 - 10
# 5= 5 - 15
# Nota: hacerlo usando y sin usar la ecuación:
# n∑ , i=1
# i =( n * (n + 1))/ 2 .
# ¿Qué versión realiza más operaciones?

#usando la fórmula:

def formula(n):
    return int(( n * (n + 1))/ 2)

def ej6_P1(n):
    for x in range(1,n+1):
        print(f"El indice es {x} y su suma triangular es: {formula(x)}")

ej6_P1(5)

def ej6_P2(n):
    contador=0
    for x in range(1,n+1):
        print(f"Indice = {x} , su suma triangular es: {x+contador}")
        contador+=x

ej6_P2(5)