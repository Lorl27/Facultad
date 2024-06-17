def factorial_rec (n):
    """ Número: Natural.
    Nat->Nat
    Calcular en forma recursiva el factorial de un número natural dado.
    factorial_rec(5) = 120, factorial_rec(0) = 1, factorial_rec(1) = 1"""
    if n == 0:
        return 1
    else:
        return n* factorial_rec (n -1)
    
def test_factorial_rec():
    assert factorial_rec(5) == 120
    assert factorial_rec(10) == 3628800
    assert factorial_rec(1) == 1
    assert factorial_rec(0) == 1


def main():
    valor = int(input("Ingrese un valor natural para cualcular su factorial: "))
    print(f"El factorial de {valor} es {factorial_rec(valor)}")


main()
