# We are given n arrays of any size which may have common elements, we need to combine all these arrays
# in such a way that each element should occurs only once and elements
# should be in sorted order? Examples:

# Input : arr = [[1, 2, 2, 4, 3, 6],
#               [5, 1, 3, 4],
#               [9, 5, 7, 1],
#               [2, 4, 1, 3]]
# Output : [1, 2, 3, 4, 5, 6, 7, 9]

# def settolist(seti:set)->list:
#     l=[]
#     for x in seti:
#         l.append(x)
#     return l

# print(settolist({1,3,4,6,7,9,0}))

# def ameli(listaM:list)->list:
#     s=set()
#     for lista in listaM:
#         s.update(lista)
#     return settolist(s)

# print(ameli([[1,2,2,4,3,6],[5, 1, 3, 4],[9, 5, 7, 1],[2, 4, 1, 3]]))

# # Input :
# lst1 = [4, 9, 1, 17, 11, 26, 28, 54, 69]
# lst2 = [9, 9, 74, 21, 45, 11, 63, 28, 26]
# # Output :
# # [9, 11, 26, 28]

# def inter(l1:list,l2:list)->list:
#     s1=set(l1)
#     s2=set(l2)
#     return settolist(s1&s2)

# print(inter(lst1,lst2))

# ---------------------------------------------

import random

palabras_posibles = ("buenas", "tardes", "como", "te", "va")


def elegirPalabra(coleccion_palabras: tuple) -> str:
    if isinstance(coleccion_palabras, tuple):
        palabra_r = random.choice(coleccion_palabras)
        return palabra_r


def buscarPosiciones(letra: str, palabra: str) -> list:
    posiciones = []
    largo = len(palabra)

    for indice in range(largo):
        if letra == palabra[indice]:
            posiciones.append(indice)

    return posiciones


def actualizarPalabra(palabra: str, posiciones: list) -> str:
    resultado = list(palabra)
    largo = len(palabra)
    for indice in range(largo):
        if indice not in posiciones:
            resultado[indice] = "_"

    return "".join(resultado)


def ahorcado(coleccion_palabras: tuple) -> str:
    max = 7
    intentos = 0
    letras_usadas = []
    alfabeto = "abcedfghijklmnñopqrstuvwxyz"
    palabra_random = elegirPalabra(coleccion_palabras)
    while intentos < max:
        letra_usu = input("Ingrese una letra: ")
        while letra_usu not in alfabeto:
            letra_usu = input("Has ingresado un caracter incorrecto.Intente de nuevo: ")
        while letra_usu in letras_usadas:
            letra_usu = input("Esa letra ya esta usada. ingrese otra: ")
        else:
            letras_usadas.append(letra_usu)

        posiciones_palabra = buscarPosiciones(letra_usu, palabra_random)
        palabra_modificada = actualizarPalabra(palabra_random, posiciones_palabra)

        print(palabra_modificada)

        if palabra_modificada == palabra_random:
            return "has ganado el juego"
        else:
            print("Letra no presente en la palabra.")
            intentos += 1
    return "Has perdido el juego"


print(ahorcado(palabras_posibles))
