# Ejercicio 4. Escriba un programa llamado grep.py que reciba una expresión y un archivo e
# imprima por pantalla las líneas del archivo que contienen la expresión recibida.

import os
ruta=os.path.dirname(os.path.abspath(__file__))

def exp(txt,expresion):
    archivo=open(ruta+txt,"r")
    
    for x in archivo:
        if x.find(expresion)!= -1:
            print(x)
            
exp("\\archivos\\lineasRandom.txt","no")