# Ejercicio 9. Escribir una función que reciba dos números como parámetros, y devuelva cuántos múltiplos
# del primero hay, que sean menores que el segundo.
# a) Implementarla utilizando un ciclo for, desde el primer número hasta el segundo.
# b) Implementarla utilizando un ciclo while, que multiplique el primer número hasta que sea mayor que el
# segundo.
# c) Comparar ambas implementaciones: ¿Cuáles más clara? ¿Cuál realiza menos operaciones?

#a:
def ciclo_for(a:int,b:int):
    contador=0
    if a>b:
        return "No es posible su calculo."
    for x in range(a,b+1):
        if x<b and (x%a)==0:
            contador+=1
            print(x)
    return f"La cantidad de númreros múltiplos de {a} menores a {b} son: {contador}\n\n"

#b
def ciclo_while(a:int,b:int)-> str:
    contador=0
    n=a
    while n<b:
        if (n%a)==0:
            contador+=1
            print(n)
        n+=1
    return f"La cantidad de númreros múltiplos de {a} menores a {b} ES: {contador}"

def main():
    print("las siguiente funciones calcularan los multiplos del primer numero MENORES al segundo, de 2 formas distintas:")
    a=int(input("Ingrese el primer numero:"))
    b=int(input("Ingrese el segundo numero: "))
    resultado_for=ciclo_for(a,b)
    resultado_while=ciclo_while(a,b)
    print(f"los numeros ingresados fueron: {a} y {b}. ," f"en el ciclo for_: {resultado_for} " , f"en el ciclo while_:{resultado_while} ", end="\t\t")
    
if __name__=="__main__":
    main()