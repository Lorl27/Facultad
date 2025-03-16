# Ejercicio 3. Dadas las siguientes ecuaciones recursivas diseñar funciones en Python que permitan eva-
# luarlas.
# a)
# lucca(0) = 2
# lucca(1) = 1
# lucca(n) = lucca(n − 1) + lucca(n − 2) para n > 2
# b)
# pell(0) = 0
# pell(1) = 1
# pell(n) = 2 × pell(n − 1) + pell(n − 2) para n > 2
# c)
# jacob(0) = 0
# jacob(1) = 1
# jacob(n) = jacob(n − 1) + 2 × jacob(n − 2) para n > 2

def lucca(n):
    if n == 0:
        return 2
    elif n == 1:
        return 1
    else:
        return lucca(n-1) + lucca(n -2)


def pell(n):
    if n == 0:
        return 0
    elif n==1:
        return 1
    else:
        return 2*pell(n - 1)+pell(n-2)
    
def jacob(n):
    if n == 0:
        return 0
    elif n==1:
        return 1
    else:
        return jacob(n - 1)+2*jacob(n-2)
        
    
def main(): 
    print("""A continuacion veremos 3 funciones distintas:
            lucca
            pell
            jacob""")
    numero=float(input("Elige tu numero para las 3 "))
    fA=lucca(numero)
    fB=pell(numero)
    fC=jacob(numero)
    
    print(fA,fB,fC,sep="--",end="\t")
    
if __name__=="__main__":
    main()