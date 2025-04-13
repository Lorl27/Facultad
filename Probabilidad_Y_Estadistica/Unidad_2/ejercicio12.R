#P2.2
#12. Analice el conjunto de datos del archivo arbol.xlsx. (adjunto)

install.packages("ggplot2")
library(ggplot2)


arbol<- read_xlsx("arbol.xlsx")  #leer tabla de excel
head(arbol)
summary(arbol)


ggplot(arbol, aes(x = altura, fill = especie)) +
  geom_histogram(bins = 10, alpha = 0.7, position = "identity") +
  facet_wrap(~especie, scales = "free_y") +
  labs(title = "Histograma de alturas por especie",
       x = "Altura (m)",
       y = "Frecuencia") +
  theme_minimal()

boxplot(altura ~ especie, data = arbol,
        main = "Distribución de altura según especie",
        xlab = "Especie",
        ylab = "Altura (m)",
        col = rainbow(length(unique(arbol$especie))),
        las = 2)  # para girar las etiquetas del eje x

print("Del histograma y boxplot, podemos observar una gran diferencia de altura según ciertas especies, por ejemplo el Elicalipto tiene los datos más concentrados en 20-30m de altura , los demás están por debajo, sus meridianas rondan cerca de los 15m , a diferencia del Eucalptio que son cerca de los 25m.")

#RESUEMN ESTADISTICO X ESPECIE
aggregate(altura ~ especie, data = arbol, 
          FUN = function(x) c(media = mean(x), 
                              mediana = median(x), 
                              sd = sd(x), 
                              min = min(x), 
                              max = max(x)))

cat("Del análisis gráfico y numérico de las alturas por especie, se advierten diferencias sustanciales en la distribución de los datos. Particularmente, la especie Eucalipto presenta alturas notablemente superiores en comparación con las demás, concentrándose mayoritariamente en el rango de 20 a 30 metros, con una mediana cercana a los 25 m. En contraste, el resto de las especies exhibe medianas en torno a los 15 metros o menos, lo cual sugiere que, en condiciones similares, el Eucalipto alcanza un desarrollo vertical significativamente más pronunciado. Esta divergencia también se refleja en la dispersión de los datos, siendo mayor en el caso del Eucalipto, lo que indica una mayor variabilidad en su crecimiento.")
