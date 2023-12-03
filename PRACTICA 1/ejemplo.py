
a = "3"

if type(a) is int:
    print(f"{a} es entero")

if isinstance(a,(int,float,str)) == True:
    print(f"{a} es numero o cadena")

