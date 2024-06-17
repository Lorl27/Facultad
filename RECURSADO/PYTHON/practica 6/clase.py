#1

def es_letraA(letra:str):
    return letra=="A" or letra=="a" or letra=="á" or letra=="Á"

def cambiar_a(palabra:str):
    respuesta=""
    for x in range(len(palabra)):
        if(es_letraA(palabra[x])):
            respuesta+="*"
        else:
            respuesta+=palabra[x]

    return respuesta


#2
def es_letraÑ(letra:str):
    return letra=="Ñ" or letra=="ñ"

def cambiar_a_2(palabra:str):
    respuesta=""
    for x in range(len(palabra)):
        if(es_letraÑ(palabra[x])):
            respuesta+="*"
        else:
            respuesta+=palabra[x]

    return respuesta

#3:

def es_letraA(letra:str):
    return letra=="A" or letra=="a" or letra=="á" or letra=="Á"

def cambiar_a_3(palabra:str,reemplazo):
    respuesta=""
    for x in range(len(palabra)):
        if(es_letraA(palabra[x])):
            respuesta+=reemplazo
        else:
            respuesta+=palabra[x]

    return respuesta


#4:

def es_letraA(letra:str):
    return letra=="A" or letra=="a" or letra=="á" or letra=="Á"

def cambiar_a_4(palabra:str):
    contador=0
    for x in range(len(palabra)):
        if(es_letraA(palabra[x])):
            contador+=1

    return contador


#5:

def reto(cadena):
    indice=0
    
    while indice<len(cadena):
        if es_letraA(cadena[indice]):
            return cadena[indice:]
    
        indice+=1
        


print(reto("hola python"))
print(reto("python"))
print(reto(""))
print(reto(" python hola chau NO"))


# def main():
#     print("El siguiente programa le permitira cambiar cualquier letra A por un asterisco: ")
#     palabra=input("escriba aqui: ")
#     resultado=cambiar_a(palabra)
#     print(f"palabra=={palabra}==>{resultado}")
#     print("El siguiente programa le permitira cambiar cualquier letra  por un asterisco: ")
#     palabra=input("escriba aqui: ")
#     resultado2=cambiar_a_2(palabra)
#     print(f"palabra=={palabra}==>{resultado2}")
#     print("El siguiente programa le permitira cambiar cualquier letra A por un lo que usted eliga: ")
#     reemplazo=input("eliga su reemplazi: ")
#     palabra=input("escriba aqui: ")
#     resultado3=cambiar_a_3(palabra,reemplazo)
#     print(f"palabra=={palabra}==>{resultado3}")
#     print("El siguiente programa le permitira contar todas las letras A: ")
#     palabra=input("escriba aqui: ")
#     resultado4=cambiar_a_4(palabra)
#     print(f"palabra=={palabra}==>{resultado4}")



# if __name__=="__main__":
#     main()
