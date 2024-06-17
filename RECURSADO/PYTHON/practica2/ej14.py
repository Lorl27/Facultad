# Ejercicio 14. Suponiendo que el primer día del año fue lunes, escribir una función que reciba
# un número con el día del año (de 1 a 366) y devuelva el día de la semana que le toca. Por
# ejemplo: si recibe ’3’ debe devolver ’miércoles’, si recibe ’9’ debe devolver ’martes’.

def num_to_sem(numero:int):
    if numero&7==0:
        print("Domingo")
    elif numero%7==6:
        print("Sabado")  #7-1=6
    elif  numero%7==5:
        print("Viernes")
    elif numero%7==4:
        print("Jueves")
    elif numero%7==3:
        print("Miercoles")
    elif numero%7==2:
        print("Martes")
    else:
        print("Lunes")
        
def main():
    sem=int(input("Inngrese el num del año: "))
    print("Su conversion es:")
    num_to_sem(sem)
    
if __name__=="__main__":
    main()