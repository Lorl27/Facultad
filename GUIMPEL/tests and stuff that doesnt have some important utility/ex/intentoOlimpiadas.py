def grilla():
    cortes=int(input("Ingrese un numero de cortes: "))
    contador=0
    lista=[]
    while contador<=cortes:
        
        x=int(input("Ingrese su coordenada x: "))
        y=int(input("Ingrese su coordenada y: "))
        lista.append([x,y])
        print(lista)
        
        if contador>2 and y==lista[-2][1]:
            print("rango x, y.")
            rango_x=[]
            print(lista[-2][0])
            print(lista[-3][0])
            print(lista[-1][0])
            for coord_x in range(lista[-2][0],lista[-2][0]):
                rango_x.append(coord_x)
            print(rango_x)
        elif contador>2 and x==lista[-2][0]:
            print("rango y, x.")
        
        if [x,y]==lista[0] and contador>1:
            print("iguales")
            break
        
        contador+=1
        
grilla()        