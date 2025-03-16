# Ejercicio 3. La fecha como tuplas
# 1. Proponer una representación con tuplas para modelar una fecha: dd:mm:aaaa.
# 2. Escriba una función de creación de un elemento del tipo Fecha, el cual toma tres datos, el día, el
# mes, y el año; y retornando un elemento de tipo Fecha válido. Los valores serán enteros en este
# caso.
# 3. Escribir una función llamada diaAnteriorNum que dada una fecha expresada como la terna (Día,
# Mes, Año) (donde Día, Mes y Año son números enteros) calcule el día anterior al dado, en el
# mismo formato.
# 4. Escriba una función diaAnteriorTex que dada una fecha expresada como la terna (Día, Mes, Año)
# (donde Día y Año son números enteros, y Mes es el texto: Ene, Feb, ..., Dic, según corresponda)
# calcule el día anterior al dado, en el mismo formato.

# fecha=(dia,mes,año)/(int,int,int)


# 2:
def is_day_valid(mes: int, dia: int, year) -> bool:
    if mes == 2:
        if is_year_bis(year):
            return 0 < dia <= 29
        else:
            return 0 < dia <= 28
    elif mes in [1,3,5,7,8,10,12]:
        return 0 < dia <= 31
    elif mes in [4, 6, 9, 11]:
        return 0 < dia <= 30
    return False
    


def is_mes_valid(mes: int) -> bool:
    return 0 < mes <= 12


def is_year_bis(year: int) -> bool:
    return (year % 4 == 0 and (not year % 100 == 0 or year % 400 == 0))


def is_year_valid(year: int):
    return 0 < year


def is_fecha(dia: int, mes: int, year: int) -> bool:
    return is_day_valid(mes, dia, year) and is_mes_valid(mes) and is_year_valid(year)


def test_is_fecha():
    f1 = (12, 3, 1)
    f2 = (999, 9, 10)
    f3 = (1, 0, 1)
    f4 = (1, 1, 0)

    assert (is_fecha(*f1)) == True
    assert (is_fecha(*f2)) == False
    assert (is_fecha(*f3)) == False
    assert (is_fecha(*f4)) == False


# 3:


def dia_anterior_NUM(dia: int, mes: int, year: int) -> tuple:
    if is_fecha(dia, mes, year):

        fecha_ant = (0, 0, 0)
        if dia > 1:
            dia -= 1
            
        else:
            if mes == 1:
                mes = 12
                dia = 31
                year -= 1
            else:
                mes -= 1
                if mes == 2:
                    if is_year_bis(year):
                        dia = 29
                    else:
                        dia = 28
                elif mes in [4, 6, 9, 11]:
                    dia = 30
                else:
                    dia = 31
            
        
            
        fecha_ant=(dia,mes,year)
        
        if not is_fecha(dia, mes, year):
            return "ERROR"

        return fecha_ant
    else:
        return "ERROR."

def test_dia_anterior():
    f1 = (12, 3, 1)
    f2 = (999, 9, 10)
    f3 = (12, 12, 12)
    f4 = (31, 1, 2004)
    f5 = (31, 1, 2003)
    f6 = (31, 2, 2004)
    f7 = (28, 2, 2004)
    f9 = (1, 1, 2004)
    f10 = (1, 2, 2004)
    f11 = (1, 12, 2004)

    assert (dia_anterior_NUM(*f1)) == (11,3,1)
    assert (dia_anterior_NUM(*f2)) == "ERROR."
    assert (dia_anterior_NUM(*f3)) == (11,12,12)
    assert (dia_anterior_NUM(*f4)) == (30,1,2004)
    assert (dia_anterior_NUM(*f5)) == (30,1,2003)
    assert (dia_anterior_NUM(*f6)) == "ERROR."
    assert (dia_anterior_NUM(*f7)) == (27,2,2004)
    assert (dia_anterior_NUM(*f9)) == (31,12,2003)
    assert (dia_anterior_NUM(*f10)) == (31,1,2004)
    assert (dia_anterior_NUM(*f11)) == (30,11,2004)
    
    
#4:

def is_day_validSTR(mes: str, dia: int, year) -> bool:
    mes=mes.lower()
    if mes == "febrero":
        if is_year_bis(year):
            return 0 < dia <= 29
        else:
            return 0 < dia <= 28
    elif mes in ["enero","marzo","mayo","julio","agosto","octubre","diciembre"]:
        return 0 < dia <= 31
    elif mes in ["abril", "junio", "noviembre", "septiembre"]:
        return 0 < dia <= 30
    return False
    


def is_mes_valid_STR(mes: str) -> bool:
    mes=mes.lower()
    return mes in ["enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"]


def is_year_bis(year: int) -> bool:
    return (year % 4 == 0 and (not year % 100 == 0 or year % 400 == 0))


def is_year_valid(year: int):
    return 0 < year


def is_fechaSTR(dia: int, mes: str, year: int) -> bool:
    return is_day_validSTR(mes, dia, year) and is_mes_valid_STR(mes) and is_year_valid(year)


def test_is_fechaSTR():
    f1 = (12, "marzo", 1)
    f2 = (999, "septiembre", 10)
    f3 = (1, "", 1)
    f4 = (1, "enero", 0)

    assert (is_fechaSTR(*f1)) == True
    assert (is_fechaSTR(*f2)) == False
    assert (is_fechaSTR(*f3)) == False
    assert (is_fechaSTR(*f4)) == False


# 3:


def dia_anterior_TXT(dia: int, mes: str, year: int) -> tuple:
    if is_fechaSTR(dia, mes, year):
        meses=["enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"]
        mes=mes.lower()
        m_i=meses.index(mes)
        
        fecha_ant = (0, 0, 0)
        if dia > 1:
            dia -= 1
            
        else:
            if mes == "enero":
                mes = "diciembre"
                dia = 31
                year -= 1
            else:
                m_i -= 1
                mes=meses[m_i]
                if mes == "febrero":
                    if is_year_bis(year):
                        dia = 29
                    else:
                        dia = 28
                elif mes in ["abril", "junio", "noviembre", "septiembre"]:
                    dia = 30
                else:
                    dia = 31
            
        
            
        fecha_ant=(dia,mes,year)
        
        if not is_fechaSTR(dia, mes, year):
            return "ERROR"

        return fecha_ant
    else:
        return "ERROR."

def test_dia_anterior():
    f1 = (12, "marzo", 1)
    f2 = (999, "septiembre", 10)
    f3 = (12, "diciembre", 12)
    f4 = (31, "enero", 2004)
    f5 = (31, "enero", 2003)
    f6 = (31, "febrero", 2004)
    f7 = (28, "febrero", 2004)
    f9 = (1, "enero", 2004)
    f10 = (1, "febrero", 2004)
    f11 = (1, "diciembre", 2004)

    assert (dia_anterior_TXT(*f1)) == (11,"marzo",1)
    assert (dia_anterior_TXT(*f2)) == "ERROR."
    assert (dia_anterior_TXT(*f3)) == (11,"diciembre",12)
    assert (dia_anterior_TXT(*f4)) == (30,"enero",2004)
    assert (dia_anterior_TXT(*f5)) == (30,"enero",2003)
    assert (dia_anterior_TXT(*f6)) == "ERROR."
    assert (dia_anterior_TXT(*f7)) == (27,"febrero",2004)
    assert (dia_anterior_TXT(*f9)) == (31,"diciembre",2003)
    assert (dia_anterior_TXT(*f10)) == (31,"enero",2004)
    assert (dia_anterior_TXT(*f11)) == (30,"noviembre",2004)