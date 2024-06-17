#Ejercicio 9. Modificar el programa anterior para que el usuario también ingrese:
# a) la cantidad de veces que desea que se repita la palabra dada.
# b) el separador entre cada repetición de la palabra

def impresion2():
    palabra=input("SI: ")
    rep_palabra=int(input("Ingrese cant veces  u want that word: "))
    sep_palabra=(input("INgrese el separador 0W0: "))

    resultado=""
    for  x in range(rep_palabra):
        resultado+=palabra
        if x<rep_palabra-1:
            resultado+=sep_palabra
    print(resultado)



impresion2()