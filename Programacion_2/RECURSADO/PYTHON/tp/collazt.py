# Ejercicio 1. Collatz
# Diseñe un programa que pida un número natural al usuario y calcule cuantas aplicaciones sucesivas de la
# función de Collatz son necesarias para alcanzar el valor 1, imprimiendo en cada caso los valores que se
# generan. Proponga una solución iterativa y una recursiva.
# Collatz(n)
# 
# n/2, si n es par
# 3 ∗ n + 1, si n es impar
# Algunas secuencia de valores para Collatz hasta que alcanza el valor 1 son:
# Collatz(4) = 2 → 1
# Collatz(26) = 13 → 40→ 20 → 10 → 5 → 16 →8 →4 → 2 → 1
# Collatz(17) = 52→ 26 → 13 → 40→ 20 → 10 → 5 → 16 →8 →4 → 2 → 1


def collatz(n:int)->str:
    """
    Calculate the Collatz sequence for a given integer.
    @param n - The starting integer for the Collatz sequence
    @return A string indicating the number of steps taken to reach 1 in the Collatz sequence.
    """
    sucesiones=0
    
    while n!=1:
        sucesiones+=1
        if (n%2)==0:
            n//=2
            print(n,end="→")
            
        else:
            n=n*3+1
            print(n)
            
    return f"La cantidad de sUcesiones para alcanzar el valor de 1 fue de: {sucesiones}"


def collatz2(n:int,sucesiones:int=0):
    
    print(n)
    if n==1:
        print(f"la cantidad de sucesiones fue: {sucesiones}")
        return n
    else:
        sucesiones+=1
        if (n%2)==0:
            n//=2
            
            
        else:
            n=n*3+1
        
        return(collatz2(n,sucesiones))

def main():
    print("La siguiente funcion le permitira ejecutar la funcion collatz dde manera iterativa:")
    n=int(input("Elige tu numero: "))
    rta=collatz2(n)
    print(rta)
    
if __name__=="__main__":
    main()