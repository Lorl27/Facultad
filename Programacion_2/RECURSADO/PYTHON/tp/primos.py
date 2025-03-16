# Ejercicio 2. Los números primos
# a) Diseñar una función que dado un número natural determine si este es primo o no. La solución deberá
# ser iterativa. Recordar que los números primos son aquellos que son divisibles por un 1 y por si
# mismo. Algunos ejemplos son: 2, 3, 5, 7, 11, 13, 17, 19, ....
# b) Mejora estos ciclos:
# Los siguientes tres ciclos intentan resolver el problema de determinar anterior, determinando si un
# número es primo o no. Pero ... creemos que algunos de ellos son mejorables ya que no siguen
# algunas de las indicaciones dadas sobre un buen diseño de ciclo o pueden haber dejado algún/os
# casos afuera.


def es_primo(n) -> bool:
    if n < 2:
        return False
    for x in range(2, n):
        if (n % x) == 0:
            return False
    return True


# Te pedimos que escribas una mejora para cada uno de ellos, si lo creen necesario, o justifica tu
# respuesta sobre porqué estarían bien diseñado si es tu consideración.
# (1) Solución de Felicitas


def es_primo_1(num):
    """
    numero: Integer
    es_primo: Integer -> Bool
    Determina si un número dado indicando si es primo o no.
    es_primo (17) = True
    es_primo (2) = True
    es_primo (25) = False
    """
    for n in range(2, num):
        if num % n == 0:
            return False
        respuesta = True
    return respuesta


# (2) Solución de Guido
def es_primo_2(num):
    """
    numero: Integer
    es_primo: Integer -> Bool
    Determina si un número dado indicando si es primo o no.
    es_primo (17) = True
    es_primo (2) = True
    es_primo (25) = False
    """
    respuesta = False
    if num > 3:
        contador = 0
        for i in range(2, num):
            if num % i == 0:
                contador = contador + 1
        if contador == 0:
            respuesta = True
    return respuesta


# 3) Solución de Franco
def es_primo_3(num):
    """
    numero: Integer
    es_primo: Integer -> Bool
    Determina si un número dado indicando si es primo o no.
    es_primo (17) = True
    es_primo (2) = True
    es_primo (25) = False
    """
    

    
    respuesta = True
    divisores = 0
    if num == 1:
        respuesta = False
    else:
        for i in range(2, num + 1):
            if num % i == 0:
                divisores += 1
            if 2 < divisores:
                respuesta = False
                break
    return respuesta


print("///////////")
print("///////////")
print(es_primo_2(1))
print("-----------")
print(es_primo_2(0))
print("-----------")
print(es_primo_2(10000000))
print("///////////")
print("///////////")
print(es_primo_3(1))
print("-----------")
print(es_primo_3(0))
print("-----------")
print(es_primo_3(10000000))
