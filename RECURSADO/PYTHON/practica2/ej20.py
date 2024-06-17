# Ejercicio 20. Diseñe un programa que imprima los primeros n números pares mayores que m.
# ¿Puede adaptar la solución propuesta en el ejercicio anterior para que resuelva este problema?


def n_mayor_m(n: int, m: int):
    if n<m:
        print(f"error. {n} es menor a {m}")
    elif n==m:
        print(f"error. {n}=={m}")
        
    for x in range(m+1, m+n):
        if x%2==0:
            print(x, end=' ')
        if x==n-1:
            break

def main():
    n = int(input("Ingrese el primer numero: "))
    m = int(input("Ingrese el 2do numero: "))
    n_mayor_m(n, m)


if __name__ == "__main__":
    main()
