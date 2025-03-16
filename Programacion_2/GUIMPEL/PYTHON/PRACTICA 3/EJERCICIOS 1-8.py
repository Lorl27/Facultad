# 1. Listas:

# Ejercicio 1. Escriba una función posicionesMultiplo que tome una lista y un número y re-
# torne la lista formada por los elementos que están en las posiciones múltiplos de ese número.
# Por ejemplo: posicionesMultiplo([1,2,3,4,5,6,7],2) retorna [1,3,5,7] y
# posicionesMultiplo([1,2,3,4,5,6,7],3) da como resultado [1,4,7].

def posicionesMultiplo(lista,number):
    l=[]
    for x in range(len(lista)):
        if (x+1) % number ==  0: #aumentamos uno porque el indice empieza en 0
            l.append(lista[x])
    return l

            
print(posicionesMultiplo([1,2,3,4,5,6,7],2))

# Ejercicio 2. Escriba una función que tome una lista de números y devuelva la suma acumu-
# lada, es decir, una nueva lista donde el primer elemento es el mismo, el segundo elemento es
# la suma del primero con el segundo, el tercer elemento es la suma del resultado anterior con el
# siguiente elemento y así sucesivamente. Por ejemplo, la suma acumulada de [1,2,3] es [1,
# 3, 6].

def sumAcum(lista):
    contador=0
    l=[]
    for x in lista:
        contador+=x
        l.append(contador)
    return l

print(sumAcum([1,2,3])) #1,3,6
print(sumAcum([2,4,7])) #2,6,13

# Ejercicio 3. Escriba una función llamada elimina que tome una lista y elimine el primer y
# último elemento de la lista. La función debe devolver una nueva lista con los elementos que no
# fueron eliminados.

def elimina(l):
                l.pop(0)
                l.pop((len(l)-1))
                return l

print(elimina([1,2,3,4,5]))

# Ejercicio 4. Escriba una función ordenada que tome una lista como parámetro y devuelva
# T rue si la lista está ordenada en orden ascendente y F alse en caso contrario. Por ejemplo,
# ordenada([1, 2, 3]) retorna T rue y ordenada([’b’, ’a’]) retorna F alse.

def ordenada(lista):
    largo=len(lista)
    for x in range(largo-1):
        if lista[x] > lista[x+1]:
            return False
    return True

print(ordenada(["a","b"])) #t
print(ordenada(["b","a"])) #f

# Ejercicio 5. Escriba una función llamada duplicado que tome una lista y devuelva T rue si
# tiene algún elemento duplicado. La función no debe modificar la lista.

def duplicado(lista):
    largo=len(lista)
    for x in range(largo):
        for z in range(x+1,largo):
                                    if lista[x] == lista[z]:
                                                            print(f"{x} == {z} (indices), {lista[x]}=={lista[z]}")
                                                            return True
    return False

print(duplicado([1,2,3])) #F
print(duplicado([1,2,3,2])) #t

# Ejercicio 6. Escriba una función llamada eliminaDuplicados que tome una lista y devuelva
# una nueva lista con los elementos únicos de la lista original. No tienen porque estar en el mismo
# orden. Ayuda: puede utilizar la función sort.

def eliminaDuplicados(lista):
    newL=[]
    
    for x in lista:
        if x not in newL:
            newL.append(x)
        #first uno, nada a la iqz append. otro ignorar.

    return newL                

print(eliminaDuplicados([1,2,3,4]))
print(eliminaDuplicados([1,2,3,4,7,7,8]))
print(eliminaDuplicados([1,1,2,0,3,4,4,4,4,4]))

#FORMA 2:
def eliminaDuplicados2(lista):
    lista.sort()  # Ordenar la lista para agrupar elementos duplicados.
    newL = []
    largo=len(lista)

    contador = 0
    while contador < largo:
        elemento_actual = lista[contador]
        newL.append(elemento_actual)

        # Avanzar al siguiente elemento diferente.
        while contador < largo and lista[contador] == elemento_actual:
            contador += 1

    return newL

#FORMA 3:
def eliminaDuplicados3(lista):
    newL=[]
    for x in lista:
        if x.count() == 1:
            newL.append(x)
    return newL


# Ejercicio 7. Escriba una función que tome una lista y retorne la cantidad de elementos dis-
# tintos que tiene. Se recomienda usar la función del ejercicio anterior.

def cantDif(lista):
    element_Dif=len(eliminaDuplicados(lista))
    return element_Dif

print(cantDif([1,2,3,4,4]))
print(cantDif([1,3,4,4]))
print(cantDif([1,2,3,4,4,3,3,3,1]))

# Ejercicio 8. Para comprobar si una palabra está en una lista se puede utilizar el operador in,
# pero sería una búsqueda lenta ya que busca a través de las palabras según el orden en el cual
# aparecen en la lista. 
# Si la lista almacena las palabras en orden alfabético, podemos acelerar
# las cosas con una búsqueda dicotómica (también conocida como búsqueda binaria). 
# Esta es similar a lo que hacemos cuando buscamos una palabra en el diccionario. 
# Comenzamos por el centro y comprobamos si la palabra que buscamos está antes o después del centro. 
# Si está antes, buscamos sólo en la primera mitad, si está después, buscamos en la segunda mitad de
# la lista. 
# Con esto podemos reducir el tiempo de búsqueda.
# Implemente la función busquedaDicotomica que toma una lista de palabras ordenadas alfabéticamente 
# y una palabra a buscar y retorna si la palabra está en la lista o no.

def busquedaDicotomica(lista:list,palabra:str)->bool:
    if ordenada(lista):
        largo=len(lista)
        inicio=0
        fin=largo-1
        pasos=1
        while inicio<=fin:
            medio= (inicio+fin)//2
            pasos+=1
            if lista[medio]==palabra:
                return True
            elif lista[medio] < palabra:
                inicio=medio+1
            else:
                fin=medio-1
        print(pasos,"pasos. ",end="")
        return False
    else:
        lista_ord=sorted(lista)
        return busquedaDicotomica(lista_ord,palabra)
    
print(busquedaDicotomica(["hola","como","estas","bien"],"bien"))
print(busquedaDicotomica(["hola","como","estas","bien","bobo","estas","ok","mal","ej","bien"],"estas"))
print(busquedaDicotomica(["hola","chau","miami","jaba","como","estas","bien"],"hola"))
print(busquedaDicotomica(["hola","como","estas","bien"],"mama"))