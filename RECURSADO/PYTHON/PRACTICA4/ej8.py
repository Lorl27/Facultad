# Ejercicio 8. Escribir un programa que le pida al usuario que ingrese una sucesión de números naturales
# (primero uno, luego otro, y así hasta que el usuario ingrese ’-1’ como condición de salida). Al final, el
# programa debe imprimir cuántos números fueron ingresados, la suma total de los valores y el promedio


def leer_centinela():
    return int(input("Ingrese un numero. (-1 para terminar)"))

def sucecion():
    num=leer_centinela()
    contador=0
    suma=0
    promedio=0
    while num != -1:
        suma+=num
        contador+=1
        num=leer_centinela()
    promedio= suma/contador
    return f"la cantidad de numeros ingresados fue de: {contador}, su suma fue:{suma} -> promedio:{promedio:0.2f}"


def main():
    print("La siguiente función le permitira ingresar todos los numeros necesarios y calcular su promedio:")
    resultado=sucecion()
    print(resultado)
    
if __name__=="__main__":
    main()