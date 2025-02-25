#parcial1 de python

#ej 1:
def mayor(l:list)->int:
    if not l:
        return "en la lista NO hay elementos"  # type: ignore
    else:
        max=l[0]
        for x in range(0,len(l)):
            if l[x]>max:
                max=l[x]
        return max
    
def mayor2(l:list)->int:
    if not l:
        return "en la lista NO hay elementos"  # type: ignore
    else:
        contador=0
        max=l[0]
        while(contador<len(l)):
            if l[contador]>max:
                max=l[contador]
            contador+=1
        return max
    
def segundo_mayor(l:list)->int:
    if not l:
        return "en la lista NO hay elementos"  # type: ignore
    else:
        max=mayor(l)
        l.remove(max)
        s_max=mayor(l)
        if max==s_max:
            return "son iguals" #type:ignore
        else:
            return s_max

def n_mayor(l:list,n:int):
    if not l:
        return "en la lista NO hay elementos"  # type: ignore
    if n==0:
        return "eror"
    
    
    if n>len(l):
        return "no se puede buscar..faltan elementos" # type: ignore
    
    maximos=[]
    l_2=l.copy()
    while(len(maximos)<n and l_2!=[]):
            max=mayor(l_2)
            maximos.append(max)
            l_2.remove(max)
        
    return maximos[-1] #los 1ros 2 casos estaban contemplados ya- indice star with 0
    
l=[2,3,5,7,90,44]
print(mayor(l))
print(mayor2(l))
print(segundo_mayor(l))
l=[2,3,5,7,90,44]
print(n_mayor(l,0))
print(n_mayor(l,1))
print(n_mayor(l,2))
print(n_mayor(l,3))
print(n_mayor(l,4))
print(n_mayor(l,5))
print(n_mayor(l,6))
print(n_mayor(l,7))

# def n_mayor2(lista, n):
#     if not lista:
#         return "La lista está vacía"
    
#     # Eliminar duplicados manteniendo el orden de la lista original
#     lista_unicos = []
#     for num in lista:
#         if num not in lista_unicos:
#             lista_unicos.append(num)
    
#     if len(lista_unicos) < n:
#         return f"No hay {n} números distintos en la lista"
    
#     # Encontrar el n-ésimo número más grande sin usar set o sort
#     for i in range(n):
#         max_actual = float('-inf')  # Inicializamos con el valor más pequeño posible
#         for num in lista_unicos:
#             if num > max_actual:
#                 max_actual = num
#         lista_unicos.remove(max_actual)  # Removemos el máximo actual de la lista
    
#     return max_actual

# print(n_mayor2(l,2))
# print(n_mayor2(l,3))
# print(n_mayor2(l,4))
# print(n_mayor2(l,5))
# print(n_mayor2(l,6))
# print(n_mayor2(l,7))

