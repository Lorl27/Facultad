# 2. Diccionarios

# Ejercicio 4. Escriba una función que reciba una lista de tuplas y devuelva un diccionario en
# donde las claves sean los primeros elementos de las tuplas y los valores una lista con los
# segundos. Por ejemplo:

# >>> l = [ ( ’ Hola ’ , ’ don␣ P e p i t o ’ ) , ( ’ Hola ’ , ’ don␣ Jose ’ ) ,
# ( ’ Buenos ’ , ’ d i a s ’ ) ]

# >>> p r i n t ( t u p l a s _ a _ d i c c i o n a r i o ( l ) )
# { ’ Hola ’ : [ ’ don␣ P e p i t o ’ , ’ don␣ Jose ’ ] , ’ Buenos ’ : [ ’ d i a s ’ ] }

l = [ ( "Hola" , "don Pepito" ) , ( "Hola" , "don Jose"  ) , ("Buenos", "dias") ]

def tuplas_diccionario(lista):
    dic={}
    for x in lista:
        clave=x[0] #x as tupla
        valor=x[1]
        if clave in dic:
            dic[clave]+=[valor] #si ya existe, le sumo el nuevo valor ya q los dic no aceptan 2 claves ==
        else:
            dic[clave]=[valor]
    return dic

print(tuplas_diccionario(l)) #{"hola":["don pepito", "don jose"], buenos:["dias"]}

# Ejercicio 5. Diccionarios usados para contar:

# a) Escriba una función que reciba una cadena y devuelva un diccionario con la cantidad de
# apariciones de cada palabra en la cadena. Por ejemplo, si recibe "Que lindo dia que hace
# hoy" debe devolver:

# { " que " : 2 , " l i n d o " : 1 , " d i a " : 1 , " hace " : 1 , " hoy " : 1 }

def cadenas(string:str)-> dict:
    dic={}
    stringM=string.upper()
    m=stringM.split()
    for x in m:
        if x!=" ":
            cant=stringM.count(x)
            dic[x]=cant
    return dic

print(cadenas("Que lindo dia que hace hoy"))

# b) Escriba una función que reciba una cadena de texto y devuelva la cantidad de apariciones
# de cada caracter en un diccionario.

def caracteres(string:str)-> dict:
    dic={}
    stringM=string.upper()
    for x in stringM:
        if x!=" ":
            cant=stringM.count(x)
            dic[x]=cant
    return dic

print(caracteres("Que lindo dia que hace hoy"))

# c) Escriba una función que reciba una cantidad de iteraciones de una tirada de 2 dados a
# realizar y devuelva un diccionario en el cual las claves sean los resultados de la suma de
# los dados y los valores sean la cantidad de veces que se observa cada resultado.

import random

def ran(num):
    conteo=0
    dic={}
    m=[]
    rep=0
    
    while conteo!=num:
        dado1=random.randint(1,6)
        dado2=random.randint(1,6)
        
        suma=dado1+dado2
        m.append(suma)
        
        for x in m:
            if x==suma:
                rep+=1
                    
        dic[suma]=rep    
        conteo+=1 #valor "LIMITE"
        rep=0 #se reinicia
        
    return dic

print(ran(6))

# Ejercicio 6. Escriba una función que reciba un texto y devuelva un diccionario que, para
# cada caracter presente en el texto, almacene la cadena más larga en la que se encuentra ese
# caracter.

def longest_c(texto:str)->dict:
    dic={}
    textoM=texto.lower()
    cadenas=textoM.split()
    
    for cadenita in cadenas:
        for caracter in cadenita:
                if caracter not in ['.',' ']:
                    if caracter not in dic or len(cadenita)>len(dic[caracter]):
                        dic[caracter]=cadenita
            
    return dic

cadena="Hola olargo . amelia hi rekateee anaranjado p murcielago"
print(longest_c(cadena))

# Ejercicio 7. Escriba una función que reciba como entrada un diccionario cuyas claves sean
# los nombres de los estudiantes y cuyos valores sean las listas de sus calificaciones y:

# a) dado el nombre de un estudiante, devuelva el promedio de sus calificaciones.
# b) devuelva el nombre del estudiante con el mayor promedio.

#dic{nombre:[n1,n2,n3]}

def suma(notas):
    anterior=0
    for x in notas:
            anterior+=x
    return anterior

print(suma([1.2 , 1.5]))

def estudiantes(diccionario:dict)->dict:
    di={}
    nombre_m=""
    mejor_p=0

    for estudiante,notas in diccionario.items():
        suma_notas=suma(notas)
        longitud=len(notas)
        promedio=suma_notas/longitud
        di[estudiante]=promedio
        
        if promedio>mejor_p:
            mejor_p=promedio
            nombre_m=estudiante
            
    di["mejor"]=nombre_m

        
    return di

alumnos = {
    "Juan": [8.5, 7.0],
    "María": [9.0, 8.5],
    "Carlos": [7.5, 6.5],
    "Ana": [8.0, 7.5],
    "Pedro": [6.0, 7.0]
}

print(estudiantes(alumnos))

# Ejercicio 8. Escriba una función que tome una cadena de texto y un diccionario cuyas claves
# sean palabras y cuyos valores sean listas de sinónimos de dichas palabras. La función debe
# reemplazar cada palabra de la cadena recibida por un sinónimo elegido de forma aleatoria. Si
# una palabra no tiene sinónimos, debe dejar la original.

#palabras:sinonimos
def sinonimos(string:str,dicco:dict)->str:
    
    palabras=string.split()
    largo=len(palabras)

    for x in range(largo):
        palabra=palabras[x]
        
        if palabra in dicco:
            sinonimo = dicco[palabra]
            
            if isinstance(sinonimo, list): 
                sinonimo_r = random.choice(sinonimo) #elige random
            else:
                sinonimo_r=sinonimo
                
            palabras[x]=sinonimo_r
        
    return " ".join(palabras)

cade="hola me re voy a la luna esta noche"
di={"hola":["buenas","hi"],"voy":["fui"]}

print(sinonimos(cade,di))

# Ejercicio 9. Escriba una función que tome como entrada dos diccionarios. Ambos tienen
# como clave nombres de productos. Los valores del primero son los precios de cada producto,
# mientras que los valores del segundo son las cantidades de cada producto que hay en el carrito.
# La función debe devolver el monto total de la compra realizada

#productos:$$
#productos:cantidad
def monto(dicc1:dict,dicc2:dict)->int:
    m=0
    for producto,precio in dicc1.items():
        for producto2,can in dicc2.items():
            if producto==producto2:
                formu=precio*can
                m+=formu
    return m

p1={
    "banana":500,
    "uvas":900,
    "manzanas":23,
    "peras":78,
    "jugo":300
}

p2={
    "banana":1,
    "uvas":3,
    "manzanas":2,
    "peras":0,
    "jugo":0
}

print(monto(p1,p2))