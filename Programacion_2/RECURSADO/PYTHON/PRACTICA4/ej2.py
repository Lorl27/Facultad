# Ejercicio 2. Escribir una función que tome un una cantidad m de valores que son ingresados por el usua-
# rio y, en la medida que lo ingresa, se muestra el factorial de ese número. El valor de m es ingresado
# inicialmente por el usuario.

def factorial(n:int):
    if n==0:
        return 1
    else:
        return n*factorial(n-1)
        
        
def fact_usu():
    limite:int=int(input("Elige la cant de numeros de los que queres saber su factorial: "))
    for _ in range (limite):
        num=int(input("pone tu numero"))
        print(f"el factorial de {num} es {factorial(num)}")
        
def main():
    fact_usu()
    
if __name__=="__main__":
    main()