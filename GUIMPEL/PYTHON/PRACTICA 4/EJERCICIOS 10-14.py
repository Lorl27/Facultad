# 3. Conjuntos

# Ejercicio 10. Escriba una función que tome una lista y utilice un conjunto para eliminar sus
# elementos duplicados.

def sinD(lista):
    s=set(lista)
    return s

print(sinD([1,2,1,2,1,3,4,5,5,5,5]))

# Ejercicio 11. Escriba una función que tome dos cadenas de texto y devuelva un conjunto con
# las palabras que aparecen en ambas cadenas (sin tener en cuenta mayúsculas y minúsculas).

def inter(str1,str2):
    string1=str1.capitalize()
    string2=str2.capitalize()
    string1=string1.split()
    string2=string2.split()
    s=set()
    for x in string1:
        if x in string2:
            s.add(x)
            
    return s
print(inter("hola como te va","hola a mi me va mal"))

# Ejercicio 12. Escriba una función que, dados dos conjuntos, devuelva un nuevo conjunto que
# contenga los elementos que están en uno de los conjuntos pero no en ambos.

#DIFERENCIA SIMETRICA
#por def: AUB-ANB v A-B U B-A
def dif_sim(conjunto1:set,conjunto2:set)->set:
    parte1=conjunto1-conjunto2
    parte2=conjunto2-conjunto1
    return parte1.union(parte2)

c1={1,2,3,4,5}
c2={1,2,6,7,89,3}
print(dif_sim(c1,c2))

# Ejercicio 13. Escriba una función que tome una lista desordenada de números naturales
# como entrada, calcule cuál es el número N máximo de la lista y devuelva un conjunto con los
# números naturales menores a N que no están en la lista.

def maximun(lista):
    largo=len(lista)
    contador=0
    max=0
    while contador<largo:
        for x in lista:
            if x>max:
                max=x
                
        contador+=1
    return max

def menores(lista:list)->set:
    conjunto=set()
    
    max=maximun(lista)
    ran=range(1,max+1)
    for x in ran:
        if x not in lista:
            conjunto.add(x)
    
    return conjunto

listitilla=[1,2,3,4,5,77,99,13]
print(menores(listitilla))

# Ejercicio 14. Organizar una reunión
# Escriba una función que tome como entrada un diccionario cuyas claves sean los nombres
# de las personas asistentes a la reunión y cuyos valores sean las listas de los días disponibles
# que tiene cada persona. La función debe devolver un conjunto con los días en los que todas
# las personas pueden asistir

#nombres:[dias]
def reunion(dicc:dict)->set:
    dias_H=[set(days) for days in dicc.values()] #Transforma cada lis_days en conjunto
    
    dias_c=set.intersection(*dias_H) #* ==todos
    
    return dias_c

reu={
    "tomas":["lunes","martes","sabado"],
    "anto":["jueves","sabado"],
    "elrichMC":["lunes","domingo","sabado"],
    "burn":["miercoles","jueves","sabado"]
}

print(reunion(reu))