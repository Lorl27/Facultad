# Ejercicio 2. Utilizando la explicación anterior diseñar los siguientes programas y funciones
# que imprimen patrones en pantalla:
# 1. Construir un programa que imprima un rectángulo con 5 filas y 3 columnas.
# 2. Construir un programa que imprima un cuadrado con 5 filas y columnas
# 3. Construir un programa que imprima un triangulo con un ángulo recto invertido de 5 filas

#1:
print("////")

for x in range(1,6):
    for y in range(1,4):
        print("*",end=" ")
    print("")

print("////")

#2:
print("////")

for x in range(1,6):
    for y in range(1,6):
        print("*",end=" ")
    print("")

print("////")

#3:
print("////")

for x in range(1,6):
    for y in range(1,6-x+1):
        print("*",end=" ")
    print("")

print("////")