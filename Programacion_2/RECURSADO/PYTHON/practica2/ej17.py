# 2.2. Revisitando problemas de Racket
# Reprogramar cada uno de los siguientes ítems. Estos problemas ya fueron resueltos el
# cuatrimestre pasado utilizando el lenguaje Racket. Repensarlos en esta oportunidad utilizando
# el lenguaje Python, reutilizando la receta de los mismos. ¿Cúanto nos sirve de lo ya hecho?


# Ejercicio 17.
# a) Defina la función vol-cubo que recibe la longitud de la arista de un cubo y calcula su
# volumen.

# b) Defina la función area-cubo que recibe la longitud de la arista de un cubo y calcula su
# área.

# c) Defina una función que según el valor que ingrese por el usuario, se calcule el volumen,
# o el área de un cubo. Tener en consideración un valor por defecto, si el valor ingresado
# no fuera el adecuado, en dicho caso deberá calcular el área de un cubo. Reutilizar las
# funciones de los ítems anteriores.

# d) Modifique la función definida en ítem anterior para que, en caso de no recibir un valor
# apropiado nos muestre el siguiente mensaje en pantalla "Valor no soportada por la función.".

# Nota: en todos los casos validar los datos de entrada, por ejemplo, es un error que la arista de un
# cubo sea 0 o un valor negativo, en dichos casos puede considerar retornar un mensaje de error,
# como por ejemplo, “Valores de Entrada Inválidos” o para no modificar el tipo de dato de retorno
# de cada función, para que contenga además String, retorna un número negativo, el cual es inválido como resultado válido, y la funciones futuras que utilizan a ésta puede determinar así
# que se trata de un error


# ; La arista es el lado común entre 2 caras, el cubo tiene 6 caras.
# ; Para calcular el volumén del cubo se debe hacer: arista * arista * arista
def vol_cubo(arista: float):
    return arista**3


# ; La arista es el lado común entre 2 caras, el cubo tiene 6 caras.
# ; Para calcular el área de una arista: arista * arista
# ; Para calcular el área del cubo se debe hacer: (arista * arista) * 6
def area_cubo(arista: float):
    return (arista**2) * 6


def validar_v(arista: float):
    if 0 < arista:
        return True
    else:
        raise ValueError(f"EL VALOR INTRODUCIDO ({arista}) ES INVALIDO.")


def main():
    while True:
        try:
            aristal = float(input("Ingresa la loingitud en cm de la arista: "))
            validar_v(aristal)
            print(
                "Puedes elegir entre calcular al área o el volumen del cubo gracias a tu arista,"
            )
            usuario = input(
                """ELIGE 
                            1: VOLUMEN
                            2: ÁREA"""
            )
            if usuario == "1":
                vol = vol_cubo(aristal)
                print(f"Tu arista es de {aristal} cm ==> volumen: {vol}")
            else:
                ar = area_cubo(aristal)
                print(f"Tu arista es de {aristal} cm ==> area: {ar}")
            break
        except ValueError as x:
            print(f"error: {x}")


if __name__ == "__main__":
    main()
