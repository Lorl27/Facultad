# Ejercicio 5. Escriba una función que reciba un número n como parámetro e imprima los pri-
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
        contador+=x
        print(f"Indice = {x} , su suma triangular es: {contador}")
        

ej6_P2(5)