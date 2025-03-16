# 1. Listas y Secuencias

# Ejercicio 1. Escriba una función que, dados una lista desordenada y un elemento:
# a) devuelva la cantidad de apariciones del elemento recibido en la lista;
# b) busque la primera coincidencia del elemento en la lista y devuelva su posición;
# c) utilizando la función anterior, busque todos los elementos que coincidan con el que fue
# recibido como parámetro y devuelva una lista con las respectivas posiciones.

l=[1,5,8,9,5,9,9,9,9]

#a
def lista_ep(lista:list,elemento):
    contador=0
    for x in lista:
        if x==elemento:
            contador+=1
    return contador

print(lista_ep(l,5))
print(lista_ep(l,9))
print(lista_ep(l,8))

#b
def lista_e(lista:list,elemento):
    largo=len(lista)
    izq=0
    der=largo-1

    while izq<=der:
        medio=(izq+der)//2
        
        if lista[medio]==elemento:
            return lista.index(elemento)
        
        elif lista[medio]<elemento:
            izq=medio+1
            
        else:
            der=medio-1    
                
    return "Not found"

print(lista_e(l,5))
print(lista_e(l,9))
print(lista_e(l,2))

#c 
def lista_p(lista:list,elemento):
    l=[]
    
    for y,x in enumerate(lista): #indice-valor
        if x==elemento:
            l.append(y)
    return l

print(lista_p(l,5)) #1,4
print(lista_p(l,9)) #3,5,6,7,8
print(lista_p(l,2)) #0

# Ejercicio 2. Escriba una función que tome una lista de números desordenada y:
# a) devuelva el valor máximo;
# b) devuelva una tupla que incluya el valor máximo y su posición.
# ¿Qué sucede si los elementos son listas de caracteres?

def max(lista):
    contador=0
    largo=len(lista)
    
    if lista ==[]:
        return "empty"
    
    max=l[0]
    
    while contador<largo:
        if int(lista[contador])>int(max):
            max=lista[contador]
        contador+=1
    return max

print(max([1,2,3,7,8,1,19,67,68,69,1,0,0]))

def tup(lista):
    maximo=max(lista)
    maximo_i=lista.index(maximo)
    return(maximo,maximo_i)

print(tup([1,2,3,7,8,1,19,67,68,69,1,0,0]))
print(tup(["2","3","44"]))

# Ejercicio 3. Escriba una función que tome una lista ordenada y un elemento. Si el elemento
# se encuentra en la lista, debe encontrar su posición mediante búsqueda binaria y devolverlo. Si
# no se encuentra, debe agregarlo a la lista en la posición correcta y devolver esa nueva posición.

def bin(lista,elemento):
    l_o=sorted(lista)
    for indice,elem in enumerate(l_o):
        if elem==elemento:
            return indice
        else:
            lista.append(elemento)
            return lista.index(elemento)
        
print(bin([1,2,3],3))
print(bin([1,2,3],6))

def busqueda_b(lista,elemento):
    l_o=sorted(lista)
    largo=len(lista)
    izq=0
    der=largo-1
    
    while izq<=der:
        medio=(izq+der)//2
        if l_o[medio]==elemento:
            return lista.index(elemento)
        elif l_o[medio] < elemento:
            izq= medio+1
        else:
            der=medio-1
            
    if elemento not in lista:
        lista.append(elemento)
        return lista.index(elemento)

print(busqueda_b([1,2,3,4],2))
print(busqueda_b([1,2,3,4],22))
print(busqueda_b([1,2,2,3,4,6,3,4],2))
print(busqueda_b([1,2,0,2,3,3,4],2))

print(" ")

def busqueda_b_o(lista,elemento):
    l_o=sorted(lista)
    largo=len(lista)
    izq=0
    der=largo-1
    
    while izq<=der:
        medio=(izq+der)//2
        if l_o[medio]==elemento:
            return medio
        elif l_o[medio] < elemento:
            izq= medio+1
        else:
            der=medio-1
            
    if elemento not in lista:
        lista.append(elemento)
        return largo

print(busqueda_b_o([1,2,3,4],2))
print(busqueda_b_o([1,2,3,4],22))
print(busqueda_b_o([1,1,1,1,1,2,3,4],22))
print(busqueda_b_o([1,2,2,3,4,6,3,4],2))
print(busqueda_b_o([1,2,0,2,3,3,4],2))
print(busqueda_b_o([1,2,3,4,5,6,7,8,9],22))