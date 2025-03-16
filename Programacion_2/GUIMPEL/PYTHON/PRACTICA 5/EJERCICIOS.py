# 1. Archivos

# Ejercicio 1. Escriba un programa llamado head.py que reciba un archivo y un número N e
# imprima las primeras N líneas del archivo.

# Ejercicio 2. Escriba un programa llamado cp.py que copie todo el contenido de un archivo a
# otro, de modo que quede exáctamente igual. Observación: usar archivo.read(bytes) para leer
# como máximo una cantidad de bytes.

# Ejercicio 3. Escribir un programa llamado wc.py que reciba un archivo, lo procese e imprima
# por pantalla cuántas líneas, cuántas palabras y cuántos caracteres tiene.

# Ejercicio 4. Escriba un programa llamado grep.py que reciba una expresión y un archivo e
# imprima por pantalla las líneas del archivo que contienen la expresión recibida.

# Ejercicio 5. Escriba un programa llamado rot13.py que reciba un archivo de texto de origen
# y uno de destino, de modo que para cada línea del archivo origen, se guarde una línea cifrada
# en el archivo destino. El algoritmo de cifrado será muy sencillo: a cada caracter comprendido
# entre la a y la z, se le suma 13 y luego se aplica el módulo 26, para obtener un nuevo caracter.

# Ejercicio 6. Persistencia de un diccionario
# a) Escriba una función cargarDatos que reciba un nombre de archivo cuyo contenido tiene
# el formato clave, valor en cada línea y devuelva un diccionario con el primer campo como
# clave y el segundo como valor.

import os
ruta=os.path.dirname(os.path.abspath(__file__))
#clave-valor

def cargarDatos(name)->dict:
    
    archivo=open(ruta+name,"r")
    
    dic={}
    
    for x in archivo:
        if x not in ["\n",".",":"]:
            sep=x[:-1].split(",") #eliminados saltos y cosas no deseadas
            dic[sep[0]]=sep[1]

    archivo.close()
    
    return dic

print(cargarDatos("\\archivos\\dicciona.txt"))

# b) Escriba una función guardarDatos que reciba un diccionario y un nombre de archivo y
# guarde el contenido del diccionario en el archivo, con el formato clave, valor.

def guardarDatos(name,dicco):
    archivo=open(ruta+name,"w")
    for x,y in dicco.items():
        archivo.write(f"{x},{y}\n")
    archivo.close()
    
dick={
    "nombre": "Juan",
    "edad": 30,
    "ciudad": "Ejemploville",
    "puntuacion": 95.5,
    "activo": True
}
guardarDatos("\\archivos\\ejercicioFinal.txt",dick)