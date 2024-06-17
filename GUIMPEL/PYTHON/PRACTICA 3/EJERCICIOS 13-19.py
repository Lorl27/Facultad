# 3. Tuplas

# Ejercicio 13. Cartas como tuplas
# a) Proponga una representación con tuplas para las cartas de la baraja francesa.
# b) Escriba una función llamada poker que reciba cinco cartas de la baraja francesa e informe
# (devuelva el valor lógico correspondiente) si esas cartas forman o no un póker (es decir
# que hay 4 cartas con el mismo número).

corazones=(1,2,3,4,5,6,7,8,9,"J","Q","K")
diamantes=(1,2,3,4,5,6,7,8,9,"J","Q","K")
treboles=(1,2,3,4,5,6,7,8,9,"J","Q","K")
picas=(1,2,3,4,5,6,7,8,9,"J","Q","K")
baraja_francesa=(corazones,diamantes,treboles,picas)

def poker(carta1,carta2,carta3,carta4,carta5):
    if carta1==carta2==carta3==carta4 or carta1==carta2==carta3==carta5 or carta2==carta3==carta4==carta5 or carta3==carta4==carta5==carta1 or carta4==carta5==carta1==carta2:
        return True
    return False

print(poker(1,2,3,4,5))
print(poker(1,2,1,1,1))
print(poker(1,1,1,3,"K"))
print(poker("k","j","j","j","1"))

# Ejercicio 14. El tiempo como tuplas
# a) Proponga una representación con tuplas para el tiempo.
# b) Escriba una función sumaTiempo que reciba dos tiempos dados y devuelva su suma.
horas=(1,2,3,4,5,6,7,8,9,10,11,12)
minutos=(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60)
segundos=(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60)
tiempo=(horas,minutos,segundos)


def sumaTiempo(tiempo1,tiempo2):
    horasT=0
    minutosT=0
    segundosT=0
    if tiempo1[0] in tiempo[0] or tiempo2[0] in tiempo[0]:
        hora=tiempo1[0]
        hora2=tiempo2[0]
        horasT=hora+hora2
    if tiempo1[1] in tiempo[1] or tiempo2[1] in tiempo[1]:
        minuto=tiempo1[1]
        minuto2=tiempo2[1]
        minutosT=minuto+minuto2
        if minuto>=60 or minuto2>=60:
            minuto-=60
            minuto2-=60
        if minutosT>=60:
            minutosT-=60
            horasT+=1
    if tiempo1[2] in tiempo[2] or tiempo2[2] in tiempo[2]:
        segundo=tiempo1[2]
        segundo2=tiempo2[2]
        segundosT=segundo+segundo2
        if segundosT>=60 or segundo>=60 or segundo2>=60:
            minutosT+=1
            segundosT-=60
    tiempoT=(horasT,minutosT,segundosT)
    return tiempoT

t1=(1,30,2)
t2=(2,1,0)
t3=(1,60,3)
t4=(5,2,67)
print(sumaTiempo(t1,t2))
print(sumaTiempo(t3,t4))

# Ejercicio 15. Escriba una función diaSiguienteE que, dada una fecha expresada como la
# tupla (Día, Mes, Año) (donde Día, Mes y Año son números enteros), calcule el día siguiente al
# dado en el mismo formato.

#fecha=(dia,mes,año)
def diaSiguienteE(tupla):
    dia=tupla[0]
    mes=tupla[1]
    anio=tupla[2]
    
    dia+=1

    if check_mes(mes):
        if dia>31:
            mes+=1
            dia=1
            
        if mes>12:
            anio+=1
            mes=1
    else:
        if check_bis(anio):
            if dia>29:
                mes+=1
                dia=1
        else:
            if dia>30:
                mes+=1
                dia=1
                
        if mes>12:
            anio+=1
            mes=1
            
    return (dia,mes,anio)

def check_mes(mes):
    return mes in [1, 3, 5, 7, 8, 10, 12]

def check_bis(anio):
    return anio%4==0 and (anio % 100 != 0 or anio % 400 == 0)


f1=(30,12,2003)
f2=(1,12,2003)
f3=(31,7,2001)
f4=(30,10,1080)
f5=(31,10,1080)
f6=(28,11,1992) #bisiesto
f7=(29,2,1992)
f8=(28,2,1992)
f9=(28,3,1992)
f10=(29,3,1992)
f11=(30,11,2020)

print(diaSiguienteE(f1)) #31,12,2003
print(diaSiguienteE(f2)) #2.12.2003
print(diaSiguienteE(f3)) #1,8,2001
print(diaSiguienteE(f4)) #31,10,1080
print(diaSiguienteE(f5)) #1,11,1080
print(diaSiguienteE(f6)) #29,11,1992
print(diaSiguienteE(f7)) #1,3,1992 
print(diaSiguienteE(f8)) #29,2,1992
print(diaSiguienteE(f9)) #29,3,1992
print(diaSiguienteE(f10)) #30,3,1992
print(diaSiguienteE(f11)) #1,12,2020

# Ejercicio 16. Escriba una función diaSiguienteT que, dada una fecha expresada como la
# tupla (Día, Mes, Año) (donde Día y Año son números enteros, y Mes es el texto "Ene", "Feb",
# ..., "Dic", según corresponda), calcule el día siguiente al dado en el mismo formato.

def check_mes2(mes,meses):
    return mes in [meses[1], meses[3], meses[5], meses[7], meses[8], meses[10], meses[12]]

def diaSiguienteT(tupla):
    dia=tupla[0]
    mes=tupla[1]
    anio=tupla[2]
    
    dia+=1
    
    meses=[0,"Ene", "Feb","Mar","Abril", "Mayo", "Jun","Jul", "Agos","Sep", "Oct","Nov", "Dic"]

    mesI=meses.index(mes)
    
    if check_mes2(mes,meses):
        if dia>31:
            mesI+=1
            mes=meses[mesI]
            dia=1
            
        if mesI>12:
            anio+=1
            mes=meses[1]
    else:
        if check_bis(anio):
            if dia>29:
                mesI+=1
                mes=meses[mesI]
                dia=1
        else:
            if dia>30:
                mesI+=1
                mes=meses[mesI]
                dia=1
                
        if mesI>12:
            anio+=1
            mes=meses[1]
            
    return (dia,mes,anio)

f11=(30,"Dic",2003)
f21=(1,"Dic",2003)
f31=(31,"Jul",2001)
f41=(30,"Oct",1080)
f51=(31,"Oct",1080)
f61=(28,"Nov",1992) #bisiesto
f71=(29,"Feb",1992)
f81=(28,"Feb",1992)
f91=(28,"Mar",1992)
f101=(29,"Mar",1992)
f111=(30,"Nov",2020)

print(diaSiguienteT(f11)) #31,12,2003
print(diaSiguienteT(f21)) #2.12.2003
print(diaSiguienteT(f31)) #1,8,2001
print(diaSiguienteT(f41)) #31,10,1080
print(diaSiguienteT(f51)) #1,11,1080
print(diaSiguienteT(f61)) #29,11,1992
print(diaSiguienteT(f71)) #1,3,1992 
print(diaSiguienteT(f81)) #29,2,1992
print(diaSiguienteT(f91)) #29,3,1992
print(diaSiguienteT(f101)) #30,3,1992
print(diaSiguienteT(f111)) #1,12,2020


# Ejercicio 17. Dominó
# a) Escriba una función que tome dos fichas de dominó e indique si encajan o no. Las fichas
# son recibidas en dos tuplas, por ejemplo: (3, 4) y (5, 4).
# b) Escriba una función que tome dos fichas de dominó e indique si encajan o no. Las fichas
# son recibidas en una cadena, por ejemplo: "[3-4 2-5]". Nota: utilizar la función split
# de cadenas.


def fichas(ficha1:tuple,ficha2:tuple)->bool:
    if ficha1==ficha2 or ficha1[1]==ficha2[1] or ficha1[1]==ficha2[0] or ficha1[0]==ficha2[0] or ficha1[0]==ficha2[1]:
        return True
    return False

print(fichas((3,4),(5,4)))
print(fichas((3,4),(4,4)))
print(fichas((4,3),(5,4)))
print(fichas((4,3),(3,4)))
print(fichas((4,3),(5,3)))
print(fichas((4,5),(9,3)))

def fichas2(str:str)->bool:
    fichas=str[1:-1].split() #saco los corchetes y, las separo
    ficha1=fichas[0]
    ficha2=fichas[1]
    
    f1_izq,f1_der=ficha1.split("-")
    f2_izq,f2_der=ficha2.split("-")
    
    if ficha1==ficha2 or f1_der==f2_der or f1_der==f2_izq or f1_izq==f2_izq or f1_izq==f2_der:
        return True
    return False
    
    

print(fichas2("[3-4 2-5]"))