# Ejercicio 11. Manejo de contraseñas
# a) Escribir un programa que contenga una contraseña inventada, que le pregunte al usuario la contraseña, y no le permita continuar hasta que la haya ingresado correctamente.
# b) Modificar el programa anterior para que solamente permita una cantidad fija de intentos.
# c) Modificar el programa anterior para que sea una función que devuelva si el usuario ingresó o no la
# contraseña correctamente, mediante un valor booleano (True o False)


#a
def contra_a():
    contraseña="peligro"
    usuario=""
    while usuario!=contraseña:
        usuario=input("ingrese la contraseña: ")
#b
def contra_b():
    contraseña="peligro"
    usuario=""
    contador=0
    while usuario!=contraseña and contador<3:
        contador+=1
        usuario=input("ingrese la contraseña: ")
        print(f"contraseña incorrecta.intento nro {contador}")
#c
def contra_c():
    contraseña="peligro"
    usuario=""
    contador=0
    while usuario!=contraseña and contador<3:
        contador+=1
        usuario=input("ingrese la contraseña: ")
        print(f"{usuario==contraseña}- intento nro {contador}")
        
contra_a()
contra_b()
contra_c()