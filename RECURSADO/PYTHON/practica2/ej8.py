# Ejercicio 8. Diseñar un programa, que utilizando funciones matemáticas, calcule las raíces
# reales (no las complejas) de un polinomio de segundo grado.

# Nota: validar que las operaciones puedan efectuarse antes de realizarlas (no dividir por cero,ni
# calcular la raíz de un número negativo). La función no tienen que devolver nada, simplemente
# puede mostrar por pantalla el resultado del cálculo.


from fractions import Fraction

# Convertir un número decimal a fracción
# numero_decimal = 0.75
# fraccion = Fraction(numero_decimal).limit_denominator()

# print(fraccion)


def raiz(n):
    return n ** (1 / 2)


def ej8(a, b, c):
    determinante = b**2 - 4 * a * c

    if a == 0:
        print("Tu UNICA raiz es x=0")
        return

    if determinante < 0:
        print("Tienes raíces complejas. No es posible su cálculo.")
        return

    x1 = (-b + raiz(determinante)) / (2 * a)
    x2 = (-b - raiz(determinante)) / (2 * a)

    if determinante == 0:
        print("Tienes una raíz doble:")
        return str(Fraction(x1).limit_denominator())
    else:
        print("Tienes dos raíces diferentes:")
        return str(Fraction(x1).limit_denominator()), str(
            Fraction(x2).limit_denominator()
        )


def main():
    print("Elige tu polinomio, pon solo los coeficientes!")
    a = float(input("a = "))
    b = float(input("b = "))
    c = float(input("c = "))
    ej = ej8(a, b, c)
    # if isinstance(ej, tuple):  # Verifica si hay dos raíces
    #     ej = tuple(map(lambda x: str(Fraction(x).limit_denominator()), ej))  # Convierte ambas raíces a fracciones
    # else:
    #     ej = str(ej)
    print(ej)


if __name__ == "__main__":
    main()
