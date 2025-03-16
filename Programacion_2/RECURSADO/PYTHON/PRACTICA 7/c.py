import codecs

#La función open recibe un parámetro opcional para indicar el modo en que se abrirá el archivo. Existen tres:
# Lectura : r
# Escritura: w
# Agregado: a

# Ejemplo:Abrir un archivo y eliminar los espacios en blanco que quedan agregados a las strings.
# almacenado en utf-8
#file_in = codecs.open("martin-fierro.txt", "r", "utf8")
#linea = file_in.readline()
#print(linea.rstrip())
#while linea != '':
#procesar linea
#    linea = file_in.readline()
#    print(linea.rstrip())# para eliminar los espacios en blancos, incluídos los saltos de lineas
#file_in.close()

#espera=input("")

# Versión for
#file_in = codecs.open("martin-fierro.txt", "r", "utf8")
#almacenado en utf-8
#for linea in file_in:
#    print(linea.rstrip("\n"))# para eliminar los salto de linea
#file_in.close()

#espera=input("")

# Ejemplo 2: Imprimir número de linea y la linea del archivo
# Versión 1:
#almacenado en utf-8
#file_in = codecs.open("martin-fierro.txt", "r", "utf8")
#i=1
#for linea in file_in:
#    linea= linea.rstrip("\n") # para eliminar los saltos de linea
#    print("Linea ", i, ":", linea)
#    i+=1
#file_in.close()
#espera = input("")

def longitud_palabras(linea):
    count=0
    for x in linea:
        if x ==" ":
         count+=1
    return count

#Versión 2: usando enumerate
file_in = codecs.open("martin-fierro.txt", "r", "utf8")
for i, linea in enumerate(file_in):
    linea = linea.rstrip("\n")  # para eliminar los salto de linea
    l=longitud_palabras(linea)
    print("Linea ", i+1, ":", linea,"longitud=",len(linea),"cantidad de palabras:",l)
file_in.close()
espera = input("")

#Tarea RIGHT NOW!:
#a) Agregar información no sólo sobre la línea que se imprime, sino también la longitud de la linea (cantidad de letras)
#b) Agregar información sobre la cantidad de palabras que tiene la linea.