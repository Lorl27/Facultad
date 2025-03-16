# Ejercicio 7. Escribir un programa que permita al usuario ingresar un conjunto de notas, preguntando a
# cada paso si desea ingresar más notas, e imprimiendo el promedio correspondiente, al finalizar la toma de
# datos

def notas():
    hay_mas_notas="si"
    cantidad=0
    sumatoria=0
    promedio=0
    while hay_mas_notas=="si":
        nota=int(input("Ingrese un numero: "))
        cantidad+=1
        sumatoria+=nota
        hay_mas_notas=input("¿Desea agregar más notas: <si-no>?").lower()
        
    promedio=sumatoria/cantidad
    return f"La cantidad de notas ingresadas fue de {cantidad}, su suma fue {sumatoria} y el promedio es: {promedio:0.2f} "   


def main():
    print("El siguiente programa le permitira ingresar cuantas notas desee, hasta que indique lo contrario:")
    resultado=notas()
    print(resultado)
    
if __name__=="__main__":
    main() 