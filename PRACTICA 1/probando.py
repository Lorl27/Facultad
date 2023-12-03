def factorial(x:int)-> int: # type: ignore
    if x>=0:
        if x==0:
            return 1
        else:
            return x*factorial(x-1)
    else:
        print("ERROR.")
        
        
factorial(5)
factorial(1)
factorial(-4)

def conteo(suma=0, contador=0):
    x=int(input("a: "))
    if x==0:
        print(suma,contador)
    else:
        conteo(suma+x,contador+1)
        
conteo()

def lista(l):
    if l!=[]:
        print(l[0])
        lista(l[1:])

lista([1,2,3,4,"so","r",True])

def facto(n):
    f=1
    for x in range(1,n+1):
        f*=x
    print(f)
    
facto(9)

lista=[1,2,3,"chau"] # type: ignore
tupla=("hola",lista)
print(tupla,lista)
lista[2]=999 # type: ignore
print(tupla,lista)
lista.append(4)
print(tupla,lista)
