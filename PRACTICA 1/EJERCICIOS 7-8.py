#Primeros programas usando cadenas

#Ejercicio 7. Escriba un programa que reciba un nombre y retorne el nombre pasado concatenado 2 veces.
# Es decir, supongamos que la función se llama duplica, si hacemos duplica(”F ederico”)
# el resultado que deberíamos obtener sería: ”F edericoF ederico”.

def duplica(nombre):
    return nombre*2

print(duplica("Federico"))

#Ejercicio 8. Escriba un programa que reciba un nombre y un número n,
# y retorne el nombre pa-sado concatenado n veces. Es decir, supongamos que la función se llama duplica,
# si hacemos duplica(”F ederico”, 3) el resultado que deberíamos obtener sería:
# ”F edericoF edericoF ederico”

def ej8(nombre,num):
    return nombre*num

print(ej8("Federico",3))