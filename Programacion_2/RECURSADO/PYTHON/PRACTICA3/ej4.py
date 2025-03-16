# Ejercicio 4. Redefinir la función factorial definida de forma recursiva no final, pero ahora utilizando una
# recursión final.

# def fibonnaci(n):
#     if n == 0 or n == 1:
#         return n
#     else:
#         return fibonacci (n -1) + fibonacci (n -2)

def fibonacci(n,result=0):
    if n==0 or n==1:
        return n
    else:
        return fibonacci(n-1,result) + fibonacci(n-2,result+n)
    
def main():
    print("FIBONACCI PERO RECURSIVO FINAL OMG")
    num=int(input("Choose your number: "))
    resultado=fibonacci(num)
    print(resultado)
    
if __name__=="__main__":
    main()