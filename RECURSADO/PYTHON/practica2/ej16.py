# Ejercicio 16. Escribir un programa que reciba como entrada un entero representando un año
# (por ejemplo 751, 1999, o 2158), y muestre por pantalla el mismo año escrito en números
# romanos.

#valores:
# M=1000
# D=500
# C=100
# L=50
# X=10
# V=5
# I=1

# def anio_a_romano(anio:int):
#     romano=""
    
#     # Miles
#     miles = anio // 1000
#     romano += "M" * miles
#     anio %= 1000
    
#     #Centenas:
#     if anio >= 900:
#         romano += "CM"
#         anio -= 900
        
#     elif anio >= 500:
#         romano += "D"
#         anio -= 500
        
#     elif anio >= 400:
#         romano += "CD"
#         anio -= 400
        
#     romano += "C" * (anio // 100)
#     anio %= 100

#     # Decenas
#     if anio >= 90:
#         romano += "XC"
#         anio -= 90
        
#     elif anio >= 50:
#         romano += "L"
#         anio -= 50
        
#     elif anio >= 40:
#         romano += "XL"
#         anio -= 40
        
#     romano += "X" * (anio // 10)
#     anio %= 10

#     # Unidades
#     if anio == 9:
#         romano += "IX"
#         anio -= 9
        
#     elif anio >= 5:
#         romano += "V"
#         anio -= 5
        
#     elif anio == 4:
#         romano += "IV"
#         anio -= 4
        
#     romano += "I" * anio

#     return romano

def año_romano(año):
    year = str(año)
    index = len(year) - 1
    unidades = "IXCM"
    unidad = ""
    decena = ""
    centena = ""
    millar = ""


    for x in range(0,len(year)):
        y = int(year[index - x]) # Separa las cifras del año
        r = unidades[x] # Agarra las unidades romanas según la cantidad de cifras

        # Transforma las unidades
        # Si es una unidad, transforma la última cifra en su valor romano
        if r == "I" :
            if y < 4:
                unidad = y * r
            elif y < 5:
                unidad = "IV"
            elif y == 5:
                unidad ="V"
            elif y > 5 and y < 9:
                unidad = f"V{(y - 5) * r}"
            else:
                unidad = "IX"

        # Transforma las decenas
        elif r == "X" :
            if y < 4:
                decena = y * r
            elif y < 5:
                decena = "IL"
            elif y == 5:
                decena = "L"
            elif y > 5 and y < 9:
                decena = f"L{(y - 5) * r}"
            else:
                decena = "XC"

        # Transforma las centenas
        elif r == "C" :
            if y < 4:
                centena = y * r
            elif y < 5:
                centena = "ID"
            elif y == 5:
                centena = "D"
            elif y > 5 and y < 9:
                centena = f"D{(y - 5) * r}"
            else:
                centena = "CM"
        
        # Transforma los millares
        elif r == "M" :
            if y < 4:
                millar = y * r
            elif y < 5:
                millar = "|IV|"
            elif y == 5:
                millar = "|V|"
            elif y > 5 and y < 9:
                millar = f"|V{(y - 5) * "I"}|"
            else:
                millar = "|IX|"

    # Concatena las cifras transformadas a números romanos
    print(millar + centena + decena + unidad)

def main():
    anio = int(input("Ingrese el año (número entero): "))
    romano = año_romano(anio)
    #print(f"El año {anio} en números romanos es: {romano}")

if __name__ == "__main__":
    main()