# 2. Cadenas:
    
# Ejercicio 9. Escriba un programa que tenga una función que tome una cadena y muestre
# cada caracter que la forma del último al inicial.

def cant(str:str):
    for x in str:
        if x!=" ":
            print(x)

cant("Hola Que Pasa RENÉ")
# Ejercicio 10. Escriba un programa que contenga a la función contar(l, x) que cuente cuán-
# tas veces aparece un carácter l dado en una cadena x.

def contar(w:str,string:str)->int:
    num=0
    largo=len(string)
    for x in string:
        if x==w:
            num+=1
    return num

print(contar("a","naranja"))

# Ejercicio 11. Escriba un programa que cuente cúantas veces aparecen cada una de las vo-
# cales en una cadena. No importa si la vocal aparece en mayúscula o en minúscula.

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

print(vocales("Murcielago"))
print(vocales("Rojo"))
print(vocales("DinosauRIO"))

# Ejercicio 12. Escriba un programa que contenga una función que reciba como parámetro una
# cadena de palabras separadas por espacios y devuelva como resultado cuántas palabras de
# más de cinco letras tiene la cadena dada.

#FORMA SIN SPLIT:
def cincoL(string:str)->int:
    conteo=0
    palabras=""
    lista=[]
    for x in string:
        if x==" ":
            if len(palabras)>5:
                conteo+=1
                lista.append(palabras)
            palabras=""
        else:
            palabras+=x #ya que no era vacia!
    if len(palabras)>5:
        lista.append(palabras)
        conteo+=1
    for x in lista:  
            print(x,end="")
    return conteo

print(cincoL("Hola como te va a vos cinco cinco1 cinco12"))

#CON SPLIT:
def ej9(string):
    conteo=0
    abc=string.split()
    for palabra in abc:
        if len(palabra)>5:
            conteo+=1
    return conteo

print(ej9("cinco1 cinco22 cinco333 8"))
