#Si escribimos tres números (inicio:fin:salto) en lugar de dos,
# el tercero se utiliza para determinar cada cuántas posiciones añadir un elemento a la lista.

l= [0,1,2,3,True,"hui"]
print(len(l)) #su largo

l[1:5:2] #[1,3]

#[expresión for variables in iterable if condición]
l1=[0,2,4]
[3*x for x in l1] # [0,6,12]

#Si pasamos tres parámetros, el tercero indica el step,
# la diferencia entre los números que se vayan generando en la secuencia.

for i in range(1,10,2):#inicio, final-1, salto
    print(i)