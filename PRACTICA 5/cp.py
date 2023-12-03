# Ejercicio 2. Escriba un programa llamado cp.py que copie todo el contenido de un archivo a
# otro, de modo que quede exáctamente igual. Observación: usar archivo.read(bytes) para leer
# como máximo una cantidad de bytes.

import os
ruta=os.path.dirname(os.path.abspath(__file__))

def copy(txt):
    archivo=open(ruta+txt,"r")
    copia=open(ruta+"copia.txt","w")
    
    lineas=archivo.readlines()
    copia.writelines(lineas)
    
    archivo.close()
    copia.close()
    
copy("\\archivos\\lineasRandom.txt")