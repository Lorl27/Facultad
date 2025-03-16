
def cuadrado(n):
    return n*n


# Problema: Pensar un número (n), duplicarlo, sumarle seis, y dividirlo por dos, y restarle el número
# elegido al comienzo. El número que queda es siempre tres.

# def aa(n):
# ope=n
# n*=2
# n+=6
# n//=2 #N=N/2 #n/2 n//2 n**2
# n-=ope
# return n

# print(aa(5))

# Problema Supongamos que queremos calcular la suma de los primeros cinco números cua-
# drados. Reutilizaremos la función cuadrado ya definida en los ejemplos anteriores.

# def ll():
# suma=0
# for pablo in range(0,5):
# print("num=",pablo)
# m=pablo*pablo
# print("m=",m)
# suma+=m
# print("suma=",suma)
# print("total=",suma)

# ll()



# def cuadrado(n):
# ope=n*n
# return ope

# Ejercicio 4. Implementar algoritmos que permitan:
# a) Calcular el perímetro de un rectángulo dada su base y su altura.
# b) Calcular el área de un rectángulo dada su base y su altura.
# c) Calcular el perímetro y el área de un rectángulo (alineado con los ejes x e y) dadas sus
# coordenadas x1, x2, y1, y2.
# d) Calcular el perímetro de un círculo dado su radio. Ayuda: Considerar a P I como 3,141592
# e) Calcular el área de un círculo dado su radio.
# f) Calcular el volumen de una esfera dado su radio.
# g) Dados los catetos de un triángulo rectángulo, calcular su hipotenusa.
# Ayuda: Definir la función raiz_cuadrada primero. No utilice el módulo math

# import math

# print(math.sqrt(2))


def perimetro(a,b):
    return 2*(a+b)

# print(perimetro(5,3))

def area(a,b):
    return(a*b)

def distancia(a,b):
    return abs(b-a)

def rectangulo(x1,x2,y1,y2):
    distancia_x=distancia(x1,x2)
    distancia_y=distancia(y1,y2)
    p=perimetro(distancia_x,distancia_y)
    a=area(distancia_x,distancia_y)
    print(f"El perimetro es {p} y el area es: {a}")

# area(5,7)

# rectangulo(2,3,5,4)

PI=3.141592

def circulo(radio):
    print( 2*PI*radio)

circulo(4)
circulo(10)

def r(radio):
    print(PI*radio**2)

r(4)

def esfera(radio):
    return (4/3)*PI*radio**3

print(esfera(6))

def raiz_cuadrada(n):
    return n**(1/2)

print(raiz_cuadrada(4))
print(raiz_cuadrada(25))

def hallar_hipotenusa(cateto1,cateto2):
    return raiz_cuadrada((cuadrado(cateto1)+cuadrado(cateto2)))

def main():
    cat1= float(input("Ingrese el nro del primer cateto: "))
    cat2= float(input("Ingrese el nro del segundo cateto: "))
    hipotenusa=hallar_hipotenusa(cat1,cat2)
    print(f"La hipotenusa de los catetos: {cat1} , {cat2} es: {hipotenusa}")

#ejercico 5:

# main()

# for i in range(5):
#      print(i * i)

# print("separador 2")
# for i in range(2, 6):
#      print(i, 2 ** i)

# print("separador 3")
# for i in range(6, 2): #doesnt work bc 6>2.
#     print(i* i)

# print("separador 4")
# for i in range(-5):
#      print(i* i + 1)
#                         #dont work bc son negativos
# print("separador 5")
# for i in range(-5, -1):
#      print(i* i, end="\t")

# print("separador 6")
# for i in range(-1, -5):
#      print(i, end=" ")

# print("separador 7")   
# for i in range(5,5):
#      print("valor: ",i , end="\n")

# print("separador 8")
# for i in [1,3,5,7,9]:
#      print("valor: ",i , end="\t")

# print("separador 9")
# for i in [-1,33,34,2,1]:
#      print("valor: ", i, " cuadrado: ", i*i)

# print("separador 10")
# for i in [-1,0,-1,0,-1,0]:
#      print("valor: ", i)
    

# print ("tres", "tristes", "tigres", sep="*")
