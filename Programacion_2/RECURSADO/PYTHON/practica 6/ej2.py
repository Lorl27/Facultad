# Ejercicio 2. Escriba un programa que contenga a la función contar(l, x) que cuente
# cuántas veces aparece un carácter l dado en una cadena x.

def contar(caracter:str,cadena:str):
    return cadena.count(caracter)

def contar2(caracter:str,cadena:str):
    contador=0
    for x in cadena:
        if x==caracter:
            contador+=1
    return contador

def main():
    print("Este programa te devuelva la cant. de veces q aparece X letra en X cadena lol ")
    letra=input("INgrese la letra elegida: ")
    cadena=input("INgrese la cadena elegida: ")
    resultado=contar(letra,cadena)
    print(f"la caena fue {cadena} y al eltra= {letra} ==> {resultado}")
    resultado2=contar2(letra,cadena)
    print(f"la caena fue {cadena} y al eltra= {letra} ==> {resultado2}")

if __name__=="__main__":
    main()