#Primeros programas interactivos:

#Ejercicio 9. Realice los siguientes ítems:
# a) Escriba una función suma que reciba dos números y retorne el resultado de la suma de ambos

# b) Escriba una función resta que reciba dos números y retorne el resultado de la resta de ambos.

# c) Escriba una función multiplica que reciba dos números y retorne el resultado de la multiplicación de ambos números.

# d) Escriba una función divide que reciba dos números y retorne el resultado de la división de ambos números.

# e) Escriba un programa que muestre un mensaje pidiendo que se elija una opción siendo las mismas:
# 1. Suma
# 2. Resta
# 3. Multiplica
# 4. Divide
# Luego de elegir la operación debe pedirse el ingreso de dos números y mostrar el resul-
# tado de la operación correspondiente (invocando a la función homónima).

# f) Agregue una opción que sea
# 5. Salir
# de manera que, mientras no se ingrese un 5 el programa siga funcionando repitiendo la
# operatoria anterior.

def suma(a,b):
    return a+b

def multip(a,b):
    return a*b

def resta(a,b):
    return a-b

def div(a,b):
    return a/b

def operaciones():
    a= int(input("Ingrese el valor para el primer número:"))
    b= int(input("Ingrese el valor para el segundo número:"))

    valor_i=int(input("""INGRESÉ ALGUNO DE LOS SIGUIENTES VALORES:
                        1. SUMA
                        2. RESTA
                        3. MULTIPLICAR
                        4. DIVISIÓN
                        5.SALIR
                        """))

    while valor_i!=5:
        if valor_i == 1:
            print(suma(a,b))
            operaciones()
        elif valor_i == 2:
            print(resta(a,b))
            operaciones()
        elif valor_i == 3:
            print(multip(a,b))
            operaciones()
        elif valor_i == 4:
            if b==0:
                print("Dividir por 0 es imposible.")
                break
            else:
                print(div(a,b))
                operaciones()
        else:
            print("VALOR INTRODUCIDO ÉRRONEO.")
            break

operaciones()

