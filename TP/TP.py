try:
    archivo = open("personas.txt", "r")
except FileNotFoundError:
    print("File not found")
else:
    mayores={}
    menores18={}
    menores10=[]
    generoInteresNinguno=[]

    for l in archivo:
        persona=l.split(", ")
            
        if int(persona[3])<11:
            menores10+=[(persona[0],persona[1],persona[3])]
            
        elif persona[5]=="ninguno\n":
            generoInteresNinguno+=[(persona[0],persona[1])]
            
        elif int(persona[3])<18:
            if persona[2] not in menores18.keys():
                menores18[persona[2]]=[(persona[0],persona[1],persona[4],persona[5])]
            else:
                menores18[persona[2]]+=[(persona[0],persona[1],persona[4],persona[5])]
                
        else:
            if persona[2] not in mayores.keys():
                mayores[persona[2]]=[(persona[0],persona[1],persona[4],persona[5])]
            else:
                mayores[persona[2]]+=[(persona[0],persona[1],persona[4],persona[5])]

    archivo.close()