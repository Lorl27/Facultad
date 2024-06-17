def factorial_ite(num):
    """Número: Natural.
    Nat->Nat
    Calcular en forma iterativa el factorial de un número natural dado.
    factorial_ite(5) = 120, factorial_ite(0) = 1, factorial_ite(1) = 1
    """
    fact = 1
    for i in range(2, num + 1):
        fact = fact * i
    return fact


def test_factorial_ite():
    assert factorial_ite(5) == 120
    assert factorial_ite(10) == 3628800
    assert factorial_ite(1) == 1
    assert factorial_ite(0) == 1


def main():
    valor = int(input("Ingrese un valor natural para cualcular sufactorial: "))
    print("El factorial de ", valor, "es ", factorial_ite(valor))


main()
