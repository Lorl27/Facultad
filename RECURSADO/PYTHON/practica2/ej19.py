# Ejercicio 19. Diseñe un programa que imprima los primeros 100 números naturales pares.
# 1. ¿Pudo usar la solución propuesta en el ejercicio anterior?
# 2. ¿Puede pensar una solución que sirva para mostrar los primeros n números naturales
# pares?

for x in range(0,100+1,2):
    print(x)
    

def num_par(n:int):
    for x in range(0,n+1):
        if x%2==0:
            print(x)
            
def main():
    nat=int(input("Ingresa el numero para el cual, veremos sus primeros valores pares"))
    num_par(nat)
    
if __name__=="__main__":
    main()