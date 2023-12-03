# Ejercicio 3. Escribir un programa llamado wc.py que reciba un archivo, lo procese e imprima
# por pantalla cuántas líneas, cuántas palabras y cuántos caracteres tiene.

import os

ruta=os.path.dirname(os.path.abspath(__file__))

def info(txt):
    archivo=open(ruta+txt,"r")
    
    lineas=archivo.readlines()
    palabras=0
    
    longit_c=[]
    line=[]
    algo=[]
    palabra=[]
    
    for palabritas in lineas:
        if palabritas not in ["\n"]:
            longit_c.append(len(palabritas)-1) #asi quitamos el salto de linea [CARACTERES]
            line.append(palabritas) #[LINEAS]
            
    carac=sum(longit_c)
    l=len(line)  

    for txt in line:
        algo.append(txt.split()) #los seprara x oracion
        palabra.append(len(algo)) #cuenta la longitud de la oracion (cant palabras x oracion)

    palabras=sum(palabra) #suma todas las longiutdes de las oraciones

    
    print(f"La cantidad de líneas que tiene es {l} , la de palabras {palabras} , y la de caracteres es {carac} ")
    
    archivo.close()
    
info("\\archivos\\lineasRandom.txt")
    