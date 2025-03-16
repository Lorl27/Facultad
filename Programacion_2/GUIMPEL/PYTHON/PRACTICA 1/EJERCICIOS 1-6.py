#Primeros programas usando números:

# Ejercicio 1. Escriba un programa que imprima los primeros 25 números naturales pares.

for x in range(0,25,2):
    print(x)

#Ejercicio 2. Escriba un programa que imprima los primeros 100 números naturales pares.
    #1. ¿Pudo usar la solución proopuesta en el ejercicio anterior?
    #2. ¿Puede pensar una solución que sirva para mostrar los primeros n números naturales pares?

fun= [x*2 for x in range(0,51)]
print(fun)

n_pares=[0,1,2,3,4,5,6,7,8,9]
for x in n_pares:
    if x%2==0:
        print(x)

#Ejercicio 3. Escriba un programa que imprima los primeros n números pares mayores que m.
    #¿Puede adaptar la solución propuesta en el ejercicio anterior para que resuelva este problema?

#n_pares=[0,1,2,3,4,5,6,7,8,9]

def numPM(n, m):
    contador = 0
    num=m+1
    while contador <n:
        if num % 2 == 0:
            print(f"los primeros {n} nums mayores que {m} son: {num}")
            contador += 1
        num += 1

numPM(4, 10)


#Ejercicio 4. Escriba un programa que calcule e imprima el resultado de la suma de
# los primeros 50 números naturales usando una función recursiva.

def suma(n,m):
    return n+m

for x in range(0,50):
    print("x sera", x, "y la suma es",suma(x,x+1))


#Ejercicio 5. Escriba un programa que calcule e imprima el resultado de la suma de
# los primeros n números naturales usando una función recursiva.

def ejercicio5(n):
    for x in range(n,n+50):
        print("x sera", x, "y la suma es",suma(x,x+1))

print(ejercicio5(1))

#Ejercicio 6. Escriba un programa que calcule e imprima el resultado de la suma de
# los números naturales mayores que n y menores que m usando una función recursiva.

def ejercicio6(n,m):
    x=1
    while x>=n and x<m :
        print("x sera", x, "y la suma es",suma(x,x+1))
        x+=1

print(ejercicio6(1,4))