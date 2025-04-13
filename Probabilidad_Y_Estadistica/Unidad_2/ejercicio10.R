#PRACTICA 2.1.

#EJERCICIO 10. Se realiza un estudio acerca de los efectos del tabaquismo sobre los patrones de sueño.
#La medición que se observa es el tiempo, en minutos, que toma quedar dormido.
#Se obtienen estos datos:

# Fumadores:
#   69.3 56.0 22.1 47.6
#   53.2 48.1 52.7 34.4
#   60.2 43.8 23.2 13.8

# No fumadores:
#   28.6 25.1 26.4 34.9
#   29.8 28.4 38.5 30.2
#   30.6 31.8 41.6 21.1
#   36.0 37.9 13.9

#a. Encuentre la media de la muestra para cada grupo.
#b. Encuentre la desviación estándar de la muestra para cada grupo.
#c. Usando un diagrama de caja comparativo grafique los conjuntos de datos fumadores vs. no fumadores.
#d. Comente qué clase de impacto parece tener el hecho de fumar sobre el tiempo que se requiere para quedarse dormido.


no_fumadores<-c(28.6,25.1,26.4,34.9,29.8, 28.4, 38.5, 30.2,30.6, 31.8, 41.6, 21.1,36.0, 37.9, 13.9)
fumadores<-c(69.3, 56.0, 22.1, 47.6,53.2, 48.1, 52.7, 34.4,60.2, 43.8, 23.2, 13.8)

media_n_f<-mean(no_fumadores)
media_n<-mean(fumadores)
cat("La media de los fumadores es: ",media_n," y la de los no fumadores:",media_n_f)

sd_n_f<-sd(no_fumadores)
sd_n<-sd(fumadores)
cat("La desviación estándar de los fumadores es: ",sd_n," y la de los no fumadores:",sd_n_f)

boxplot_n_f=boxplot(x=no_fumadores,col="lightskyblue")
boxplot_n=boxplot(x=fumadores,col="salmon")

grupo <- c(rep("Fumadores", length(fumadores)), rep("No Fumadores", length(no_fumadores)))
valores <- c(fumadores, no_fumadores)

boxplot(valores ~ grupo,
        col = c("salmon", "lightskyblue"),
        main = "Boxplot comparativo",
        xlab = "Grupo",
        ylab = "Tiempo (min) para quedarse dormido")

quantile(no_fumadores,c(0.5))
quantile(fumadores,c(0.5))

# Lo que podemos observar es un que los fumadores tandar mayor tiempo que los no fumadores en quedarse dormidos.
# El promedio de tiempo que tardan los no fumadores es de 30.2 min mientras que los fumadores 47.85 min (mediana), la desviación estandár también nos indica que los fumadores tienen datos más dispersos, algunos tardan mayor tiempo en dormirse que otros mientras que los no fumadores tienen tiempo más concentrados.
