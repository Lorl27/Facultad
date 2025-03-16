# Ejercicio 1. Escribir un ciclo definido para imprimir por pantalla todos los números entre 10 y 20.


def numbers():
    for x in range(10,20+1):
        print(x)
        
def main():
    numbers()
        
if __name__=="__main__":
    main()