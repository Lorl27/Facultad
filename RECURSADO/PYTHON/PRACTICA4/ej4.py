# Bucles For
"""
    The function calculates the final amount to be paid based on an initial amount, interest rate, and
    number of years, displaying yearly interest amounts and the total amount paid.
    
    :param pesos: The parameter `pesos` represents the initial amount of money borrowed
    :type pesos: float
    :param tasa_interes: The parameter `tasa_interes` represents the interest rate for the credit. It is
    a floating-point number that indicates the percentage of interest to be applied to the initial
    amount over the specified number of years
    :type tasa_interes: float
    :param anios: The parameter `anios` represents the number of years for which the loan amount will be
    paid back. It is an integer value that indicates the duration over which the loan will be repaid
    :type anios: int
    :return: The function `monto_credito` is returning the final amount to be obtained after paying off
    the credit.
"""


# Ejercicio 4. Escriba una función que reciba una cantidad de pesos, una tasa de interés y un número de
# años para pagarlo, y retorne, como resultado, el monto final a obtener. La fórmula a utilizar es:
# Cn = C × (1 + x
# 100 )n
# Donde C es el capital inicial, x es la tasa de interés y n es el número de años a calcular. En el programa
# se podrá visualizar los intereses por año, el monto original pedido, el monto final de dinero abonado. Los
# intereses por año, mostrarlo de forma tabular, encabezado por el monto original y al final el monto total
# pagado por el crédito.


def monto_credito(pesos:float,tasa_interes:float,anios:int)-> float:
    credito=0
    contador=0
    while contador<=anios:
        credito+=(1+(tasa_interes/100))**contador
        credito*=pesos
        
        print(f"""intereses x año:
                año:{contador+1} - interes {credito:0.2f}""")
    
        contador+=1
        
    print(f"""PESOS={pesos}
            INTERESES X AÑO={tasa_interes}
            AÑOS PARA PAGAR:{anios}
            
            TOTAL: {credito:0.2f}""")
    
    return credito


def main():
    """
    The main function takes user input for the amount of money, interest rate, and number of years, and
    then calls the monto_credito function with these values.
    """
    cant_pesos=float(input("elige la plata: "))
    cant_interes=float(input("elige el interes: "))
    cant_panios=int(input("elige los años: "))
    monto_credito(cant_pesos,cant_interes,cant_panios)
    
    
if __name__=="__main__":
    main()