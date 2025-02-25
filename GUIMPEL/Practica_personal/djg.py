def suma2 (a,b):
    result= a + b
    return result

def dividir(a,b):
    return (a/b)

barbie= dividir(4600,4)
opp= dividir(6800,4)

print(suma2(barbie,opp))

def suma(n,m):
    return n+m

def ejercicio5(n):
    contador=0
    for x in range(n,50):
        print(suma(x,contador))
    contador+=1
print(ejercicio5(2))

def pedir_numero_positivo():
    while True:
        try:
            numero = float(input("Ingrese un número positivo: "))
            if numero > 0:
                return numero  # Devuelve el número si es positivo
            else:
                print("Por favor, ingrese un número positivo.")
        except ValueError:
            print("Error: Debe ingresar un número válido.")

# Llama a la función para obtener un número positivo
numero_positivo = pedir_numero_positivo()

print(f"Ha ingresado el número positivo: {numero_positivo}")

def promedio(x):
    if len(x) ==0:
        return 0
    else:
        return sum(x)/len(x) #sum == suma de touts le ingredients of x , if x it´s a list.

notas=[]

def ej8():
    usu=input("¿Desea ingresar una nota?. Responda con SI/NO ")
    while usu == "SI":
        nota= int(input("Ingresala acá: "))
        notas.append(nota)
        print("notas=",notas)
        ej8()
        break
    print("tu promedio es:",promedio(notas))



ej8()

condicion = 2

acciones = {
    1: "Hacer a",
    2: "Hacer b",
    3: "Hacer c"
}

resultado = acciones.get(condicion, "Hacer d")
print(resultado)

#simulacion de switch en python


