# Ejercicio 1. Escribir funciones que dada una cadena de caracteres:
# a) Imprima los dos primeros caracteres.
# b) Imprima los tres últimos caracteres.
# c) Imprima dicha cadena cada dos caracteres. Ej.:“recta"debería imprimir “rca".
# d) Dicha cadena en sentido inverso. Ej.: “hola mundo!"debe imprimir “!odnum aloh".
# e) Imprima la cadena en un sentido y en sentido inverso. Ej: “reflejoïmprime “reflejoojelfer".

#a:

def eja(cadena:str):
    return cadena[:2]

def test_eja():
    assert eja("hola")=="ho"
    assert eja("MANOPla")=="MA"
    assert eja("SUICIDIO")=="SU"

def ejb(cadena:str):
    largo=len(cadena)
    return cadena[largo-3::]

def test_ejb():
    assert ejb("hola")=="ola"
    assert ejb("MANOPla")=="Pla"
    assert ejb("SUICIDIO")=="DIO"

def ejc(cadena:str):
    return cadena[::2]

def test_ejc():
    assert ejc("hola")=="hl"
    assert ejc("MANOPla")=="MNPa"
    assert ejc("SUICIDIO")=="SIII"

def ejd(cadena:str):
    return(cadena[::-1])

def test_ejd():
    assert ejd("hola")=="aloh"
    assert ejd("MANOPla")=="alPONAM"
    assert ejd("SUICIDIO")=="OIDICIUS"

def eje(cadena:str):
    return(cadena + ejd(cadena))

def test_eje():
    assert eje("hola")=="holaaloh"
    assert eje("MANOPla")=="MANOPlaalPONAM"
    assert eje("SUICIDIO")=="SUICIDIOOIDICIUS"

def main():
    print("Este programa imprimirá los priemros 2 carácteres de cualquier cadena dada: ")
    cadena=input("INgrese la cadena elegida: ")
    resultado=eja(cadena)
    print(f"La cadena fue: {cadena} => {resultado}")
    print("Este programa imprimirá los 3 últimos carácteres de cualquier cadena dada: ")
    resultado=ejb(cadena)
    print(f"La cadena fue: {cadena} => {resultado}")
    print("Este programa imprimirá la cadena cada dos caracteres de cualquier cadena dada: ")
    resultado=ejc(cadena)
    print(f"La cadena fue: {cadena} => {resultado}")
    print("Este programa imprimirá la cadena ecadena en sentido inverso de cualquier cadena dada: ")
    resultado=ejd(cadena)
    print(f"La cadena fue: {cadena} => {resultado}")
    print("Este programa imprimirá la cadena en un sentido y en sentido inverso de cualquier cadena dada: ")
    resultado=eje(cadena)
    print(f"La cadena fue: {cadena} => {resultado}")
    

if __name__=="__main__":
    main()

