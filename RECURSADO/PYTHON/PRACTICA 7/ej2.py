# Ejercicio 2. El tiempo como tuplas
# 1. Proponer una representación con tuplas para modelar el tiempo: hh:mm:ss.
# 2. Escriba una función de creación de un elemento del tipo Tiempo, el cual tome tres datos, la hora,
# los minutos, y los segundos, y retorne un elemento de tipo Tiempo válido.
# 3. Escribir una función suma_Tiempo que reciba dos tiempos dados y devuelva la suma de éstos.
# 4. Escribir una función resta_Tiempo que reciba dos tiempos dados y devuelva la resta de éstos.

#1
#representación: time=(hora,minutos,segundos) / (int,int,int)

#2
def is_time(hora:int,minutos:int,segundos:int):
    hora=hora%24
    return 0 <= hora <=60 and 0 <= minutos <= 60 and 0 <= segundos <= 60

#3
def sumar_Tiempos(tiempo1,tiempo2):
    
    # Validamos los tiempos:
    if is_time(*tiempo1) and is_time(*tiempo2):
        
        # Sumar horas, minutos y segundos
        hora_sumada = tiempo1[0] + tiempo2[0]
        minutos_sumados = tiempo1[1] + tiempo2[1]
        segundos_sumados = tiempo1[2] + tiempo2[2]
        
        # Ajustar los segundos
        if segundos_sumados >= 60:
            minutos_sumados += segundos_sumados // 60
            segundos_sumados = segundos_sumados % 60
        
        # Ajustar los minutos
        if minutos_sumados >= 60:
            hora_sumada += minutos_sumados // 60
            minutos_sumados = minutos_sumados % 60
        
        # Ajustar las horas (asumiendo formato de 24 horas)
        hora_sumada = hora_sumada % 24
        
        tiempo_sumado=(hora_sumada,minutos_sumados,segundos_sumados)
        return tiempo_sumado
    else:
        return "El tipo de dato es inválido."
    
    
def test_sumar_Tiempo():
    t1=(2,3,50)
    t2=(6,9,10)
    t3=(1,1,1)
    t4=(60,60,60)
    assert(sumar_Tiempos(t1,t2))==(8,13,0)
    assert(sumar_Tiempos(t3,t4))==(14,2,1)
    
#4:

def restar_tiempos(tiempo1,tiempo2):
    if is_time(*tiempo1)and is_time(*tiempo2):
        r_s=abs(tiempo1[2]-tiempo2[2])
        r_m=abs(tiempo1[1]-tiempo2[1])
        r_h=abs(tiempo1[0]-tiempo2[0]) %24 #f.24hs
        
        return (r_s,r_m,r_h)
    else:
        return "invalide type."
    
def pytest_restar_tiempos():
    t1=(2,3,50)
    t2=(6,9,10)
    t3=(1,1,1)
    t4=(60,60,60)
    assert(restar_tiempos(t1,t2))==(4,6,40)
    assert(restar_tiempos(t3,t4))==(10,59,59)
    
