# Ejercicio 4. Escriba un programa que contenga la función que reciba como parámetro una
# cadena de palabras separadas por espacios y devuelva, como resultado, cuántas palabras de
# más de cinco letras tiene la cadena dada

def ej4(cadena:str):
    contador=0
    cadena=cadena.lower()
    for x in cadena:
        if x==" ":
            if len(cadena)+1>5:
                contador+=1
    return contador

def main():
    print("Este programa te devuelva la cant. de palabras de más de 5 letras en X cadena de palabras lol ")
    cadena=input("INgrese la cadena elegida: ")
    resultado=ej4(cadena)
    print(f"la caena fue {cadena} y ==> {resultado}")

if __name__=="__main__":
    main()