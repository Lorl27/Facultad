# Ejercicio 4. Modificar el ejercicio anterior de forma tal que contenga una opción mas la cual
# me permita calcular alguna de las funciones trigonométicas, como el sen, cos, y tan. Estas
# opciones deberán aparecer como un sub-menu.

import os
import time


import os
import time


def imprimirMenu():
    """None->Integer
    Muestra un menú de opciones y devuelve la
    opción ingresada por el usuario.
    Opciones:
    1. Factorial
    2. Fibonacci
    3. Promedio Aritmetico
    4. Primo
    5. Para Salir

    """
    os.system("clear")
    print("1. Calcula el Factorial ")
    print("2. Calcula el Fibonacci ")
    print("3. Calcula el Promedio Aritmético")
    print("4. Determina si es un número primo")
    print("5. Opción de Salida")

    opcion = int(input("Ingrese la opción elegida: ? "))
    return opcion


def factorial(numero):
    """Integer -> Integer
    Ejemplos:
    factorial(2)==2
    factorial(0)==1
    factorial(4)==24
    """
    print("Se debe genera el código para calcular el factorial de: ", numero)
    respuesta=1
    for x in range(2,numero+1):
        respuesta+=x
    return respuesta


def fibonacci(numero):
    """Integer -> Integer"""
    print("Se debe genera el código para calcular el fibonacci de: ", numero)
    
    a, b = 0, 1
    
    for _ in range(numero):
        a, b = b, a+b
        
    return a


def promedioAritmetico(numero1, numero2):
    """Integer Integer-> Integer"""
    print(
        "Se debe genera el código para calcular el promedio de: ",
        numero1,
        " con ",
        numero2,
    )
    
    respuesta = (numero1+numero2)//2
    return respuesta


def esPrimo(numero):
    """Integer -> Boolean"""
    print(
        "Se debe genera el código para calcular si es primo o no el: ", numero, " dado "
    )
    if numero<2:
        respuesta=False
    for x in range(2,numero+1):
        if (x%numero)==0:
            respuesta=False
    respuesta = True
    
    return respuesta


def realizarAcciones(opcion):
    """Integer -> None
    Realiza una acción según la opción del menú elegida. Si la opcion no es valida entonces muestra en pantalla un mensaje de error.
    """
    if opcion == 1:
        numero = int(input("Ingrese nro a calcular? "))
        respuesta = factorial(numero)
        print("El factorial del numero dado es: ", respuesta)
    elif opcion == 2:
        numero = int(input("Ingrese nro a calcular? "))
        respuesta = fibonacci(numero)
        print("El fibonacci del numero dado es: ", respuesta)
        time.sleep(5)
    elif opcion == 3:
        numero1 = int(input("Ingrese el primer nro a calcular? "))
        numero2 = int(input("Ingrese el segundo nro a calcular? "))
        respuesta = promedioAritmetico(numero1,numero2)
        print("El Promedio Aritmetico de los numeros dados es: ", respuesta)
        time.sleep(5)
    elif opcion == 4:
        numero = int(input("Ingrese nro a calcular? "))
        respuesta = esPrimo(numero)
        print("El numero dado es primo?: ", respuesta)
        time.sleep(5)
    else:
        print("La opción seleccionada no es valida.")


def main():
    respuesta = imprimirMenu()
    while respuesta != 5:
        realizarAcciones(respuesta)
        respuesta = 5
    print("Gracias por usar este Menú")


main()
