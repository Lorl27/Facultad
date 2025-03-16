# Ejercicio 13. Modificar el programa anterior para satisfacer los siguientes requerimientos:
# a) Se diferencia una categoría más, ahora si la temperatura esta entre 25 y 32 grados el
# mensaje deberá ser “Caluroso", pero si la temperatura excede los 32 grados deberá decir
# "Muy caluroso".
# b) Se establece un nuevo criterio de clasificación:
# Intervalo Denominación
# menos de 0 grados "Helado"
# entre 0 y 10 grados "Frío"
# entre 10 y 15 grados “Fresco”
# entre 15 y 25 grados “Agradable”
# entre 25 y 32 grados “Caluroso”
# más de 32 grados “ Muy Caluroso”
# Modificar el programa para que se adapte a este cambio.
# c) El programa ahora deberá avisarnos si es necesario utilizar protector solar o no. Para ello,
# se sabe que, si la temperatura es menor a los 15 no es necesario utilizar protector solar,
# pero por el contrario si la temperatura supera dicho valor, si se debe utilizar protector.
# d) ¿Todas las modificaciones que hicimos sobre nuestro programa fueron iguales? Existe
# alguna diferencia entre ellas. Explicar.


def funcion_clima(temperatura:int):
    if 0>temperatura:
        print("Helado")
    elif 0<= temperatura <10:
        print("Frío")
    elif 10<= temperatura<15:
        print("Fresco")
    elif 15<= temperatura <25:
        print("Agradable")
    elif 25<= temperatura <32:
        print("Caluroso")
    else:
        print("Muy Caluroso")
        
    if temperatura>15:
        print("Necesitas llevar protector solar.")

def main():
    temp=int(input("Ingrese su temp: "))
    print("El clima es: ")
    funcion_clima(temp)
    
if __name__=="__main__":
    main()