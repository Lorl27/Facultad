#ciclos anidados

#Ejercicio 1. Construir las tablas de multiplicar de los números de 1 al 10.

for x in range(1,11):
    for y in range(1,11):
        print(f"{x}*{y}=={x*y}")
    print()