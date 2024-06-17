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


print(es_primo_1(1))
print("-----------")
print(es_primo_1(0))
print("-----------")
print(es_primo_1(10000000))