#PRACTICA 2.1.

#EJERCICIO 11. Analice en forma completa el conjunto de datos 'chickwts' (paquete:datasets)

install.packages("datasets")  #Instalar paquetes
library(datasets) #Importarlos

# Chicken Weights by Feed Type
#An experiment was conducted to measure and compare the effectiveness of various feed supplements on the growth rate of chickens.

# Cargar el conjunto de datos
library(datasets)
data("chickwts")

# Ver las primeras filas
head(chickwts)

# Resumen general del dataset
summary(chickwts)

# ¿Cuántas observaciones hay por tipo de alimento?
table(chickwts$feed)

# Medidas de tendencia central y dispersión por tipo de alimento
aggregate(weight ~ feed, data = chickwts, 
          FUN = function(x) c(media = mean(x), sd = sd(x), mediana = median(x)))

# Histograma general de pesos
hist(chickwts$weight,
     main = "Distribución del peso de las gallinas",
     xlab = "Peso (gramos)",
     col = "olivedrab2",
     border = "white")

# Boxplot comparativo por tipo de alimento
boxplot(weight ~ feed, data = chickwts,
        main = "Boxplot: peso según tipo de alimento",
        xlab = "Tipo de alimento",
        ylab = "Peso (gramos)",
        col = "lightblue",
        las = 2) # Las=2 para que los nombres estén inclinados y se lean mejor


#El conjunto de datos chickwts contiene observaciones del peso (en gramos) de gallinas alimentadas con distintos suplementos. 
#El análisis descriptivo muestra que existen diferencias sustanciales en el peso según el tipo de alimento suministrado.
#Por ejemplo, el suplemento sunflower muestra valores medios y máximos superiores a los de horsebean, que tiene pesos más bajos. 
#El boxplot evidencia una mayor variabilidad en suplementos como casein y sunflower, mientras que otros 
#como linseed presentan menor dispersión.
#Esto sugiere que ciertos alimentos tienen un impacto más positivo en el crecimiento de las gallinas,
#tanto en promedio como en términos de variabilidad.

