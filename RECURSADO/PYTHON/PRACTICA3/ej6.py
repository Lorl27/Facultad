
# Ejercicio 6. Diseñe funciones en Python que le permitan calcular las siguientes operaciones dadas por sus
# ecuaciones recursivas. Indique en la declaración de propósito de cada función, las operaciones aritméticas
# a las que corresponden. Las operaciones se suponen que se calculan sobre los números naturales.


# a)
# div_nat(n, m) =
# { 0 si m > n
# div_nat(n − m, m) + 1 si m 6 n


# b)
# mult_nat(n, m) =
# { 0 si m = 0
# mult_nat(n, m − 1) + n si m > 1


# c)
# pot_nat(n, m) =
# { 1 si m = 0
# pot_nat(n, m − 1) × n si m > 1


# d)
# rest_nat(n, m) =
# 
# 
# 
# 0 si m > n
# n si m = 0
# rest_nat(n − 1, m − 1) si m 6 n

def div_nat(n:int,m:int):
    if m>n:
        return 0 
    else:
        return div_nat(n-m,m)+1
    
def mult_nat(n:int,m:int):
    if m==0:
        return 0
    else:
        return mult_nat(n, m - 1) + n
        
def pot_nat(n:int,m:int):
    if m==0:
        return 1
    else:
        return pot_nat(n, m - 1) * n

def rest_nat(n:int,m:int):
    if m>n:
        return 0
    elif m==0:
        return n
    else:
        return rest_nat(n - 1, m - 1)
    
    
def main():
    print("""Realizaremos 4 operaciones sobre números NATURALES:
            division
            multiplicacon
            potencia
            resta""")
    a=int(input("ELige tu primer numero NATURAL para todas:"))
    b=int(input("ELige tu segundo numero NATURAL para todas:"))
    
    if a<=0 or b<=0:
        print("NO es posible. no es natural!")
        
    else:
        resultado_div=div_nat(a,b)
        resultado_mult=mult_nat(a,b)
        resultado_pot=pot_nat(a,b)
        resultado_rest=rest_nat(a,b)
        
        print(f"""LOs numeros ingreados fueron {a} y {b}.
                el resultado de la division fue {resultado_div},
                el resultado de la multiplicacion fue {resultado_mult},
                el resultado de la potenca fue {resultado_pot}
                y por ultimo, el de la resta: {resultado_rest}""")
        
if __name__=="__main__":
    main()