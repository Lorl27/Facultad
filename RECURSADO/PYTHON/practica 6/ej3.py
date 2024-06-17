# Ejercicio 3. Escriba un programa que cuente cuántas veces aparecen cada una de las voca-
# les en una cadena. No importa si la vocal aparece en mayúscula o en minúscula.

def contar(caracter:str,cadena:str):
    return cadena.count(caracter)

def vocales(cadena:str)->str:
    string=cadena.lower()
    vocal_a=contar("a",string)
    vocal_e=contar("e",string)
    vocal_i=contar("i",string)
    vocal_o=contar("o",string)
    vocal_u=contar("u",string)
    total=vocal_u+vocal_e+vocal_i+vocal_a+vocal_o
    
    return f"""La cantidad de vocales es:{total}, con:
                a={vocal_a}
                e={vocal_e}
                i={vocal_i}
                o={vocal_o}
                u={vocal_u}"""

def main():
    print("Este programa te devuelva la cant. de vocales en X cadena lol ")
    cadena=input("INgrese la cadena elegida: ")
    resultado=vocales(cadena)
    print(f"la caena fue {cadena} y ==> {resultado}")

if __name__=="__main__":
    main()