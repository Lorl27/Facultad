# Ejercicio 5. Escribir una función que dada una cadena de caracteres, devuelva:

# a) La primera letra de cada palabra. Por ejemplo, si recibe, “Universal Serial Bus"deberá
# devolver, “USB".
# b) Dicha cadena con la primera letra de cada palabra en mayúsculas. Por ejemplo, si recibe,
# “república argentina", deberá devolver, “República Argentina".
# c) Las palabras que comiencen con la letra “A"; por ejemplo, si recibe “Antes de ayer almorcé y cené"deberá devolver “Antes ayer almorcé".
# d) Generalice el problema anterior para cualquier vocal o consonante.

#eja:

def eja(cadena:str)->str:
    cadena=cadena.upper()
    result=""
    for i in range(len(cadena)): 
        if i==0 or cadena[i-1]==" ":
            result+=cadena[i]
        
    return result


#B:

def ejb(cadena:str)->str:
    result=""
    for x in range(len(cadena)):
        if x==0 or cadena[x-1]==" ":
            result+=cadena[x].upper()
        else:
            result+=cadena[x]
    return result


#C:

def es_letra_A(letra:str):
    return letra=="A" or letra=="Á" or letra=="a" or letra=="á"

def encontrar_palabras_con_A(cadena: str) -> str:
    result = ""
    palabras = cadena.split()  # Dividir la cadena en palabras
    for palabra in palabras:
        if es_letra_A(palabra[0]):  # Verificar si la primera letra de la palabra es "A" o "a"
            result += palabra + " "  # Agregar la palabra al resultado
    return result.rstrip()  # Eliminar el espacio extra al finalt


def ejc_gaspi(cadena):
    espacio = " "
    palabra = ""
    cortar = 0
    palabras_con_a = ""
    cadena += " "
    for i in range(len(cadena)):
        if espacio == cadena[i]:
            palabra = cadena[cortar:i]
            if palabra[0] == "a" or palabra[0] == "A":
                palabras_con_a += palabra
                palabras_con_a += " "
            cortar = i+1
            palabra = ""
    return palabras_con_a
    
    


def ejd(cadena:str,variante:str)->str:
    espacio=" "
    palabra=""
    palabras_con_variante=""
    cadena+=" "
    cut=0

    for x in range(len(cadena)):
        if espacio==cadena[x]:
            palabra=cadena[cut:x]
            if palabra[0]==variante.upper() or palabra[0]==variante.lower():
                palabras_con_variante+=palabra + " "
            cut=x+1
            palabra=""
    return palabras_con_variante


def main():
    print("Este programa te devuelva la premera letra d cada palabra: ")
    cadena=input("INgrese la cadena elegida: ")
    resultado=eja(cadena)
    print(f"la caena fue {cadena} y ==> {resultado}")
        
    print("Este programa te devuelva la premera letra d cada palabra en MAYUS: ")
    cadena=input("INgrese la cadena elegida: ")
    resultado2=ejb(cadena)
    print(f"la caena fue {cadena} y ==> {resultado2}")
        
    print("Este programa te devuelva solo las palabras q tienen la letrs A al comienzo: ")
    cadena=input("INgrese la cadena elegida: ")
    resultado3=encontrar_palabras_con_A(cadena)
    print(f"la caena fue {cadena} y ==> {resultado3}")
    
    

    print("Este programa te devuelva solo las palabras q tienen la letrs ELEGIDA al comienzo: ")
    letra=input("INgrese la LETRA elegida: ")
    cadena=input("INgrese la cadena elegida: ")
    resultado4=ejd(cadena,letra)
    print(f"la caena fue {cadena} y ==> {resultado4}")

if __name__=="__main__":
    main()
