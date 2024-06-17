def set_dia(fecha,dia_nuevo):
    fecha_nueva=(dia_nuevo,)+fecha[1:] #copia
    return fecha_nueva


def set_mes(fecha,mes_nuevo):
    fecha_nueva=(fecha[0],)+(mes_nuevo,)+fecha[2:] #cuidado error!!
    return fecha_nueva

def set_anio(fecha,anio_nuevo):
    fecha_nueva=fecha[:-1]+(anio_nuevo,)
    return fecha_nueva

def set_fecha_NUEVA(fecha,dia_nuevo,mes_nuevo,anio_nuevo):
    dia_n=set_dia(fecha,dia_nuevo)
    mes_n=set_mes(fecha,mes_nuevo)
    anio_n=set_anio(fecha,anio_nuevo)

    fecha=(dia_n[0],)+(mes_n[1],)+(anio_n[-1],)
    return fecha

print(set_anio((2,2,2020),2024))

print(set_fecha_NUEVA((2,2,2020),4,6,2024))