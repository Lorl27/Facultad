# Ejercicio 3. Usando la función, dada como ejemplo en la presentación de La Receta en Python, para
"""
    The code defines a function to convert temperatures from Fahrenheit to Celsius and generates a
    conversion table from 0°F to 120°F in increments of 10°F.
    
    :param temp_f: The `temp_f` parameter represents the temperature in Fahrenheit that you want to
    convert to Celsius. The `far_cel` function takes this Fahrenheit temperature as input and returns
    the equivalent temperature in Celsius
    :return: The `temp_c` variable, which stores the temperature in Celsius, is being returned by the
    `far_cel` function.
"""
# convertir una temperatura en Fahrenheit a Celsius se pide que genere una tabla de conversión de tempe-
# raturas, desde 0◦F hasta 120◦F, de 10 en 10.


def far_cel (temp_f):
    temp_c = (temp_f -32) *5/9
    return temp_c


def temp_conver():
    temp_f=0
    while temp_f<=120:
        print(f"{temp_f}F to C = {far_cel(temp_f):0.2f}C")
        temp_f+=10
    
    
def main():
    temp_conver()    
    
if __name__=="__main__":
    main()