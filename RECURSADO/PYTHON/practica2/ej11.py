# Ejercicio 11. Usando las funciones del ejercicio anterior, escribir un programa que pida al
# usuario dos intervalos expresados en horas, minutos y segundos, sume sus duraciones, y
# muestre por pantalla la duración total en horas, minutos, y segundos.


def segundo_valido(segundo: int):
    if 0 <= segundo <= 59:
        return True
    else:
        raise ValueError(
            f"Los segundos ({segundo}) que has ingresado NO son válidos. revisá..."
        )


def minuto_valido(minuto: int):
    if 0 <= minuto <= 59:
        return True
    else:
        raise ValueError(
            f"Los minutos ({minuto}) que has ingresado NO son válidos. revisá..."
        )


def segundos_conversion(horas: int, minutos: int, segundos: int):
    resultado = segundos
    minutos_a_segundos = minutos * 60
    horas_a_segundos = horas * 3600
    resultado += minutos_a_segundos + horas_a_segundos

    return resultado


def hora_normal_conversion(segundos: int):

    horas = segundos // 3600
    segundos_restantes = segundos % 3600

    minutos = segundos_restantes // 60
    segundos_restantes %= 60

    if segundos_restantes > 59:
        minutos += 1
        segundos_restantes = 0

    elif minutos > 59:
        horas += 1
        minutos = 0

    return (horas, minutos, segundos_restantes)


def main():
    print("sumaremos 2 horas:")

    while True:
        try:
            print("Ingrese la primera hora:")

            segundos = int(input("Ingresa los segundos: "))
            minutos = int(input("Ingresa los minutos: "))
            horas = int(input("Ingresa las horas: "))

            # validar:
            segundo_valido(segundos)
            minuto_valido(minutos)

            hora_1 = segundos_conversion(horas, minutos, segundos)

            print("Ingrese la segunda hora:")

            segundos_2 = int(input("Ingresa los segundos: "))
            minutos_2 = int(input("Ingresa los minutos: "))
            horas_2 = int(input("Ingresa las horas: "))

            # validar:
            segundo_valido(segundos_2)
            minuto_valido(minutos_2)

            hora_2 = segundos_conversion(horas_2, minutos_2, segundos_2)

            desconversion = hora_normal_conversion((hora_1 + hora_2))

            print(
                f"El resultado de sumar {hora_1} y {hora_2} segundo(s) / ({horas},{minutos},{segundos}) y ({horas_2},{minutos_2},{segundos_2}) ==> {desconversion}"
            )
            break

        except ValueError as x:
            print(f"Error: {x}")


if __name__ == "__main__":
    main()
