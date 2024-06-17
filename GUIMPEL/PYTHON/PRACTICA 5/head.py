# Ejercicio 1. Escriba un programa llamado head.py que reciba un archivo y un número N e
# imprima las primeras N líneas del archivo.

import os
ruta=os.path.dirname(os.path.abspath(__file__))

def heady(txt,n:int):
    archivo=open(ruta+txt,"r")
    contador=0

    while n >contador:
        print(archivo.readline())
        contador+=1

    archivo.close()


heady("\\archivos\\lineasRandom.txt",3)
#head("\\lineasRandom.txt",5)