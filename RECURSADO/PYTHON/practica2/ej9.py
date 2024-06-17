# Ejercicio 9. Diseñar funciones que resuelvan los siguientes problemas:
# a) Dado un año indicar si es bisiesto.
# Nota: un año es bisiesto si es un número divisible por 4, pero no si es divisible por 100,
# excepto que también sea divisible por 400.
# b) Dado un mes, devolver la cantidad de días correspondientes.
# c) Dado un mes, representado como un número, devolver el mes asociado en palabras. Así
# para el valor 1 la función devolverá, “Enero”, y para 4 devolverá “Abril”, etc.
# d) Traducir una fecha dado su mes en formato numérico, a una fecha con su mes escrito en
# palabras. Por ejemplo, para fecha_palabra(1,3,2019) una traducción posible es "1
# de Marzo de 2019".
# Nota: en todos los casos, invocar las funciones escritas previamente cuando sea posible,
# y validar los datos de entrada.


# ERRORES:
def dia_valido(dia: int):
    if 1 <= dia <= 31:
        return True
    else:
        raise ValueError(f"El día ingresado ({dia}) no es válido.")


def mes_valido(mes: int):
    if 1 <= mes <= 12:
        return True
    else:
        raise ValueError(f"El mes ingresado ({mes}) no es válido.")


def anio_valido(anio: int):
    if 1000 <= anio <= 9999:
        return True
    else:
        raise ValueError(f"El año ingresado ({anio}) no es válido.")


def bisisesto(anio: int):
    return (anio % 4 == 0 and anio % 100 != 0) or (anio % 400 == 0)


def dias_del_mes(mes: str, anio: int):
    if mes.lower() in ["enero", "marzo", "julio", "agosto", "octubre", "diciembre"]:
        return 31
    elif mes.lower() == "febrero":
        if bisisesto(anio):
            return 29
        else:
            return 28
    else:
        return 30


def dias_del_mes_num(mes: int):
    lista_meses = [
        "enero",
        "febrero",
        "marzo",
        "abril",
        "mayo",
        "junio",
        "julio",
        "agosto",
        "septiembre",
        "octubre",
        "noviembre",
        "diciembre",
    ]

    if 1 <= mes <= 12:
        return lista_meses[mes - 1]
    else:
        raise ValueError(f"El número de mes ingresado ({mes}) no es válido.")


def fecha_numero_a_fecha_escrita(dia: int, mes: int, anio: int):
    try:
        dia_valido(dia)
        mes_valido(mes)
        anio_valido(anio)

        if dia > dias_del_mes(dias_del_mes_num(mes), anio):
            raise ValueError(
                f"El día ({dia}) no es válido para el mes ingresado ({dias_del_mes_num(mes)})."
            )

        return f"{dia} de {dias_del_mes_num(mes)} de {anio}"

    except ValueError as e:
        return str(e)


def main():
    print("Veremos la fecha en formato escrito.")
    while True:
        try:
            dia = int(input("Ingresa el día: "))
            mes = int(input("Ingresa el mes: "))
            anio = int(input("Ingresa el año: "))

            # Verificar la validez de la fecha
            dia_valido(dia)
            mes_valido(mes)
            anio_valido(anio)

            # Llamar a la función para obtener la fecha en formato escrito
            value = fecha_numero_a_fecha_escrita(dia, mes, anio)

            # Imprimir el resultado
            print(f"Ingresaste {(dia, mes, anio)} ==> {value}")
            break
        except ValueError as e:
            # Capturar cualquier error de validación y proporcionar una sugerencia
            print(f"Error: {e}Intenta nuevamente con una fecha válida.")

            # Sugerir una fecha válida modificada
            if "día" in str(e):
                if dia > 31:
                    dia = 1
                    if mes == 12:
                        mes = 1
                        anio += 1
                    else:
                        mes += 1
                else:
                    dia += 1

            elif "mes" in str(e):
                if mes > 12:
                    mes = 1
                    anio += 1
                else:
                    mes += 1
                    dia = 1

            elif "año" in str(e):
                anio += 1
                mes = 1
                dia = 1

            print(f"Sugerencia: Prueba con {(dia, mes, anio)}")


if __name__ == "__main__":
    main()
