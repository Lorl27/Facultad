// =========================================================================
//                  LIBRERÍA DE MÍNIMOS CUADRADOS 
// =========================================================================

//1. Método de Eliminación Gaussiana con pivoteo parcial
function [x,a] = gausselimPP(A,b)
[nA,mA] = size(A);
[nb,mb] = size(b);
a = [A b];
n = nA;

for k=1:n-1
    kpivot = k; amax = abs(a(k,k));
    for i=k+1:n
        if abs(a(i,k))>amax then
            kpivot = i; amax = a(i,k);
        end
    end
    temp = a(kpivot,:); a(kpivot,:) = a(k,:);
    a(k,:) = temp;
    
    for i=k+1:n
        for j=k+1:n+1
            a(i,j) = a(i,j) - a(k,j)*a(i,k)/a(k,k);
        end
        for j=1:k
            a(i,j) = 0;
        end
    end
end

x(n) = a(n,n+1)/a(n,n);

for i = n-1:-1:1
    sumk = 0;
    for k=i+1:n
        sumk = sumk + a(i,k)*x(k);
    end
    x(i) = (a(i,n+1)-sumk)/a(i,i);
end
endfunction


//2. Constructor de Matriz de Vandermonde A
// Crea columnas [1, x, x^2, ... x^n]
// n: grado del polinomio: p=[1,...,x^(grado)]
function A = ConstruirVandermonde(x, n)
    m = length(x);
    A = ones(m, 1);
    for j = 1:n
        A = [A, (x').^j];
    end
endfunction


// 3. Aproximación polinomial de mínimos cuadrados para matrices con rango completo
function [p, err, coefs]=MinCuad_poly(x, y, grado)
    // Construir sistema A
    A = ConstruirVandermonde(x, grado);
    b = y'; // Transpuesta para que sea vector columna
    
    // Resolver Sistema Normal: (A' * A) * x = (A' * b)
    MatrizNormal = A' * A;
    VectorIndep  = A' * b;
    
    [coefs, dump] = gausselimPP(MatrizNormal, VectorIndep);
    
    // Crear objeto polinomio
    p = poly(coefs, "x", "coeff");
    
    // Calcular Error (Norma 2 del residuo)
    y_aprox = horner(p, x);
    err = norm(y - y_aprox); 
endfunction


// correciones para ej 3 - si tira erorr usar estas:
// 3. Aproximación polinomial (VERSIÓN ROBUSTA)
function [p, err, coefs]=MinCuad_poly2(x, y, grado)
    // Aseguramos que x e y sean columnas para evitar conflictos
    x_col = x(:); 
    y_col = y(:);
    
    // Construir sistema A
    A = ConstruirVandermonde2(x_col, grado);
    b = y_col; // Ya lo forzamos a columna arriba, no hace falta transponer
    
    // Resolver Sistema Normal: (A' * A) * x = (A' * b)
    MatrizNormal = A' * A;
    VectorIndep  = A' * b;
    
    [coefs, dump] = gausselimPP(MatrizNormal, VectorIndep);
    
    // Crear objeto polinomio
    p = poly(coefs, "x", "coeff");
    
    // Calcular Error (Norma 2 del residuo)
    y_aprox = horner(p, x_col);
    err = norm(y_col - y_aprox); 
endfunction

// 2. Constructor de Matriz de Vandermonde A (VERSIÓN ROBUSTA)
function A=ConstruirVandermonde2(x, n)
    x_col = x(:); // <--- Forzamos a que sea vector columna siempre
    m = length(x_col);
    A = ones(m, 1);
    for j = 1:n
        // Como x_col ya es columna, NO lo transponemos aquí
        A = [A, (x_col).^j]; 
    end
endfunction

//---------------------------------------------------------------------------

// ==========================================
//  RESOLUCIÓN DEL EJERCICIO 7 - 9
// ==========================================

function run_ejercicio_Generico()
    clc;
    mprintf("\n=== EJERCICIO GENÉRICO (Tipo Ej 7 y 8) ===\n");
    mprintf("Use este script para: Cualquier tabla X vs Y simple.\n");
    mprintf("Calcula polinomios de grados 1, 2 y 3 y dice cuál es el mejor.\n");

    // ************************************************************
    // ************ ZONA DE DATOS (MODIFICAR AQUÍ)  **************
    // ************************************************************
    
    // Datos Ejercicio 7 (Ejemplo por defecto)
    // x_datos = [0, 0.15, 0.31, 0.5, 0.6, 0.75];
    // y_datos = [1, 1.004, 1.031, 1.117, 1.223, 1.422];
    
    // Datos Ejercicio 8 (Descomenta para usar)
     x_datos = [4, 4.2, 4.5, 4.7, 5.1, 5.5, 5.9, 6.3, 6.8, 7.1];
     y_datos = [102.56, 113.18, 130.11, 142.05, 167.53, 195.14, 224.87, 256.73, 299.5, 326.72];

    // ************************************************************
    // ***************** FIN ZONA DE DATOS ************************
    // ************************************************************

    grados = [1, 2, 3];
    errores = [];
    polinomios = list();
    
    xx = linspace(min(x_datos), max(x_datos), 200);
    scf(0); clf();
    plot(x_datos, y_datos, "ko", "MarkerSize", 4);  
    colores = ["r-", "g--", "b-."];
    
    for i=1:3
        g = grados(i);
        [p, err,coefs] = MinCuad_poly(x_datos, y_datos, g);
        errores(i) = err;
        polinomios(i) = p;
        mprintf("\nGrado %d: Error = %.5f\nPolinomio: ", g, err); disp(p);
        plot(xx, horner(p, xx), colores(i)); //plot(xx, yy3, 'b-.', 'thickness', 2); // Grado 3
    end
    legend(["Datos"; "Grado 1"; "Grado 2"; "Grado 3"]);
    title("Ajuste Polinomial Genérico");
    
    [min_e, idx] = min(errores);
    mprintf("\n>> MEJOR AJUSTE MATEMÁTICO: Grado %d (Menor error: %.5f)\n", grados(idx), min_e);
endfunction
        
// ==========================================
//  RESOLUCIÓN DEL EJERCICIO 3
// ==========================================
        
function run_ejercicio_3_PreciosPan()
    clc;
    mprintf("\n=== EJERCICIO 3: Evolución de Precios (Comparativa Años) ===\n");
    mprintf("Use este script si piden: Comparar ajustes (lineal, cuad, cub) de dos años distintos.\n");
    
    
    // ************************************************************
    // ************ ZONA DE DATOS (MODIFICAR AQUÍ)  **************
    // ************************************************************
    
    // Variable Independiente (Meses)
    x = (1:12)';  //forzamos a que sea columna para evitar errores! 
    
    // Variable Dependiente (Precios AÑO 1)
    y_anio1 = [145.61, 151.12, 157.27, 164.72, 172.29, 182.91, 185.12, 188.62, 190.09, 197.99, 204.32, 207.97];
              
    // Variable Dependiente (Precios AÑO 2)
    y_anio2 = [209.92, 225.82, 265.71, 295.24, 301.62, 311.80, 327.39, 343.10, 366.54, 385.20, 407.77, 428.42];
               
    grados = [1, 2, 3]; // Grados a probar
    
    // ************************************************************
    // ***************** FIN ZONA DE DATOS ************************
    // ************************************************************

    titulos = ["Lineal", "Cuadrático", "Cúbico"];
    
    // --- ANÁLISIS AÑO 1 ---
    mprintf("\n--- RESULTADOS AÑO 1 ---\n");
    polys_1 =list(); //para guardar polinomios
    errs_1 = [];
    for i=1:3
        g = grados(i);
        [p, err,c] = MinCuad_poly2(x, y_anio1, g);
        polys_1(i) = p;
        errs_1(i) = err;
        mprintf("Grado %d (%s): Error = %.4f\n", g, titulos(i), err);
        mprintf("   P(x) = "); disp(p);
    end
    
    // --- ANÁLISIS AÑO 2 ---
    mprintf("\n--- RESULTADOS AÑO 2 ---\n");
    polys_2 = list(); errs_2 = [];
    for i=1:3
        g = grados(i);
        [p, err,c] = MinCuad_poly2(x, y_anio2, g);
        polys_2(i) = p;
        errs_2(i) = err;
        mprintf("Grado %d (%s): Error = %.4f\n", g, titulos(i), err);
        mprintf("   P(x) = "); disp(p);
    end

    // GRAFICACIÓN
    xx = linspace(min(x), max(x), 200); // Vector suave para las curvas
    scf(1); clf(); f=gcf(); f.figure_size=[1000,500];
    
    subplot(1,2,1); // Año 1
    plot(x, y_anio1, "k.", "MarkerSize", 15); //datos reales 
    plot(xx, horner(polys_1(1), xx), "r-", "Thickness", 2);  //lineal
    plot(xx, horner(polys_1(2), xx), "g--", "Thickness", 2); //cuadrática
    plot(xx, horner(polys_1(3), xx), "b-.", "Thickness", 2); //cúbica
    title("Año 1 (Precios)", "fontsize", 3);
    legend(["Datos"; "Lineal"; "Cuadrático"; "Cúbico"], 2); xlabel("Mes"); ylabel("Precio ($)");  xgrid();
    
    subplot(1,2,2); // Año 2
    plot(x, y_anio2, "k.", "MarkerSize", 15);
    plot(xx, horner(polys_2(1), xx), "r-", "Thickness", 2);
    plot(xx, horner(polys_2(2), xx), "g--", "Thickness", 2);
    plot(xx, horner(polys_2(3), xx), "b-.", "Thickness", 2);
    title("Año 2 (Precios)", "fontsize", 3);legend(["Datos"; "Lineal"; "Cuadrático"; "Cúbico"], 2); xlabel("Mes"); ylabel("Precio ($)");  xgrid();
    
    mprintf("\n[CONCLUSIÓN AUTOMÁTICA]\n");
    mprintf("Compara las curvas rojas (lineal) y verdes (cuadrática).\n");
    mprintf("Si la verde se curva mucho y reduce el error, hay aceleración (convexidad).\n");
    
     mprintf("\n=== CONCLUSIONES (Items c y d) ===\n");
    
    // Análisis 2021
    diff_err_1 = errs_1(1) - errs_1(2); // Mejora de lineal a cuadrática
    mprintf("\n>> SOBRE 2021:\n");
    if diff_err_1 < 2 then // Umbral arbitrario de mejora pequeña
        mprintf("   El modelo LINEAL es suficiente. La mejora al usar cuadrática es despreciable.\n");
        mprintf("   Comportamiento: Crecimiento constante (inflación inercial).\n");
    else
        mprintf("   El modelo cuadrático ajusta mejor.\n");
    end
    
    // Análisis 2022
    diff_err_2 = errs_2(1) - errs_2(2);
    mprintf("\n>> SOBRE 2022:\n");
    if diff_err_2 > 5 then
        mprintf("   El modelo LINEAL tiene mucho error comparado con el cuadrático/cúbico.\n");
        mprintf("   Se recomienda el modelo CUADRÁTICO.\n");
        mprintf("   Comportamiento: Aceleración de precios (Convexidad notoria).\n");
    else
        mprintf("el lineal/cubico va bien")
    end
    
    mprintf("\n>> CONCLUSIÓN GENERAL (d):\n");
    mprintf("   En 2021 el precio subió de forma estable (aprox $5.6 por mes).\n");
    mprintf("   En 2022 hubo una aceleración inflacionaria fuerte (curva convexa).\n");
    mprintf("   El precio NO sigue una tendencia lineal a largo plazo, se acelera.\n");
    
    mprintf("CONCLUCIONES TEORICAS:\n")
    mprintf("c) ¿Qué aproximación se ajusta más?Año 2021:\n Observarás que la línea roja (Lineal) pasa muy cerca de todos los puntos. Aunque el polinomio cúbico siempre tendrá matemáticamente menos error, visualmente la tendencia es Lineal. \n Usar un cúbico sería sobreajustar (overfitting).Año 2022: Observarás que la línea roja queda muy mal (los datos hacen una panza hacia arriba).\n  La curva verde (Cuadrática) se ajusta casi perfecto a esa aceleración\n")
    mprintf("d) ¿Qué conclusión se infiere?\n La dinámica de precios cambió de un año al otro.En 2021, la inflación del pan fue constante (la pendiente es la misma todo el año).\n En 2022, hubo una aceleración del precio (la pendiente aumenta mes a mes, por eso se necesita un término $x^2$ positivo). Esto indica un empeoramiento de las condiciones económicas respecto a la inflación del producto");
endfunction





// =========================================================================
//                       RESOLUCIÓN EJERCICIO 4
// =========================================================================

function run_ejercicio_4_Temperaturas()
    clc;
    mprintf("\n=== EJERCICIO 4: Temperaturas (Vandermonde vs QR) ===\n");
    mprintf("Use este script si piden: Comparar estabilidad numérica (Ecuaciones Normales vs QR).\n");
    mprintf("Clave: Ver cómo falla el grado alto con Ecs Normales.\n");
    
     mprintf("\n============================================================\n");
    mprintf("   ENUNCIADO - Aproximación por Mínimos Cuadrados\n");
    mprintf("============================================================\n\n");

    mprintf("Consideremos la siguiente tabla que muestra el promedio mensual\n");
    mprintf("de la temperatura (°C) mínima y máxima en la ciudad de Rosario\n");
    mprintf("durante el año 2022.\n\n");

    mprintf("Mes:   Ene22  Feb22  Mar22  Abr22  May22  Jun22  Jul22  Ago22  Sep22  Oct22\n");
    mprintf("Max.:  32.9   30.8   26.4   24.2   19.2   16.5   19.3   21.0   23.0   26.2\n");
    mprintf("Min.:  19.5   15.5   13.1    9.8    5.7    2.2    5.3    4.7    6.0   10.5\n\n");

    mprintf("Sea p_n(x) el polinomio de aproximación de mínimos cuadrados de grado\n");
    mprintf("menor o igual a n que se obtiene de tomar para x1 = 1 el valor promedio\n");
    mprintf("de temperatura máxima en Ene22, para x2 = 2 el valor de la máxima en Feb22, etc.\n");
    mprintf("Dicho polinomio se puede obtener como solución del problema de mínimos cuadrados:\n\n");
    mprintf("      A^T A x = A^T b\n\n");

    mprintf("donde A =\n");
    mprintf("[ 1  x1  x1^2  ...  x1^n ]\n");
    mprintf("[ 1  x2  x2^2  ...  x2^n ]\n");
    mprintf("[  .   .    .        .   ]\n");
    mprintf("[ 1 x10 x10^2 ... x10^n ]\n\n");

    mprintf("------------------------------------------------------------\n");
    mprintf("a) Obtenga los polinomios de aproximación de mínimos cuadrados\n");
    mprintf("   p3(x), p5(x), p7(x) y p9(x) invirtiendo la matriz A^T A\n");
    mprintf("   utilizando la función inv de Scilab. Grafique en el mismo\n");
    mprintf("   gráfico los 4 polinomios obtenidos usando un espaciado de 0.1.\n");
    mprintf("   En el mismo gráfico grafique los puntos de la tabla.\n\n");

    mprintf("b) Obtenga los polinomios de aproximación de mínimos cuadrados\n");
    mprintf("   p3(x), p5(x), p7(x) y p9(x) aplicando la factorización QR.\n");
    mprintf("   Obtenga la solución invirtiendo la matriz R usando inv.\n");
    mprintf("   Grafique en un nuevo gráfico los 4 polinomios obtenidos\n");
    mprintf("   junto con los puntos de la tabla.\n\n");

    mprintf("c) Explique cualquier discrepancia observada en los polinomios\n");
    mprintf("   obtenidos en los ítems a) y b). ¿Tuvo alguna dificultad en\n");
    mprintf("   obtener las soluciones de mínimos cuadrados por alguno de\n");
    mprintf("   los métodos?\n\n");

    mprintf("d) ¿Cuál de los cuatro polinomios emplearía para aproximar los\n");
    mprintf("   datos? Justifique.\n");
    mprintf("============================================================\n\n");
    //Está diseñado intencionalmente para mostrarte por qué nunca debes resolver Mínimos Cuadrados invirtiendo la matriz normal ($A^T A$) cuando el grado es alto.El problema tiene una "trampa" numérica: La matriz de Vandermonde se vuelve mal condicionada (casi singular) muy rápido. Verás que el método A fallará estrepitosamente en grado 9, mientras que el método B (QR) sobrevivirá. 
    
    // ************************************************************
    // ************ ZONA DE DATOS (MODIFICAR AQUÍ)  **************
    // ************************************************************
    
    // Variable X (Meses)
    x_meses = 1:10;  //enero a octubre
    
    // Variable Y (Temperaturas Máximas)
    y_max = [32.9, 30.8, 26.4, 24.2, 19.2, 16.5, 19.3, 21.0, 23.0, 26.2];
    
    grados = [3, 5, 7, 9]; // Grados a testear
    
    // ************************************************************
    // ***************** FIN ZONA DE DATOS ************************
    // ************************************************************

    colores = ["r-", "g-", "b-", "m-"];  //rojo verde azul magenta
    xx = linspace(min(x_meses), max(x_meses), 200);     // Vector denso para graficar suavemente
    
    // =========================================================
    // INCISO A: MÉTODO DE ECUACIONES NORMALES (Invertir A'A)
    // Solución: x = inv(A'A) * A'b
    // =========================================================
    scf(0); clf();
    plot(x_meses, y_max, "k.", "MarkerSize", 15);
    title("Método A: Ecuaciones Normales (FALLA en grado alto)", "fontsize", 3);    xlabel("Mes"); ylabel("Temp Max");
    leyendas = ["Datos"];
    
    mprintf("\n--- MÉTODO A: Ecuaciones Normales ---\n");
    for i = 1:length(grados)
        n = grados(i);
        A = ConstruirVandermonde(x_meses, n); // 1. Construir A
        MatrizNormal = A' * A;         // 2. Resolver: coefs = inv(A'*A) * (A'*y)
         VectorIndep  = A' * y_max';
         
        // Check de condicionamiento
        if cond(MatrizNormal) > 1e12 then
            mprintf("! ADVERTENCIA Grado %d: Matriz mal condicionada (Cond > 1e12)\n", n);
        end
        
        coefs = inv(MatrizNormal) * VectorIndep;      // Scilab lanzará un warning en grado 9 probablemente
        P = poly(coefs, "x", "coeff");  // 3. Crear Polinomio y Graficar
        plot(xx, horner(P, xx), colores(i), "Thickness", 2);
        leyendas = [leyendas; "Grado " + string(n)];
    end
    legend(leyendas, 4); xgrid();// 4 = abajo derecha
    
   // =========================================================
    // INCISO B: MÉTODO FACTORIZACIÓN QR
    // A = Q*R  =>  R*x = Q'*b  => x = inv(R) * (Q'*b)
    // =========================================================
    mprintf("\n--- MÉTODO B: Factorización QR ---\n");
    scf(1); clf();
    plot(x_meses, y_max, "k.", "MarkerSize", 15);
    title("Método B: Factorización QR (ESTABLE)", "fontsize", 3); xlabel("Mes"); ylabel("Temp Max");
    leyendas = ["Datos"];
    
    mprintf("\n--- MÉTODO B: Factorización QR ---\n");
    for i = 1:length(grados)
        n = grados(i);
        A = ConstruirVandermonde(x_meses, n);
        
         // 2. Factorización QR
        // "e" significa "economy size" (R cuadrada) para sistemas sobredeterminados
        [Q, R] = qr(A, "e"); 
        
         // 3. Resolver: x = inv(R) * (Q' * y)
        // Nota: Q' * y proyecta b sobre el espacio columna
        coefs = inv(R) * (Q' * y_max');
        
        P = poly(coefs, "x", "coeff");
        plot(xx, horner(P, xx), colores(i), "Thickness", 2);
        leyendas = [leyendas; "Grado " + string(n)];
    end
    legend(leyendas, 4); xgrid();
    
     mprintf("c) Explicación de las discrepancias y dificultades\n\nObservación Visual:\nEn el gráfico del Método A (Ventana 0), verás que el polinomio de grado 9 (y quizás el de 7) se comporta de forma errática, vibra demasiado o desaparece de la escala.\n Es una basura numérica.En el gráfico del Método B (Ventana 1), el polinomio de grado 9, aunque oscila (Fenómeno de Runge), sigue pasando por los puntos.\n\nJustificación Técnica (La clave):\nLa matriz de Vandermonde ($A$) es inherentemente mal condicionada.\n\nMétodo A (Ecuaciones Normales): \nAl calcular $A^T A$, estás elevando al cuadrado el número de condición.Si el número de condición de $A$ es $10^7$, el de $A^T A$ será $10^{14}$.La precisión de máquina (double precision) tiene unos 16 dígitos significativos.\n Si el número de condición se acerca a $10^{16}$, la matriz se vuelve computacionalmente singular.Al intentar hacer inv(At*A), el error de redondeo se magnifica tanto que la solución pierde sentido.\n\nMétodo B (QR): \nEste método trabaja directamente con $A$ (descompuesta en $Q$ y $R$).El número de condición relevante es el de $R$, que es igual al de $A$ (no al cuadrado).Por eso QR es mucho más estable numéricamente y logra resolver el sistema donde el Método A falla\n\n\n.d) ¿Cuál polinomio emplearía?\nRespuesta: Emplearía el de Grado 3 (Cúbico) o como mucho Grado 5.Justificación:Tendencia Física: La temperatura anual sigue un ciclo estacional suave (baja en invierno, sube en verano), similar a una parábola o una función trigonométrica suave.\n\nSobreajuste (Overfitting):Los polinomios de grado 7 y 9 intentan pasar por cada pequeña variación de los datos (ruido). Esto genera oscilaciones violentas entre los meses (Fenómeno de Runge).\nSi usas el de grado 9 para predecir la temperatura en el día 15 de un mes (ej: $x=5.5$), te dará un valor absurdo (muy alto o muy bajo) debido a estas oscilaciones.Principio de Parsimonia: El modelo más simple que explique bien los datos suele ser el mejor. \n\nEl grado 3 captura la U del invierno perfectamente sin inventar oscilaciones que no existen\n");
    
endfunction

// =========================================================================
//                       RESOLUCIÓN EJERCICIO 5
// =========================================================================

function run_ejercicio_5_Gompertz()
    clc;
    mprintf("\n=== EJERCICIO 5: Modelo Gompertz (Epidemia) ===\n");
    

    mprintf("Use este script si piden: Ajustar g(t) = th1 * exp(-th2 * exp(-th3 * t)).\n");
    mprintf("Método: Linealización doble logaritmo.\n");
    
     mprintf("\n============================================================\n");
    mprintf("   ENUNCIADO - Ejercicio 5\n");
    mprintf("============================================================\n\n");

    mprintf("5) La siguiente tabla presenta el número de casos diarios de gripe\n");
    mprintf("   en una determinada localidad. En el estudio de epidemias, el\n");
    mprintf("   siguiente modelo básico describe el crecimiento:\n\n");

    mprintf("   Día   Casos\n");
    mprintf("    0     35\n");
    mprintf("    1     23\n");
    mprintf("    2     47\n");
    mprintf("    3     59\n");
    mprintf("    4     82\n");
    mprintf("    5    113\n");
    mprintf("    6    143\n");
    mprintf("    7    179\n");
    mprintf("    8    233\n");
    mprintf("    9    269\n");
    mprintf("   10    303\n");
    mprintf("   11    335\n");
    mprintf("   12    371\n");
    mprintf("   13    404\n");
    mprintf("   14    434\n");
    mprintf("   15    446\n");
    mprintf("   16    457\n");
    mprintf("   17    470\n");
    mprintf("   18    481\n");
    mprintf("   19    482\n");
    mprintf("   20    476\n");
    mprintf("   21    465\n");
    mprintf("   22    454\n");
    mprintf("   23    436\n");
    mprintf("   24    424\n");
    mprintf("   25    397\n");
    mprintf("   26    385\n");
    mprintf("   27    359\n");
    mprintf("   28    340\n");
    mprintf("   29    322\n");
    mprintf("   30    303\n\n");

    mprintf("   Modelo del número total de infectados hasta un instante t:\n");
    mprintf("       g(t) = θ1 * exp(-θ2 * exp(-θ3 * t))\n\n");
    mprintf("   Fijando θ1 = 13129.3, se desea ajustar por mínimos cuadrados\n");
    mprintf("   los parámetros θ2 y θ3 a partir de los datos de la tabla.\n");
    mprintf("   En la misma figura, graficar los casos totales en función del\n");
    mprintf("   tiempo y la función g(t) obtenida por mínimos cuadrados.\n\n");

   
    mprintf("============================================================\n\n");
    
     mprintf("\n============================================================\n");
    mprintf("   LINEALIZACIÓN DEL MODELO DE GOMPERTZ\n");
    mprintf("============================================================\n\n");
    
    disp(" se debe  linealizar porque el moidelo de creciimiento de fompertz no es lineal y no se puede aplicar miniomso cuadrados directamente . entonces para linealizar la ecuacion, hay que apligar logaritmo 2 veces")
    mprintf("Modelo original:\n");
    mprintf("   $y = \\theta_{1} \\cdot e^{-\\theta_{2} e^{-\\theta_{3} t}}$\n\n");

    mprintf("Paso 1: Pasamos $\\theta_{1}$ dividiendo:\n");
    mprintf("   $\\dfrac{y}{\\theta_{1}} = e^{-\\theta_{2} e^{-\\theta_{3} t}}$\n\n");

    mprintf("Paso 2: Aplicamos logaritmo natural:\n");
    mprintf("   $\\ln\\!\\left(\\dfrac{y}{\\theta_{1}}\\right) = -\\theta_{2} e^{-\\theta_{3} t}$\n\n");

    mprintf("Paso 3: Multiplicamos por $-1$ y aplicamos logaritmo de nuevo:\n");
    mprintf("   $\\ln\\!\\left(-\\ln\\!\\left(\\dfrac{y}{\\theta_{1}}\\right)\\right) = \\ln(\\theta_{2} e^{-\\theta_{3} t})$\n");
    mprintf("   $\\ln\\!\\left(-\\ln\\!\\left(\\dfrac{y}{\\theta_{1}}\\right)\\right) = \\ln(\\theta_{2}) - \\theta_{3} t$\n\n");

    mprintf("¡Ahora es una recta!\n\n");

    mprintf("Variable transformada:\n");
    mprintf("   $Z = \\ln\\!\\left(-\\ln\\!\\left(\\dfrac{y}{\\theta_{1}}\\right)\\right)$\n\n");

    mprintf("Variable independiente:\n");
    mprintf("   $X = t$\n\n");

    mprintf("Ordenada al origen:\n");
    mprintf("   $a_{0} = \\ln(\\theta_{2}) \\;\\Rightarrow\\; \\theta_{2} = e^{a_{0}}$\n\n");

    mprintf("Pendiente:\n");
    mprintf("   $a_{1} = -\\theta_{3} \\;\\Rightarrow\\; \\theta_{3} = -a_{1}$\n");
    mprintf("============================================================\n\n");

    // ************************************************************
    // ************ ZONA DE DATOS (MODIFICAR AQUÍ)  **************
    // ************************************************************
    
    // Tiempo t
    t = (0:30)';   //dias del 0 al  30 - vector columna
    
    // Casos y (debe ser vector columna)
    y = [35; 23; 47; 59; 82; 113; 143; 179; 233; 269; 303; ...
         335; 371; 404; 434; 446; 457; 470; 481; 482; 476; ...
         465; 454; 436; 424; 397; 385; 359; 340; 322; 303];
         
    // Parámetro FIJO dado por enunciado
    theta1 = 13129.3; 
    
    // ************************************************************
    // ***************** FIN ZONA DE DATOS ************************
    // ************************************************************

    // 2. LINEALIZACIÓN DE LOS DATOS
    // Ecuación linealizada: ln( -ln(y/theta1) ) = ln(theta2) - theta3 * t
    // Forma: Z = A0 + A1 * t
    
    // Transformamos las Y en Z
    // Nota: y/theta1 siempre es < 1, por lo que su ln es negativo.
    // Al ponerle el menos adelante, se hace positivo y podemos aplicar ln de nuevo.
    

    Z = log( -log(y ./ theta1) );     // Linealización: ln(-ln(y/th1)) = ln(th2) - th3*t
    
    
    // 3. AJUSTE POR MÍNIMOS CUADRADOS (RECTA)
    // Construimos matriz Vandermonde para recta: [1, t]
    
    // Ajuste lineal Z = A0 + A1*t
    A = [ones(length(t),1), t];    
    
     // Resolvemos sistema normal (A'A)x = A'Z
    // coefs(1) será A0, coefs(2) será A1
    coefs = (A' * A) \ (A' * Z); 
    
    A0 = coefs(1);
    A1 = coefs(2);
    
    mprintf("\n--- Ajuste Linealizado ---\n");
    mprintf("Pendiente (A1): %.5f\n", A1);
    mprintf("Ordenada  (A0): %.5f\n", A0);
    
    // 4. RECUPERAR PARÁMETROS ORIGINALES (THETA 2 y 3)
    // A0 = ln(theta2)  => theta2 = exp(A0)
    // A1 = -theta3     => theta3 = -A1
    
    // Recuperar parámetros
    theta2 = exp(A0);
    theta3 = -A1;
    
    mprintf("\nRESULTADOS:\nTheta1 (Fijo) = %.1f\nTheta2 = %.5f\nTheta3 = %.5f\n", theta1, theta2, theta3);
    
    // Graficar - Definimos la función del modelo con los parms encontrados
    function casos = g(tiempo)
        casos = theta1 * exp( -theta2 * exp(-theta3 * tiempo) );
    endfunction

    
    tt = linspace(min(t), max(t), 200);     // Vector suave para la curva
    
    scf(0); clf();
    plot(t, y, "ro", "MarkerSize", 6, "MarkerFaceColor", "red");    // Graficar puntos originales
    plot(tt, g(tt), "b-", "Thickness", 2);  ///modelo ajustado
    title("Ajuste Gompertz", "fontsize", 3); legend(["Datos Reales"; "Modelo g(t) Ajustado"], 2);
    xlabel("Día (t)");
    ylabel("Casos Totales"); xgrid();
    
     mprintf("\nGráfica generada.\n");
    mprintf("Observación: La curva azul debería suavizar la tendencia de los puntos rojos.\n");

endfunction

    

// =========================================================================
//                  EJERCICIO 6: Regresión Multivariable (3D)
// =========================================================================

function run_ejercicio_6_Multivariable()
    clc;
    mprintf("\n=== EJERCICIO 6: Regresión Multivariable 3D ===\n");
    mprintf("Use este script si piden: Ajustar f(x,v) = a + bx + cv (Plano).\n");
    
    mprintf("\n============================================================\n");
    mprintf("   ENUNCIADO - Ejercicio 6\n");
    mprintf("============================================================\n\n");

    mprintf("6) La regresión lineal de mínimos cuadrados se puede extender a\n");
    mprintf("   datos que dependen de dos o más variables (regresión lineal\n");
    mprintf("   multivariable). Si la variable dependiente es y y las variables\n");
    mprintf("   independientes son x y v, los datos se pueden aproximar mediante\n");
    mprintf("   una función de la forma:\n\n");

    mprintf("       $f(x, v) = a + b x + c v$\n\n");

    mprintf("a) Para este caso, exprese en forma vectorial el sistema de ecuaciones\n");
    mprintf("   a resolver para hallar la solución de mínimos cuadrados.\n\n");

    mprintf("b) Obtenga la aproximación lineal de mínimos cuadrados que ajusta el\n");
    mprintf("   siguiente conjunto de datos:\n\n");

    mprintf("   x   v    y\n");
    mprintf("   0   0   1.42\n");
    mprintf("   0   1   1.85\n");
    mprintf("   1   0   0.78\n");
    mprintf("   2   0   0.18\n");
    mprintf("   2   1   0.60\n");
    mprintf("   2   2   1.05\n\n");

    mprintf("c) Grafique los datos en 3D utilizando la función scatter3 de Scilab.\n");
    mprintf("   Utilizando el comando:\n");
    mprintf("       set(gca(), auto_clear, off)\n");
    mprintf("   grafique en el mismo gráfico el plano $f(x, v) = a + b x + c v$\n");
    mprintf("   obtenido por mínimos cuadrados, utilizando la función plot3d.\n");
    mprintf("============================================================\n\n");
    
     mprintf("pasamos de  ajustar una linea en 2d, a un plano en 3d")
       disp(" queremos austar el podelo y=a*1+b*x+c*v");
       disp("tenemos n datos, sistema sobredeterminado Au=b, construido con");
       disp(" vector de incognitas u: con coef que buscamos, u=[a,b,c]t]")
       disp("vector de datos dependientes y: y=[y1....yn]t");
       disp("matriz de diseño A: la 1ra col son 1 (t.indep) , la 2da datos de x y al tercera,da os de v");
       disp("A=[ 1 x1 v1 ; 1 x2 v2 ; ... ; 1 xn vn]");
       disp("luego se debe resolver el sistrma por minimos cuadrados como : (AtA)u=Aty");
    
    // ************************************************************
    // ************ ZONA DE DATOS (MODIFICAR AQUÍ)  **************
    // ************************************************************
    
    // Vectores COLUMNA
    x = [0; 0; 1; 2; 2; 2];
    v = [0; 1; 0; 0; 1; 2];
    y = [1.42; 1.85; 0.78; 0.18; 0.60; 1.05];
    
    // ************************************************************
    // ***************** FIN ZONA DE DATOS ************************
    // ************************************************************

    // Matriz de Diseño A = [1, x, v]
    A = [ones(length(x),1), x, v];
    
    // 3. RESOLVER SISTEMA DE MÍNIMOS CUADRADOS
    // Ecuación normal: (A'A)*u = A'y
    // Scilab resuelve esto eficientemente con el operador \ (backslash)
    // O explícitamente: u = inv(A'*A) * (A'*y)
    
    // Resolver (A'A)u = A'y
    u = (A' * A) \ (A' * y);
    
    mprintf("\n--- Resultados del Ajuste ---\n");
    mprintf("Coeficiente a (Indep): %.4f\n", u(1));
    mprintf("Coeficiente b (Pend x): %.4f\n", u(2));
    mprintf("Coeficiente c (Pend v): %.4f\n", u(3));
    mprintf("\nMODELO: f(x,v) = %.4f + (%.4f)x + (%.4f)v\n", u(1), u(2), u(3));
    
    // Gráfico 3D
    scf(0); clf(); f=gcf(); f.color_map=jetcolormap(64);  //colores bonitoss.
    param3d(x, v, y); // Usamos param3d para poner los puntos en el espacio
    
    
    // Configurar estética de los puntos
    h_puntos = gce(); 
    h_puntos.mark_mode = "on";       // Activar marcas
    h_puntos.mark_style = 9;         // Estilo círculo relleno (varía según versión)
    h_puntos.mark_size_unit = "point";
    h_puntos.mark_size = 4;
    h_puntos.mark_foreground = 5;    // Color rojo (en colormap default)
    h_puntos.line_mode = "off";      // Sin líneas uniendo puntos
    
    // Plano
    x_g = linspace(min(x), max(x), 10);
    v_g = linspace(min(v), max(v), 10);
    
    // Calculamos Z para cada par (x,v)
    // Scilab plot3d espera vectores x, y y una matriz Z
    Z = zeros((length(x_g), length(v_g)));
    
    for i=1:10, for j=1:length(v_g), Z(i,j) = u(1) + u(2)*x_g(i) + u(3)*v_g(j); end, end             // Evaluamos el modelo: a + bx + cv
    
    set(gca(), "auto_clear", "off");     // Comando solicitado para superponer gráficos
    plot3d(x_g, v_g, Z);     // Dibujamos el plano (superficie)
    
    
    
    // Estética final
    h_plano = gce();
    h_plano.color_flag = 1; // Color basado en Z
    
    title("Regresión Multivariable: Plano vs Datos", "fontsize", 3);
    xlabel("Eje X"); 
    ylabel("Eje V"); 
    zlabel("Eje Y (Dependiente)");
    
    mprintf("\nGráfico 3D generado.\n");
    mprintf("Los puntos rojos son los datos, la superficie es el plano de ajuste.\n")
endfunction



// =========================================================================
//                  EJERCICIO 2 EXAMEN: Ajuste Cosenoidal
// =========================================================================
function run_ejercicio_2_Examen_Coseno()
    clc;
    mprintf("\n=== EJERCICIO 2 EXAMEN: Ajuste y = a + b*cos(2*pi*x) ===\n");
    mprintf("Objetivo: Ajustar una función no polinómica usando Mínimos Cuadrados.\n");
    
      /*ej2 examen:  hallar la funcion del tipo y=a+b*cos(2*pi*x) que mejor se ajuste , mediante el criterio de los minimos cuadrados, a los pares de puntos
    
    xi | 0 | 0.25 | 0.5 | 0.75
    yi | 2 | 1 | 0 | 1
    
    graficar en scilab la nube de puntos y la funcion que los aproxima*/
    
    //A diferencia de los polinomios ($1, x, x^2$), aquí tus funciones base son distintas:Función 1 (para $a$): $f_1(x) = 1$Función 2 (para $b$): $f_2(x) = \cos(2\pi x)$Por lo tanto, no podemos usar tu función ConstruirVandermonde (que solo hace potencias), pero sí podemos usar tu función gausselimPP para resolver el sistema final.
    
    // ************************************************************
    // ************ ZONA DE DATOS (MODIFICAR AQUÍ)  **************
    // ************************************************************
    
    // Datos xi
    x = [0; 0.25; 0.5; 0.75]; // Forzamos columna con ;
    
    // Datos yi
    y = [2; 1; 0; 1];         // Forzamos columna con ;
    
    // ************************************************************
    // ***************** FIN ZONA DE DATOS ************************
    // ************************************************************

    // 1. CONSTRUCCIÓN DE LA MATRIZ DE DISEÑO A
    // El modelo es y = a*(1) + b*(cos(2*pi*x))
    // Columna 1: Unos (coeficiente a)
    // Columna 2: Evaluaciones del coseno (coeficiente b)
    
    col_1 = ones(length(x), 1);
    col_2 = cos(2 * %pi * x);
    
    A = [col_1, col_2];
    
    mprintf("\nMatriz de Diseño A construida manualmente:\n");
    disp(A);
    
    // 2. SISTEMA DE ECUACIONES NORMALES: (A'A)u = A'y
    MatrizNormal = A' * A;
    VectorIndep  = A' * y;
    
    mprintf("\nResolviendo sistema normal con gausselimPP...\n");
    
    // Usamos TU función de eliminación gaussiana
    [coefs, dump] = gausselimPP(MatrizNormal, VectorIndep);
    
    a_val = coefs(1);
    b_val = coefs(2);
    
    mprintf("\n>> RESULTADOS:\n");
    mprintf("   a = %.4f\n", a_val);
    mprintf("   b = %.4f\n", b_val);
    mprintf("\n   Función ajustada: y = %.4f + %.4f * cos(2*pi*x)\n", a_val, b_val);
    
    // 3. CÁLCULO DEL ERROR
    // Evaluamos la función obtenida en los puntos x originales
    // Usamos coefs(:) para asegurar que sea vector columna [2x1]
    // A es [4x2] y coefs(:) es [2x1] -> Resultado [4x1] (Correcto)
    y_aprox_en_puntos = A * coefs(:); // Es lo mismo que a + b*cos...
    error_norma = norm(y - y_aprox_en_puntos);
    
    mprintf("   Error de ajuste (Norma 2): %.4e\n", error_norma);
    if error_norma < 1e-10 then
        mprintf("   ¡Ajuste PERFECTO! La función pasa exactamente por los puntos.\n");
    end

    // 4. GRAFICACIÓN
    // Creamos vector denso para que el coseno se vea curvo y suave
    xx = linspace(min(x)-0.1, max(x)+0.1, 200);
    yy_modelo = a_val + b_val * cos(2 * %pi * xx);
    
    scf(0); clf();
    
    // Puntos originales
    plot(x, y, "ro", "MarkerSize", 10, "MarkerFaceColor", "red");
    
    // Función ajustada
    plot(xx, yy_modelo, "b-", "Thickness", 2);
    
    title("Ajuste Mínimos Cuadrados: a + b*cos(2\pi x)", "fontsize", 3);
    legend(["Datos (xi, yi)"; "Modelo Ajustado y(x)"]);
    xlabel("x"); ylabel("y");
    xgrid();
    
    mprintf("\nGráfica generada.\n");

endfunction


// .........................................................................
// ........................... MENÚ PRINCIPAL ..............................
// .........................................................................

while %t
    mprintf("\n==================================================================\n");
    mprintf("          SISTEMA EXPERTO DE MÍNIMOS CUADRADOS (EXAMEN)           \n");
    mprintf("==================================================================\n");
    mprintf("1. EJ 3: Evolución de Precios (Comparar 2 años, lineal/cuad/cub)\n");
    mprintf("2. EJ 4: Temperaturas (Estabilidad Numérica: Normal vs QR)\n");
    mprintf("3. EJ 5: Epidemia / Gompertz (Linealización con Logaritmos)\n");
    mprintf("4. EJ 6: Multivariable 3D (Plano f = a + bx + cv)\n");
    mprintf("5. GENÉRICO (Ej 7/8): Ajuste Polinomial Simple G1 A G3 (Cualquier Tabla)\n");
    mprintf("6. EJ 2 EXAMEN: Ajuste Cosenoidal (y = a + b*cos(2pi*x))\n");
    mprintf("0. SALIR\n");
    mprintf("------------------------------------------------------------------\n");
    
    opcion = input("Elige una opción: ");
    
    select opcion
    case 1 then run_ejercicio_3_PreciosPan();
    case 2 then run_ejercicio_4_Temperaturas();
    case 3 then run_ejercicio_5_Gompertz();
    case 4 then run_ejercicio_6_Multivariable();
    case 5 then run_ejercicio_Generico();
    case 6 then run_ejercicio_2_Examen_Coseno();
    case 0 then mprintf("\n¡Éxitos en el examen!\n"); break;
    else mprintf("\nOpción no válida.\n");
    end
end
