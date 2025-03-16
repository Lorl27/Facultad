# Ejercicio 7. Diseñar una implementación propia de la función abs, que devuelva el valor
# absoluto de cualquier valor que reciba.


def ejercicio7(x: float):
    if x < 0:
        return x * -1
    else:
        return x


def main():
    value = int(input("choose your number here: "))
    v = ejercicio7(value)
    print(f"el número {value} ha sido convertido a {v}")


if __name__ == "__main__":
    main()
