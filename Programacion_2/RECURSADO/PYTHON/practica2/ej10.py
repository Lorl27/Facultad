# Ejercicio 10. Diseñar dos funciones que permitan calcular:
# a) La duración en segundos de un intervalo dado en horas, minutos, y segundos.
# b) La duración en horas, minutos y segundos de un intervalo dado en segundos.
# Nota: en todos los casos validar los datos de entrada, los segundos los minutos deben estar
# comprendidos entre 0 y 59 inclusive, para las horas no pondremos restricciones.


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
    print("Convertiremos la hora normal a solo de segundos: ")
    print("Y luego, haremos al revés: ")

    while True:
        try:

            segundos = int(input("Ingresa los segundos: "))
            minutos = int(input("Ingresa los minutos: "))
            horas = int(input("Ingresa las horas: "))

            # validar:
            segundo_valido(segundos)
            minuto_valido(minutos)

            conversion = segundos_conversion(horas, minutos, segundos)

            print(
                f"Has ingresado {horas} hora(s) con {minutos} mintuo(s) y {segundos} segundo(s) ==> {conversion} segundos totales"
            )

            segundos = int(input("Ingresa los segundos, para pasar a hora classic: "))

            desconversion = hora_normal_conversion(segundos)

            print(
                f"Lo(s) segundo(s) ingresado(s) fueron: {segundos} ==> {desconversion}"
            )
            break

        except ValueError as x:
            print(f"Error: {x}")


if __name__ == "__main__":
    main()
