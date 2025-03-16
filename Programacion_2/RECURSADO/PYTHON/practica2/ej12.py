
# Ejercicio 12. Definir la función observar_clima la cual clasifica con una “etiqueta” ciertos
# intervalos numéricos asociados a temperaturas ambientes. La categorización de las temperaturas es la siguiente:
# Intervalo Denominación
# menos de 0 grados "Helado"
# entre 0 y 15 grados "Frío"
# entre 15 y 25 grados “Agradable”
# más de 25 grados “Caluroso”

def funcion_clima(temperatura:int):
    if 0>temperatura:
        print("Helado")
    elif 0<= temperatura <15:
        print("Frío")
    elif 15<= temperatura <25:
        print("Agradable")
    else:
        print("Caluroso")
        

def main():
    temp=int(input("Ingrese su temp: "))
    print("El clima es: ")
    funcion_clima(temp)
    
if __name__=="__main__":
    main()