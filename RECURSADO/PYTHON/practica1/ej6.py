
# Ejercicio 6. Implementar un algoritmo que, dado un número entero n, permita calcular su
# factorial

def factorial(n):
    if n==1 or n==0:
        return 1
    else:
        return factorial(n-1)*n

# print(factorial(5))
