# -----------------------------------------------------
# ANTONELLA GRASSI -- 24/06/24
# PROGRAMACIÓN 2 - RECURSADO  --- TRABAJO PRÁCTICO NRO 2
# FCEIA - UNR
# -----------------------------------------------------

# ---------------------------------------------------------------------------
# Ejercicio 21. Diseñe un programa que permita clasificar 23 notas de un examen de distintos
# alumnos ingresadas por un auxiliar docente. Para ello, el docente estableció el siguiente criterio
# de aprobación, el cual él programa deberá imprimir, luego de cargada la nota.
# Nota Condición
# 1 ≤ nota < 4 Insuficiente
# 4 ≤ nota < 6 No Aprobado
# 6 ≤ nota < 8 Aprobado
# 8 ≤ nota < 10 Muy Bueno
# nota = 10 Excelente
# -----------------------------------------------------------------------------

# DISEÑO DE DATOS:
# nota: float
# Resultado de la función: str

# condiciones_notas: float->str
# Es una función auxiliar para la función "examen_notas", lo que hace es
# que según la nota introducida por el docente a cargo, devuelve la condición
# del alumno

# Propósito:
# Devolver la condición del alumno según qué nota se ha sacado

# EJEMPLOS:
# condiciones_notas(2)=="Insuficiente"
# condiciones_notas(10)=="Excelente"


def condiciones_notas(nota: float):
    if 1 <= nota < 4:
        return "Insuficiente"
    elif 4 <= nota < 6:
        return "No Aprobado"
    elif 6 <= nota < 8:
        return "Aprobado"
    elif 8 <= nota < 10:
        return "Muy Bueno"
    elif nota == 10:
        return "Excelente"
    else:
        return "Nota no válida, Ingrese una en el rango (1,10)"


# CASOS DE PRUEBA:
def test_condiciones_calculadora():
    assert condiciones_notas(10) == "Excelente"
    assert condiciones_notas(2.5) == "Insuficiente"
    assert condiciones_notas(8) == "Muy Bueno"
    assert condiciones_notas(0) == "Nota no válida, Ingrese una en el rango (1,10)"


# DISEÑO DE DATOS:
# Entrada del usuario (float) : nota
# Resultado de la función (str): condicion


# examen_notas: () -> None
# Es una función en la que el docente a cargo tiene que introducir
# la cantidad de alumnos que quiere evaluar y luego la nota de cada uno de ellos,
# Luego, el programa devolverá la condición de la materia basándose en esa nota

# Propósito:
# Solicitar al usuario la nota de cada alumno e imprimir su condición.


def examen_notas():
    for alumno in range(1, 23 + 1):
        print(f"Ingrese la nota del alumno nro: {alumno}")
        nota = float(input("NOTA: "))

        condicion = condiciones_notas(nota)
        print(f"Su condición es: {condicion}")


# CASOS DE PRUEBA:
# No se pueden realizar casos de prueba aquí ya que la función es interactiva


def main():
    print("Ingrese la nota de cada alumno para saber su condición:")
    examen_notas()


if __name__ == "__main__":
    main()
