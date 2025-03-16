# Ejercicio 6. Diseñar tres funciones que resuelvan los siguientes problemas:
# a) Dado un número entero n, indicar si es par o no.
# b) Dado un número entero n, indicar si es múltiplo de tres o no.
# c) Dado un número entero n, y un factor f indicar si es múltiplo de f o no.


def ejercicio6_A(n:int):
    cartel=f"{n} es un número: "
    if (n%2)==0:
        cartel+="par"
    else:
        cartel+=" impar"
    print(cartel)
    
def ejercicio6_B(n:int):
    cartel=f"{n} es un número: "
    if (n%3)==0:
        cartel+="múltiplo de 3"
    else:
        cartel+=" que NO es múltiplo de 3"
    print(cartel)
    
def ejercicio6_C(n:int,f:int):
    cartel=f"{n} es un número: "
    if (n%f)==0:
        cartel+=f"múltiplo de {f}"
    else:
        cartel+=f" que NO es múltiplo de {f}"
    print(cartel)
    
def main():
    variable=int(input("Ingresa tu número para EJERCICIO A,B,C: "))
    ejercicio6_A(variable),ejercicio6_B(variable),ejercicio6_C(variable,6)
    
if __name__ == "__main__":
    main()