# Practica 2, parte 1 
# EJERCICO NRO 9: Las edades de los sujetos sometidos a un estudio de reproducibilidad son las
#siguientes:
#   22 22 23 24 25 25 26 27 28 29 29 29 29 29 31 31 32 33 34 35 35
#   35 36 38 39 39 42 42 44 44 45 45 45 47 48 52 59 66 67 69 69
# a. Defina y clasifique la variable en estudio.
# b. Guarde los valores correspondientes a la variable edad en un vector.
# c. Ensaye comandos R a fin de obtener:
    # c1) Tamaño de la muestra.
    # c2) Media, mediana, moda y cuartiles.
    # c3) Rango, rango intercuartílico. Desviación estándar. Variancia.
    # c4) Percentil 10 y percentil 50.
    # c5) Mínimo y máximo y cuartiles, todos mediante un único comando.
    # c6) Diagrama de caja.
    # c7) Diagrama tallo-hoja.
    # c8) Histograma.
#d. Interprete los resultados obtenidos en el ítem c)

print("La variable edad es una variable de tipo cuantitativa discreta, medida en razón. Además de ser univariada")

edad_sujetos <- c(22,22,23,24,25,25,26,27,28,29,29,29,29,29,31,31,32,33,34,35,35,35,36,38,39,39,42,42,44,44,45,45,45,47,48,52,59,66,67,69,69)
print(edad_sujetos)

tamaño_muestra=length(edad_sujetos)
print("El tamaño de la muestra es: "); print(tamaño_muestra)

media<-mean(edad_sujetos)
mediana<-median(edad_sujetos)
moda<- as.numeric(names(sort(table(edad_sujetos), decreasing = TRUE)[1]))
Q1<- edad_sujetos[(tamaño_muestra+1) * 25/100] #quantile(edad_sujetos, probs=(0.25))
Q3<- edad_sujetos[(tamaño_muestra+1) * 75/100]

print("La media aritmetica es:"); print(media)
print("La mediana es:"); print(mediana)
print("El primer cuartil es:"); print(Q1)
print("El tercer cuartil es:"); print(Q3)
print("La moda es:"); print(moda)

minimo<- min(edad_sujetos)
maximo<- max(edad_sujetos)
rango<-(maximo - minimo)
RI<-(Q3-Q1) #IQR(edad_sujetos)
desviacion_estandar=sd(edad_sujetos)
variancia=var(edad_sujetos)

print("El rango es: "); print(rango)
print("El rango intercuartilico es: "); print(RI)
print("La desviación estandar es: "); print(desviacion_estandar)
print("La varianca es "); print(variancia)

percentil_10 <-  quantile(edad_sujetos, c(0.10));  
percentil_50 <- quantile(edad_sujetos, c(0.50));

print("El percentil 10 es:"); print(percentil_10)
print("El percentil 50 es:"); print(percentil_50)

max_min_cuartiles123<-quantile(edad_sujetos,probs=c(0,0.25,0.50,0.75,1)) #summary(edad_sujetos)


cat("El mínimo es", max_min_cuartiles123[1], 
    "| Q1:", max_min_cuartiles123[2], 
    "| Q2 (mediana):", max_min_cuartiles123[3], 
    "| Q3:", max_min_cuartiles123[4], 
    "| Máximo:", max_min_cuartiles123[5], "\n") 

bloxplot<- boxplot(x=edad_sujetos,col="purple")

tallo_hoja<-stem(edad_sujetos,scale=0.5)

png("histograma_edad.png") #Para guardarlo como imagen
histograma<- hist(x=edad_sujetos,main="Histograma de la edad",breaks=seq(20, 70, by = 5), xlab="Edad", ylab="Frecuencia", col="#7FFFD4")
abline(v = media, col = "red", lwd = 2)
abline(v = mediana, col = "blue", lwd = 2)
legend("topright", legend=c("Media", "Mediana"), col=c("red", "blue"), lwd=2) #Incorporar líneas de referencia al gráfico.

dev.off()


#Con todos los datos del item c, podemos afirmar que la mayoría de personas se encuentran en el rango etario de [20-35] , mostrado claramente por el histograma y boxplot.
#El rango intercuartílico (RI) indica que el 50% central de los datos está entre Q1 y Q3.
#No hay valores extremos visibles en el boxplot.
#El diagrama de tallo y hoja confirma la concentración de datos en la zona de los 20 y 30 años.
#La media y la mediana están cercanas, lo que sugiere una distribución simétrica o casi simétrica.
#La moda es 29 años, que aparece con más frecuencia.

