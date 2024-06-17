
import random
r = random.random ()

# random() Genera un número aleatorio entre 0 y 1
# randint(x,y) Genera un número entero aleatorio entre x e y, incluyendo ambos
# randrange(x) Genera un número entero aleatorio entre 0 y x-1

# 1) Simule lanzamientos de un dado. Muestre el resultado en cada intento y finalice cuando
# salga el número 6. También añada cuantas veces se lanzó el dado.

def dado():
    conteo=0
    while conteo <6:
        dadito = random.randrange(7)
        print("El número fue: ", dadito)
        conteo+=1
    print("Intentos:" , conteo)

dado()

# 2) Simule n lanzamientos de dos dados, donde n es un valor que se debe pedir que se
# ingrese por teclado. Muestre cuántas veces los dados tuvieron el mismo resultado.

def lanzamientos():
    conteo=0
    contador=0
    intentos=int(input("Ingrese una cantidad n de lanzamientos: "))
    while conteo != intentos:
        dado1= random.randrange(7)
        dado2=random.randrange(7)
        print(f"dado 1 == {dado1} y dado 2 == {dado2}")
        conteo+=1
        if int(dado1)==int(dado2): # type: ignore
            contador+=1
    print(contador)

lanzamientos()

# 3) Simule n lanzamientos de un dado en un juego con las siguientes reglas: si sale 6 gana
# 4 pesos; si sale 3 gana 1 dólar; si sale 1 sigue jugando y si sale 2, 4 o 5 pierde 2 pesos.
# Muestre los valores que salen y el resultado final del juego.

def simulador():
    conteo=0
    pesos=0
    dolar=0
    intentos=int(input("Ingrese un num de intentos: "))
    while conteo != intentos:
        dado=int(random.randrange(7))
        conteo+=1
        if dado ==6:
            pesos+=4
            print(f"Ganaste 4 pesos, total: {pesos} pesos y {dolar} dolares")
            conteo+=1
        elif dado==3:
            dolar+=1
            print(f"Ganaste 1 dolar, total: {pesos} pesos y {dolar} dolares")
        elif dado ==1:
            print("Tenes otra chance")
            conteo-=1
        elif dado ==2 or dado==5 or dado==4:
            pesos-=2
            print(f"perdiste 2 pesos, total: {pesos} pesos y {dolar} dolares")
    print(f"total: {pesos} pesos y {dolar} dolares")

simulador()