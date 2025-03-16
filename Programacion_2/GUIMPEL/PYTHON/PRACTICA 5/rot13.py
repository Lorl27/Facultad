# Ejercicio 5. Escriba un programa llamado rot13.py que reciba un archivo de texto de origen
# y uno de destino, de modo que para cada línea del archivo origen, se guarde una línea cifrada
# en el archivo destino. El algoritmo de cifrado será muy sencillo: a cada caracter comprendido
# entre la a y la z, se le suma 13 y luego se aplica el módulo 26, para obtener un nuevo caracter.
#ROT13 = CIFRADE DE CÉSAR * 13
import os
ruta=os.path.dirname(os.path.abspath(__file__))

def cifrado(letra):
    abecedario="abcdefghijklmnñopqrstuvwxyz"
    if letra.isalpha():
        letra=letra.lower()
        indice=abecedario.index(letra)
        cuenta =(indice + 13) % 26
        new_l=abecedario[cuenta]
    else:
        new_l=letra
    return new_l

def rota(txtO,txtD):
    origen=open(ruta+txtO,"r")
    destino=open(ruta+txtD,"w")

    for lineas in origen:
        cif="".join([cifrado(caracter) for caracter in lineas])
        destino.write(cif)

    origen.close()
    destino.close()


rota("\\archivos\\cifra.txt","\\archivos\\epty.txt")