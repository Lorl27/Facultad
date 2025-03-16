import sys # para acceder a los argumentos del programa
from typing import IO # importo el tipo de los archivos abiertos

# Toma una variable de tipo FILE y un entero N e imprime por 
# pantalla las primeras N líneas del archivo, o hasta que se 
# termine si no tiene N líneas
def head (a : IO, n : int) -> None : 
    linea = a.readline()
    i = 0
    while (i < n and linea != ""):
        print(linea)
        linea = a.readline() 
        i += 1

# Función principal del programa.
# Se encarga de extraer los argumentos del programa y llamar
# a la función head 
def main () -> int:
    if (len(sys.argv) != 3): 
        print("Número de argumentos incorrecto.")
        return 1    
    
    # en la posición 0 de sys.argv siempre está el nombre del 
    # programa, en este caso sys.argv[0] == "head.py"

    nombre_archivo = sys.argv[1]
    archivo = open(nombre_archivo,"r")

    n = int(sys.argv[2])

    head(archivo, n)

    archivo.close() 

    return 0

# Acá le digo a python que la función principal 
# de mi programa es main.
if __name__ == "__main__":
    main()