
# Ejercicio 15. Programa de astrología: el usuario debe ingresar el día y mes de su cumpleaños
# y el programa le debe decir a qué signo corresponde.
# Aries: 21 de marzo al 20 de abril. Tauro: 21 de abril al 20 de mayo.
# Geminis: 21 de mayo al 21 de junio. Cancer: 22 de junio al 23 de julio.
# Leo: 24 de julio al 23 de agosto. Virgo: 24 de agosto al 23 de septiembre.
# Libra: 24 de septiembre al 22 de octubre. Escorpio: 23 de octubre al 22 de noviembre.
# Sagitario: 23 de noviembre al 21 de diciembre. Capricornio: 22 de diciembre al 20 de enero.
# Acuario: 21 de enero al 19 de febrero. Piscis: 20 de febrero al 20 de marzo.


def signo_zodiaco(dia, mes):
    if (mes == 3 and dia >= 21) or (mes == 4 and dia <= 20):
        return "Aries"
    elif (mes == 4 and dia >= 21) or (mes == 5 and dia <= 20):
        return "Tauro"
    elif (mes == 5 and dia >= 21) or (mes == 6 and dia <= 21):
        return "Géminis"
    elif (mes == 6 and dia >= 22) or (mes == 7 and dia <= 23):
        return "Cáncer"
    elif (mes == 7 and dia >= 24) or (mes == 8 and dia <= 23):
        return "Leo"
    elif (mes == 8 and dia >= 24) or (mes == 9 and dia <= 23):
        return "Virgo"
    elif (mes == 9 and dia >= 24) or (mes == 10 and dia <= 22):
        return "Libra"
    elif (mes == 10 and dia >= 23) or (mes == 11 and dia <= 22):
        return "Escorpio"
    elif (mes == 11 and dia >= 23) or (mes == 12 and dia <= 21):
        return "Sagitario"
    elif (mes == 12 and dia >= 22) or (mes == 1 and dia <= 20):
        return "Capricornio"
    elif (mes == 1 and dia >= 21) or (mes == 2 and dia <= 19):
        return "Acuario"
    elif (mes == 2 and dia >= 20) or (mes == 3 and dia <= 20):
        return "Piscis"
    else:
        return "Fecha no válida"


def main():
    dia = int(input("Ingresa el día de tu cumpleaños: "))
    mes = int(input("Ingresa el mes de tu cumpleaños (en número): "))
    
    signo = signo_zodiaco(dia, mes)
    print(f"Tu signo del zodíaco es: {signo}")


if __name__ == "__main__":
    main()
