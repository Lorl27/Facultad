# Ejercicio 1. Una variante de esta función es la función cuenta_progresiva la cual cuenta en forma ascen-
# dente comenzando desde cero hasta el valor 10, y al llegar a éste último valor, emite el mensaje Boom!.
# cuenta_progresiva (n) =
# { "Boom!" si n = 10
# cuenta_progresiva(n+1) si n > 0 ∧ n < 10
# Te pedimos en este caso que:
# (a) Implementes y diseñes una función recursiva en Python que nos permita programar la función
# cuenta_progresiva. ¿Qué diferencia hay con la anterior? ¿Cómo debo invocarla en la función main?

# (b) ¿Qué problemas podrían llegar a surgir en este tipo de código? ¿Puedo variar el tope de conteo?: Si,
# no, y/o porqué, ¿qué necesitarías? De ser posible, implementar dicha función pidiéndole al usuario
# que ingrese un valor que indique hasta donde se realizará el conteo. En caso contrario argumenta con
# palabras tu decisión.

def cuenta_progresiva(n):
    if n==10:
        return 'boom!'
    elif 0<n<10:
        return str(n)+ "\n" + cuenta_progresiva(n-1)
    elif n<0:
        return 'no es posible retroceder'
    elif n>10:
        return 'no es posible avanzar'
    else:
        return 'fin'
    
def cuenta_progresiva_mejorada(n:float,conteo_max:int):
    if n==conteo_max:
        return 'boom!'
    elif 0<n<conteo_max:
        return str(n)+ "\n" + cuenta_progresiva_mejorada(n-1,conteo_max)
    elif n<0:
        return 'no es posible retroceder'
    elif n>conteo_max:
        return 'no es posible avanzar'
    else:
        return 'fin'    
    
def main():
    print("""Este programa sirve para ver la cuenta regresiva de un numero dado:
            ej nro a:""")
    numero=int(input("Elige tu nro: "))
    result_A=cuenta_progresiva(numero)
    print(result_A)
    print("Ahora, item b:")
    limite=int(input("Elige tu limite maximo!"))
    result_b=cuenta_progresiva_mejorada(numero,limite)
    print(result_b)
    
    
if __name__=="__main__":
    main()