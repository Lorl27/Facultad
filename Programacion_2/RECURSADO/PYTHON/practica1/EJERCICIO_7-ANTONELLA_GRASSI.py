# Antonella Grassi , 07/03/24.
# TRABAJO PRÁCTICO NRO 1
# -----------------------------------------------------

# Ejercicio 7. Implementar algoritmos que resuelvan los siguientes problemas:
## a) Dados dos números,imprimir la suma, resta, división y multiplicación de ambos.
## b) Dado un número entero n,imprimir su tabla de multiplicar.

# -----------------------------------------------------

# Diseño de datos:

# Primer número (float) : a
# Segundo número (float): b

# Resultado de las operaciones (float): suma, resta, multiplicación, división

# calculadora: float,float->float
# El usuario ingresa dos números, dados éstos realiza las 4 operaciones (suma-resta-multiplicación-división)
##En caso de que el segundo número ingresado sea  un 0, la división dará error, ya que no es posible realizarla.
##Si no es un 0, se realizará la división
# El resto de operaciones se realizará de igual manera en los 2 casos.


# Proposito:
# Realiza las 4 operaciones básicas (suma, resta, multiplicación, división) con dos números,
# para luego mostrar el resultado al usuario


# EJEMPLOS:
# calculadora(5,6)=(11,-1,30,0.8333333333333334)
# calculadora(1,2)=(3,-1,2,0.5)


def calculadora(a, b):

    suma = a + b
    resta = a - b
    multiplicacion = a * b

    if b != 0:
        division = a / b
    else:
        division = "error, no se puede dividir por 0."  # Es necesario crear el condicional para que no se "rompa" el código

    return suma, resta, multiplicacion, division


# Casos de prueba:
def test_calculadora():
    assert calculadora(5, 6) == (11, -1, 30, 0.8333333333333334)
    assert calculadora(0, 2) == (2, -2, 0, 0.0)
    assert calculadora(10, 0) == (10, 10, 0, "error, no se puede dividir por 0.")
    assert calculadora(-10, 1) == (-9, -11, -10, -10.0)


################################################################

# Diseño de datos:
# Número entero (int): n
# Resultado de la tabla de multiplicar (int): resultado

# tabla:int->int
# Dado un numero, lo que hacemos es -- a través de un ciclo "for" -- multiplicar ese número por cada número correspondiente de la tabla de multiplicar,
# Es decir, desde el 0 al 10.

# Proposito: Imprime la tabla de multiplicar de un número entero.

# Ejemplo:
# tabla(2) te debería devolver
# 2*1=2
# 2*2=4
# 2*3=6
# 2*4=8
# 2*5=10
# 2*6=12
# 2*7=14
# 2*8=16
# 2*9=18
# 2*10=20


def tabla(n):
    for numero in range(1, 11):
        resultado = n * numero
        print(
            f"El número {n} multipicado por {numero}, da como resultado: {resultado} "
        )


# Casos de prueba:
# tabla(5) === ("""El número 5 multipicado por 1, da como resultado: 5
# El número 5 multipicado por 2, da como resultado: 10
# El número 5 multipicado por 3, da como resultado: 15
# El número 5 multipicado por 4, da como resultado: 20
# El número 5 multipicado por 5, da como resultado: 25
# El número 5 multipicado por 6, da como resultado: 30
# El número 5 multipicado por 7, da como resultado: 35
# El número 5 multipicado por 8, da como resultado: 40
# El número 5 multipicado por 9, da como resultado: 45
# El número 5 multipicado por 10, da como resultado: 50""")


# tabla(10) === (El número 10 multipicado por 1, da como resultado: 10
# El número 10 multipicado por 2, da como resultado: 20
# El número 10 multipicado por 3, da como resultado: 30
# El número 10 multipicado por 4, da como resultado: 40
# El número 10 multipicado por 5, da como resultado: 50
# El número 10 multipicado por 6, da como resultado: 60
# El número 10 multipicado por 7, da como resultado: 70
# El número 10 multipicado por 8, da como resultado: 80
# El número 10 multipicado por 9, da como resultado: 90
# El número 10 multipicado por 10, da como resultado: 100
# El número 20 multipicado por 1, da como resultado: 20
# El número 20 multipicado por 2, da como resultado: 40
# El número 20 multipicado por 3, da como resultado: 60
# El número 20 multipicado por 4, da como resultado: 80
# El número 20 multipicado por 5, da como resultado: 100)


# tabla(-5)==(El número -5 multipicado por 1, da como resultado: -5
# El número -5 multipicado por 2, da como resultado: -10
# El número -5 multipicado por 3, da como resultado: -15
# El número -5 multipicado por 4, da como resultado: -20
# El número -5 multipicado por 5, da como resultado: -25
# El número -5 multipicado por 6, da como resultado: -30
# El número -5 multipicado por 7, da como resultado: -35
# El número -5 multipicado por 8, da como resultado: -40
# El número -5 multipicado por 9, da como resultado: -45
# El número -5 multipicado por 10, da como resultado: -50)


# tabla(0) ==(El número 0 multipicado por 1, da como resultado: 0
# El número 0 multipicado por 2, da como resultado: 0
# El número 0 multipicado por 3, da como resultado: 0
# El número 0 multipicado por 4, da como resultado: 0
# El número 0 multipicado por 5, da como resultado: 0
# El número 0 multipicado por 6, da como resultado: 0
# El número 0 multipicado por 7, da como resultado: 0
# El número 0 multipicado por 8, da como resultado: 0
# El número 0 multipicado por 9, da como resultado: 0
# El número 0 multipicado por 10, da como resultado: 0)


def main():
    print("Ejercicio a)")
    a = float(input("Ingresa el primer número: "))
    b = float(input("Ingresá el segundo número: "))
    suma, resta, multiplicacion, division = calculadora(a, b)
    print(
        f"\n La suma es {suma}. \n La resta es {resta}. \n La multiplicación es: {multiplicacion}. \n Por último, la división da como resultado: {division}"
    )

    print("\nEjercicio b)")
    n = int(input("Ingresé el número al que desea obtener la tabla de multiplicar: "))
    tabla(n)


if __name__ == "__main__":
    main()
