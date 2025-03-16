#-----------------------------------------------------
# ANTONELLA GRASSI -- 24/06/24
# PROGRAMACIÓN 2 - RECURSADO  --- TRABAJO PRÁCTICO NRO 2
# FCEIA - UNR
#-----------------------------------------------------

#---------------------------------------------------------------------------
# Ejercicio 22.
# a) Teniendo en cuenta lo realizado en el programa anterior, diseñar ahora una programa
# clasificar 10 notas, donde ahora la nota se obtendrá a partir del promedio de las tres notas
# obtenidas por el estudiante en el cuatrimestre. Así, el docente ingresará las tres notas
# del alumno 1, y el programa clasificará el promedio (previo cálculo) utilizando el criterio
# explicado en el ejercicio anterior. Luego, ingresará la notas del alumno 2, y clasificará el
# promedio, y así sucesivamente, hasta completar con la clasificación de los 10 alumnos
# b) ¿Qué modificaciones realizaría en su programa si el docente ahora toma 4 parciales durante el cuatrimestre?
# ¿Y si ingresa 7 notas por alumno?
# c) ¿Qué modificaciones realizaría en su programa si el docente ahora recibe 15 alumnos?
# ¿Y si debe las notas de 50 alumnos?
#-----------------------------------------------------------------------------

# DISEÑO DE DATOS:
# nota: float
# Resultado de la función: str

#condiciones_notas: float->str
#Es una función auxiliar para la función "examen_notas", lo que hace es
# que según la nota introducida por el docente a cargo, devuelve la condición 
# del alumno

#Propósito:
# Devolver la condición del alumno según qué nota se ha sacado

#EJEMPLOS:
# condiciones_notas(2)="Insuficiente"
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
        return ("Nota no válida, Ingrese una en el rango (1,10)")
        nota = int(input("Ingresala nuevamente: "))
        return condiciones_notas(nota)

#CASOS DE PRUEBA:
def test_condiciones_calculadora():
    assert condiciones_notas(10)=="Excelente"
    assert condiciones_notas(2.5)=="Insuficiente"
    assert condiciones_notas(8)=="Muy Bueno"

# DISEÑO DE DATOS:
# cantidad_de_parciales: int
# cantidad_de_notas: int
# Resultado de la función: str

#examen_notas: int int-> str
#Es una función en la que el docente a cargo tiene que introducir
# la cantidad de parciales que ha evualuado y 
# la cantidad de notas (es decir, de alumnos que realizaron el examen) que debe evaluar,
# para así poder ingresar las notas de los parciales a cada alumno y obtener
# su condición en la materia en base a su promedio(resultante de las notas ingresadas)

#Propósito:
# Devolver la condición del alumno según qué notas se ha sacado en los parciales realizados
# (Sirve para un amplio número de alumnos)

def examen_notas(cantidad_de_parciales: int, cantidad_de_notas: int):
    
    if cantidad_de_notas<=0 or cantidad_de_parciales<=0:
        print("Error. La cantidad de notas/parciales no puede ser evaluda")
        cantidad_de_parciales=int(input("Ingrese cantidad de parciales a evaluar: "))
        cantidad_de_notas=int(input("Ingrese la cantidad de notas(alumnos) a evaluar: "))
        return examen_notas(cantidad_de_parciales,cantidad_de_notas) #para que no se rompa la función, como aún no aprendimos a usar un Ciclo While o las Excepciones, así el código es continúo.
    
    for alumno in range(1, cantidad_de_notas + 1):
        print(f"Ingrese las notas del alumno nro: {alumno}")
        
        suma_notas = 0
        
        for parcial in range(1, cantidad_de_parciales + 1):
            nota = float(input(f"Nota {parcial}: "))
            suma_notas += nota
            
        promedio = suma_notas / cantidad_de_parciales

        condicion = condiciones_notas(promedio)
        print(f"Su condición es: {condicion}, promedio={promedio:0.2f}")


def main():
    print(
        """El siguiente programa, le permitirá ingresar las notas correspondientes a c/u de los alumnos,
            según la cantidad de parciales que ha tomado, luego calculará su condición en la materia,
            respecto al promedio que obtuvo el alumno."""
    )
    cantidad_parciales = int(
        input("Ingrese la cantidad de parciales a tener en cuenta por alumno: ")
    )
    cantidad_notas = int(input("Ingrese la cantidad de notas para clasificar(cantidad de alumnos): "))
    
    examen_notas(cantidad_parciales, cantidad_notas)


if __name__ == "__main__":
    main()
