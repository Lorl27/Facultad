# Ejercicio 6. Nos piden que escribamos una función que le pida al usuario que ingrese un número positivo.
# Si el usuario ingresa cualquier número que no sea lo pedido, se le debe informar de su error mediante un
# mensaje y volverle a pedir el número.
# Resolver este problema usando:
# (a) Un ciclo interactivo.
# (b) Un ciclo con centinela.
# ¿Tendría sentido hacerlo con ciclo denido? Justificar.

#a:

def ciclointeractivo():
    hay_mas_datos = "Si"
    
    while hay_mas_datos == "Si":
        num = int(input("Ingrese un numero positivo: "))
        
        if num < 0:
            print("Error: El número ingresado no es positivo. Inténtalo de nuevo.")
            continue
        
        hay_mas_datos = input("Quiere seguir? <Si-No>: ")

#b:

def leer_centinela():
    return input("Ingrese un numero (* para terminar): ")

def ciclocentinela():
    centinela = leer_centinela()
    
    while centinela != "*":
        num = int(centinela)
        
        if num <0:
            print("Error: Debe ingresar un número positivo.")
            
        centinela = leer_centinela()


def main():
    print("elige entre 1 ó 2.","1:interactivo","2:centinela",sep=";\t\t\n")
    eleccion:int=int(input("_ "))
    if eleccion==2:
        ciclocentinela()
    elif eleccion==1:
        ciclointeractivo()
    else:
        print("valor no comprendido.inepto")
    
if __name__=="__main__":
    main()