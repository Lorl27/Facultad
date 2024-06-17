# Ejercicio 1. Las cartas como tuplas
# 1. Proponga una representación con tuplas para las cartas de la baraja francesa.
# 2. Escriba una función de creación de un elemento del tipo Carta, la cual tome dos datos, el valor y
# el palo, de una carta, y retorne un elemento de tipo Carta válido.
# 3. Escriba una función es_poker que reciba cinco cartas de la baraja francesa e informe (devuelva el
# valor lógico correspondiente) si esas cartas forman o no un poker (es decir si hay cuatro cartas con
# el mismo número)

#1:

def baraja_francesa():
    cartas=("A",1,2,3,4,5,6,7,8,9,10,"J","Q","K")
    palos=("pica","diamante","trebol","corazon")


#2:
def is_cartas(valor:int,palo:str)->tuple:
    if type(valor)==int and type(palo)==str:
        return (valor,palo)

#3:

def es_poker(c1,c2,c3,c4,c5):
    cartas = (c1, c2, c3, c4, c5)
    
    for i,x in cartas:
        if is_cartas(i,x):
            valores = [carta[0] for carta in cartas] #lista que contiene solo los valores

            for valor in valores:
                count = 0
                for v in valores:
                    if v == valor:
                        count += 1
                if count == 4:
                    return "si forma poker"
            
            return "no forma poker"

c1=(4,"p")
c2=(34,"a")
c3=(44,"a")
c4=(56,"a")
c5=(4,"6")


print(es_poker(c1,c2,c3,c4,c5))

c1=(4,"p")
c2=(4,"a")
c3=(4,"a")
c4=(5,"a")
c5=(4,"6")


print(es_poker(c1,c2,c3,c4,c5))
        

