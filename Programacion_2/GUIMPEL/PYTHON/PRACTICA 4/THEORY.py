a={} #diccionario vacio, class:dict
b={"nombre":"bruno","amelia":66} #clave:valor
print(b["amelia"])
#diccionario indexeado x clave no por index. calve=amelia/nombre
#E una unica CLAVE. si E2== ; se guarda el ultimo
#ERROR si intento acceder a una clave que NO existe

#PARA AGREGAR VALORES:
m={1:["HOLA"],"A":(1,2,3)}

m[2]="NUEVO"
print(m) #m[clave]=valor

#PARA MODIFICARLOS:
m[1]+=["chu"] #m={1:["hola","chu"],"A":(1,2,3),2:"NUEVO"}
print(m)

#recorrer diccionario
for x in m:
    print(x) #==claves
    print(m[x])#==valores
    
m.items() #=> retorna toda la secuencia de pares calve-valor
#entonces:
for x,y in m.items():
    print(x,y) #valor:clave
    
#METODOS:
l=[(1,"valor"),("clave","valor")]
dict(l) #=> Lo convierte a diccionario: {1:"valor","clave":"valor"}

m.keys() #=> devuelve las CLAVES del diccionario
m.values() #LOS VALORES

#----------------------CONJUNTOS:
s=set() #conjunto , type:set

c={1,"ho",(1,2)}  #NO inporta su orden y si hay repeticion le chupa un huevo

#AÑADIR ELEMNTO:
c.add("abc") 
c.add(0)

c.update([4,2,3]) #c={1,"ho",2,3,"abc",0,4} #permite agregar los elmentos d la L o Conjunto

#BORRAR:
c.discard(5) #si no existe,no pasa nada.
c.remove(4) #si no existe, da error!

#UNIR:
r=c|s #no retorna nada
s.union(c) #retorna la union

#INTERSECTAR:
d=c&s #no retorna
s.intersection(c) #ternova la inter

#DIFERENCIA:
f=s-c
s.difference(c)