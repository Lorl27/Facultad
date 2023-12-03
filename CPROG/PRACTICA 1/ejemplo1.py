def SumN (suma=0,contador=0):
    num=int(input())
    if num==0:
        print("la suma fue de", suma, "y se ingresaron", contador, " numeros")
    else:
        SumN(suma+num,contador+1)