import random

palabras_posibles=("buenas","tardes","como","te","va")
word_tuple = ("hola", "casa", "perro", "gato", "amigo", "familia", "tiempo", "trabajo", "estudio", "viaje",
            "película", "libro", "música", "teléfono", "computadora", "internet", "amor", "odio", "feliz",
            "triste", "comer", "beber", "caminar", "correr", "dormir", "despertar", "jugar", "aprender",
            "escuchar", "hablar", "pensar", "saber", "conocer", "ver", "sentir", "tocar", "ayudar", "nadar",
            "bailar", "cantar", "comprar", "vender", "dinero", "fuego", "agua", "aire", "sol", "luna", "cielo",
            "nube", "montaña", "río", "mar", "ciudad", "país", "gobierno", "historia", "arte", "educación", "religión",
            "cultura", "deporte", "salud", "enfermedad", "vida", "muerte")


def elegirPalabra(coleccion_palabras:tuple)->str:
    if isinstance(coleccion_palabras,tuple):
        palabra_r=random.choice(coleccion_palabras)
        return palabra_r

def buscarPosiciones(letra:str,palabra:str)->list:
    posiciones=[]
    largo=len(palabra)
    
    for indice in range(largo):
        if letra==palabra[indice]:
            posiciones.append(indice)
            
    return posiciones

# def actualizarPalabra(palabra:str,posiciones: list)->str:
#     resultado = list(palabra)
#     largo=len(palabra)
#     for indice in range(largo):
#         if indice not in posiciones:
#             resultado[indice]="_" 
            
#     return "".join(resultado)

def ahorcado(coleccion_palabras:tuple)->str:
    max=7
    intentos=0
    letras_usadas=[]
    alfabeto="abcedfghijklmnñopqrstuvwxyz"
    palabra_random=elegirPalabra(coleccion_palabras)
    palabra_modificada = "_" * len(palabra_random)
    while intentos<max:
        letra_usu=input("Ingrese una letra: ").lower()
        while letra_usu not in alfabeto:
            letra_usu=input("Has ingresado un caracter incorrecto.Intente de nuevo: ")
        while letra_usu in letras_usadas:
            letra_usu=input("Esa letra ya esta usada. ingrese otra: ")
        else:
            letras_usadas.append(letra_usu)
            
        posiciones_palabra=buscarPosiciones(letra_usu,palabra_random)
        #palabra_modificada=actualizarPalabra(palabra_random,posiciones_palabra)   
        
        if posiciones_palabra:
            for posicion in posiciones_palabra:
                palabra_modificada = palabra_modificada[:posicion] + letra_usu + palabra_modificada[posicion+1:]
        else:
            print("Letra no presente en la palabra.")
            intentos += 1
            
        print(palabra_modificada)
        
        if palabra_modificada==palabra_random:
            return "has ganado el juego" 
        
    return f"Has perdido el juego. La palabra era {palabra_random}"        

print(ahorcado(word_tuple))