# Ejercicio 10. Escriba una función que reciba un número natural e imprima todos los números primos que
# hay hasta ese número. Para esto se pide que:
# a) Defina una función es_primo que toma un número natural y verifique si es un número primo.
# b) Resuelva el problema usando la función definida en el punto anterior.

def es_primo(n)->bool:
    if n<2:
        return False
    for x in range(2,n):
        if(n%x)==0:
            return False
    return True

def primos(n):
    for x in range(n+1):
        if es_primo(x):
            print(x)
            
            
def main():
    print("El siguiente programa le permitira calcular la cantidad de numeros primos hasta un número dado")
    n=int(input("eliga ese numero: "))
    primos(n)
    
    
if __name__=="__main__":
    main()