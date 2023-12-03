import os
ruta=os.path.dirname(os.path.abspath(__file__))

def rut(txt):
    archivo=open(ruta+txt,"r")


    archivo.close()


rut("\\archivos\\lineasRandom.txt")