#Bucles While:

# Ejercicio 7. Escriba una función que le pida al usuario que ingrese un número positivo. Si el
# usuario ingresa cualquier cosa que no sea lo pedido se le debe informar de su error mediante
# un mensaje y volver a pedirle el número, repitiendo este proceso hasta que ingrese lo pedido.

def pos():
    n=int(input("Ingresa un numero: "))
    while n<0:
        print("Error. Ingresa un número positivo.")
        pos()

pos()

# Ejercicio 8. Escriba un programa que permita al usuario ingresar un conjunto de notas, pre-
# guntando a cada paso si desea ingresar más notas, e imprima el promedio correspondiente al
# finalizar la toma de datos.

def promedio(x):
    if len(x) ==0:
        return 0
    else:
        return sum(x)/len(x) #sum == suma de touts le ingredients of x , if x it´s a list.

notas=[]

def ej8():
    while True:
        usu = input("¿Desea ingresar una nota? Responda con SI/NO: ")
        if usu == "SI":
            nota = int(input("Ingresá la nota: "))
            notas.append(nota)
        elif usu == "NO":
            break
        else:
            print("Respuesta no válida. Responda con SI o NO.")

    if len(notas) > 0:
        print(f"Tus notas son: {notas} y tu promedio es DE: {promedio(notas):.2}" )
    else:
        print("No se ingresaron notas, no se puede calcular el promedio...")

ej8()

# Ejercicio 9. Escriba un programa que pida dos números enteros. El programa pedirá de nuevo
# el segundo número mientras no sea mayor que el primero. El programa terminará escribiendo
# los dos números.

def nums():
    while True:
        try:
            n1=int(input("Ingrese un numero entero: "))
            n2=int(input("Ingrese otro numero entero: "))
            while n1>n2:
                n2=int(input("Ingrese otro número, para que sea mayor al primero: "))
            print(f"Número 1 es:{n1} y Número 2 es:{n2}")
            break
        except ValueError:
            print("Ha ingresado algo que NO es un número entero...")

nums()

# Ejercicio 10. Escriba una función que reciba dos números como parámetros y devuelva cuán-
# tos múltiplos del primero hay que sean menores que el segundo.

# a) Implementarla utilizando un ciclo for, desde el primer número hasta el segundo.

def multi1(a,b):
    contador=0
    for x in range(a,b):
        if x %a == 0:
            contador+=1
    print(f"hay {contador} mutliplos de {a} menores que {b}")

multi1(5,10)

# b) Implementarla utilizando un ciclo while, que multiplique el primer número hasta que sea
# mayor que el segundo.

def ej10(a,b):
    contador=0
    while a<b:
        if contador%a ==0:
            contador+=1
        a*=2
        print(f"hay {contador} mutliplos de {int(a/2)} menores que {b}")

ej10(5,10)

# c) Comparar ambas implementaciones: ¿Cuál es más clara? ¿Cuál realiza menos operacio-
# nes?
#Más clara: a.;menos op: b

# Ejercicio 11. Manejo de contraseñas

# a) Escriba un programa que contenga una contraseña inventada. El programa debe pre-
# guntarle al usuario la contraseña y no permitirle continuar hasta que la haya ingresado
# correctamente.

# b) Modifique el programa anterior para que solamente permita como máximo una cantidad
# fija de intentos.

# c) Modifique el programa anterior para que sea una función que devuelva si el usuario in-
# gresó la contraseña correctamente o no, mediante un valor booleano (True o False).

def contraseñaA():
    contraseña= "password"
    intentosV= 1
    while intentosV<=3:
        usuario= input("Ingrese una contraseña valida: ")
        if usuario == contraseña:
            print(f"La has obtenido en {intentosV} intentos")
            return True
        else:
            print(f"Has ingresado {usuario} y es incorrecta. Es tu intento nr {intentosV}")
            intentosV+=1
    print(f"Has agotados los {intentosV} intentos")
    return False

contraseñaA()

# Ejercicio 12. Escriba una función que reciba un número natural e imprima todos los números
# primos que hay menores o iguales que ese número. Para esto se pide que:
# a) Defina una función es_primo que toma un número natural y verifica si es un número primo.
# b) Resuelva el problema usando la función definida en el punto anterior.

def es_primo(numero):
    if numero <= 1: #primo: a>1 , a/1, a/a
        #print (False)
        return False

    for x in range(2, numero):
        if numero % x == 0:
            #print(numero,False)
            return False #div ergo NO primo

    #print (numero,True)
    return True #if not found= primo.

def primos(n):
    for x in range (1,n+1):
        if es_primo(x) == True:
            print(f"En el rango de {n}, {x} es primo")


# Ejercicio 13. Potencias de dos
# a) Escriba una función es_potencia_de_dos que reciba como parámetro un número natural
# y devuelva True si el número es una potencia de 2 y False en caso contrario.
# b) Escriba una función que, dados dos números naturales pasados como parámetros, de-
# vuelva la suma de todas las potencias de 2 que hay en el rango formado por esos números
# (0 si no hay ninguna potencia de 2 entre los dos). Utilice la función es_potencia_de_dos
# descripta en el punto anterior.

def es_potencia_de_dos(n):
    for x in range(0,n):
        if 2**x == n:
            return True

    return False

def potencias(a,b):
    sumap = 0
    for x in range(a,b):
        if es_potencia_de_dos(x):
            print(f"Potencia: {x}, suma hasta ahora(sin {x}): {sumap}")
            sumap+=x
    print(f" El total es: {sumap}")


potencias(1,9)