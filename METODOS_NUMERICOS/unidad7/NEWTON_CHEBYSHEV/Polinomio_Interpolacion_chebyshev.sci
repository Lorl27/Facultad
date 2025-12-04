// Raíces del polinomio de Chebyshev
 // en el intervalo es el estándar: [-1, 1]
function w = roots_Cheby(n)
    // Entrada: n = grad del polinomio de Chebyshev
    // Salida: w = vector con las raices del polinomio de Chebyshev
    for i=0:(n-1) do
        w(i+1)=cos((2*i+1)*%pi/(2*n))
    end
endfunction

/*Para el intervalo $[-1, 1]$ (que es el intervalo estándar de Chebyshev), la fórmula para encontrar los $n$ nodos (raíces de $T_n(x)$) es:
$x_k =\cos\left(\frac{2k-1}{2n}\pi\right),\quad k=1,\dots,n$ */


// Raíces del polinomio de Chebyshev  -- el índice va de i=0  a  n-1
// a, b son los extremos del intervalo no estándar: a != -1 ó b != 1
// es decir, raices en un intervalo arbritario [a,b]
function w = roots_Cheby_ab(n,a,b)
    for i=0:(n-1) do
        w(i+1)=cos((2*i+1)*%pi/(2*n))
    end
    w = ((b-a)*w + (b+a))/2
endfunction

// Generador de Nodos de Chebyshev en intervalo general [a, b]
// Usa el cambio de variable: t = ((b+a) + x*(b-a)) / 2
//n_puntos = cantidad nodos ; gr pol = n_puntos-1 ;)
function t = nodos_chebyshev_ab(n_puntos, a, b)  // -- indice de k=1 a n (OPTIMO)
    // 1. Hallar raíces en intervalo estándar [-1, 1]
    // k va de 1 a n_puntos
    k = 1:n_puntos;
    x_std = cos( ((2*k - 1) ./ (2 * n_puntos)) * %pi );
    
    // 2. Aplicar cambio de variable lineal al intervalo [a, b]
    t = ((b + a) + x_std .* (b - a)) / 2;
endfunction

//============================================================0

// Polinomio de Chebyshev -- RECURSIVO --
function w = Cheby(x,n)
    // Entrada: n = número natural; x = número real
    // Salida: Polinomio de Chebyshev de grado n evaluado en x
    if n==0 then
        w = 1
    elseif n==1 then
        w = x
    elseif n==2 then
        w = 2*x.^2-1
    else
        w = 2*x.*Cheby(x,n-1)-Cheby(x,n-2)
    end
endfunction

// ==========================================
// 2. FUNCIONES AUXILIARES (Interpolación Newton)
// ==========================================
// Usamos Newton para crear el polinomio que pasa por los nodos de Chebyshev  -- CALCULA LOS COEFICIENTES , TABLA DE DIFERENCIAS DIVIDIDAS
function coefs = DiferenciasDivididas(x, y)
    n = length(x);
    D = zeros(n, n);
    D(:,1) = y'; // Columna Y
    for j = 2:n
        for i = 1:n-j+1
            D(i,j) = (D(i+1,j-1) - D(i,j-1)) / (x(i+j-1) - x(i));
        end
    end
    coefs = D(1,:); // Primera fila (Coeficientes a0, a1...)
endfunction

function val = EvalPolinomio(x_nodos, coefs, x_eval)
    // Evaluación usando Horner con la forma de Newton
    n = length(coefs);
    val = coefs(n) * ones(x_eval); 
    for i = n-1:-1:1
        val = val .* (x_eval - x_nodos(i)) + coefs(i);
    end
endfunction

// Construir el objeto Polinomio desde los coeficientes de Newton
function P = ConstruirPoly(x_nodos, coefs)
    s = poly(0, "x");
    P = coefs(1);
    term = 1;
    n = length(coefs);
    for i = 2:n
        term = term * (s - x_nodos(i-1));
        P = P + coefs(i) * term;
    end
endfunction

// ==========================================
// 2.2. FUNCIONES EXACTAS (RUNGE)
// ==========================================
// Función Exacta (Runge)
function y = f_runge(x)
    y = 1 ./ (1 + x.^2);
endfunction

// Función exacta
function y = f_exacta(x)
    y = exp(x);
endfunction

// ==========================================
// 3. RESOLUCIÓN DEL EJERCICIO 10
// ==========================================
mprintf("=== EJERCICIO 10: Interpolación de e^x en [-1, 1] ===\n");

// (a) Hallar nodos y polinomio
// Queremos P3(x) (Grado 3) -> Necesitamos 4 nodos.
// Usamos las raíces de T4(x) usando TU función.
n_nodos = 4;
x_nodos = roots_Cheby_ab(n_nodos,1,-1);  //x_cheb = cos( ((2*k - 1) ./ (2*n)) * %pi );

// Evaluamos f(x) = e^x en esos nodos
y_nodos = exp(x_nodos);

// Construimos el polinomio interpolante (Coeficientes de Newton)
coefs_poly = DiferenciasDivididas(x_nodos, y_nodos);

mprintf("Nodos de Chebyshev utilizados (Raíces de T4):\n");
disp(x_nodos);
mprintf("\nCoeficientes del Polinomio de Interpolación (Newton):\n");
disp(coefs_poly);


// (b) Graficar el error
// Creamos un vector denso para graficar suavemente
xx = linspace(-1, 1, 1000);

// Calculamos valores exactos y aproximados
yy_exacta = exp(xx);
yy_aprox  = EvalPolinomio(x_nodos, coefs_poly, xx);

// Error = Exacta - Aproximada
error_vec = yy_exacta - yy_aprox;
mprintf("\nError máximo absoluto en el intervalo: %.2e\n", max(abs(error_vec)));

// --- GRAFICACIÓN ---
f = scf(0); // Nueva ventana
f.figure_size = [1000, 500];

// Subplot 1: Comparación Visual
subplot(1,2,1);
plot(xx, yy_exacta, "k-", "Thickness", 2); // e^x
plot(xx, yy_aprox, "r--", "Thickness", 2); // P3(x)
plot(x_nodos, y_nodos, "b.", "MarkerSize", 3); // Los nodos usados
title("f(x) = e^x vs P_3(x) (Nodos Chebyshev)", "fontsize", 3);
legend(["Exacta (e^x)"; "Interpolación P3"; "Nodos Chebyshev"], 2);
xlabel("x"); xgrid();

// Subplot 2: El Error
subplot(1,2,2);
plot(xx, error_vec, "b-", "Thickness", 2);
plot(xx, zeros(xx), "k-"); // Línea de referencia 0
title("Error: e^x - P_3(x)", "fontsize", 3);
xlabel("x"); ylabel("Magnitud del Error");
xgrid();

mprintf("\nGráficas generadas. Observa la distribución del error (Equioscilación).\n");

disp("-----------------------SEPARADOR--------------------")
// ==========================================
// 2. RESOLUCIÓN DEL EJERCICIO
// ==========================================
mprintf("=== EJERCICIO 11: Aproximación de cos(t) en [0, pi/2] ===\n");

// --- CONFIGURACIÓN ---
a = 0; 
b = %pi / 2;
n_grado = 3;      // Polinomio Cúbico
n_puntos = n_grado + 1; // Necesitamos 4 nodos para grado 3

// --- 1. OBTENER NODOS ---
// A) Nodos de Chebyshev (usando el cambio de variable)
t_cheby = nodos_chebyshev_ab(n_puntos, a, b);

// B) Nodos Equidistantes (para comparar, como tenías en tu código)
t_equi = linspace(a, b, n_puntos);

// --- 2. EVALUAR LA FUNCIÓN g(t) = cos(t) ---
y_cheby = cos(t_cheby);
y_equi  = cos(t_equi);

mprintf("Nodos Chebyshev en [0, %.4f]:\n", b);
disp(t_cheby);

// --- 3. INTERPOLACIÓN (Obtener polinomios) ---
coefs_cheby = DiferenciasDivididas(t_cheby, y_cheby);
coefs_equi  = DiferenciasDivididas(t_equi, y_equi);


// ==========================================
// 3. GRÁFICAS Y ERROR
// ==========================================
// Grid denso para graficar curvas suaves
tt = linspace(a, b, 1000);
y_exacta = cos(tt);

// Evaluar polinomios
p_cheby_vals = EvalPolinomio(t_cheby, coefs_cheby, tt);
p_equi_vals  = EvalPolinomio(t_equi, coefs_equi, tt);

// Calcular Errores
err_cheby = y_exacta - p_cheby_vals;
err_equi  = y_exacta - p_equi_vals;

// --- DIBUJAR ---
f2 = scf(1);  //nueva ventana ID1
f2.figure_size = [1000, 500];

// Subplot 1: Función y Aproximaciones
subplot(1,2,1);
plot(tt, y_exacta, "k-", "Thickness", 3);
plot(tt, p_cheby_vals, "b--", "Thickness", 2);
plot(tt, p_equi_vals, "r:", "Thickness", 2);
plot(t_cheby, y_cheby, "b.", "MarkerSize", 3); // Nodos Cheby
title("Aproximación Cúbica de cos(t)", "fontsize", 3);
legend(["cos(t)"; "Chebyshev"; "Equidistante"], 3); // 3=Abajo Izq
xlabel("t"); xgrid();

// Subplot 2: Comparación de Errores
subplot(1,2,2);
plot(tt, err_cheby, "b-", "Thickness", 2);
plot(tt, err_equi, "r-", "Thickness", 1);
plot(tt, zeros(tt), "k-"); // Eje 0
title("Error de Aproximación (Grado 3)", "fontsize", 3);
legend(["Error Chebyshev"; "Error Equidistante"], 1); // 1=Arriba Der
xlabel("t"); ylabel("Error");
xgrid();

// Resultados numéricos
max_err_cheby = max(abs(err_cheby));
max_err_equi = max(abs(err_equi));

mprintf("\n--- RESULTADOS DE ERROR MÁXIMO ---\n");
mprintf("Equidistante: %.6f\n", max_err_equi);
mprintf("Chebyshev:    %.6f\n", max_err_cheby);

if max_err_cheby < max_err_equi then
    mprintf(">> Conclusión: Chebyshev reduce el error máximo.\n");
end

disp("-----------------------SEPARADOR--------------------")
//====================================
// 2. CONFIGURACIÓN DEL PROBLEMA
// ==========================================
mprintf("=== EJERCICIO 2: Interpolación de e^x en [-1, 1] ===\n");

// Derivada (n+1) para la cota de error
// Tenemos 4 nodos -> Polinomio Grado 3 (n=3).
// Fórmula error usa derivada n+1 = 4.
// f''''(x) de e^x es e^x.
// El máximo en [-1, 1] ocurre en x=1.
M4 = exp(1); 
Factorial_4 = 24; // 4!


// ==========================================
// 3. INCISO A: Interpolación Equidistante
// ==========================================
// Corregimos los nodos para que sean uniformes en [-1, 1]
x_eq = [-1, -1/3, 1/3, 1]; 
y_eq = f_exacta(x_eq);

// Coeficientes del polinomio p(x)
coefs_p = DiferenciasDivididas(x_eq, y_eq);

mprintf("\n--- (a) Polinomio p(x) (Equidistante) ---\n");
mprintf("Nodos: "); disp(x_eq);
mprintf("Coeficientes Newton: "); disp(coefs_p);


// ==========================================
// 4. INCISO B: Evaluación Puntual
// ==========================================
puntos_test = [-0.9, 0.01];

mprintf("\n--- (b) Evaluación en puntos ---\n");
for val = puntos_test
    exacto = f_exacta(val);
    aprox  = EvalPolinomio(x_eq, coefs_p, val);
    err_real = abs(exacto - aprox);
    
    mprintf("x = %.2f | Exacto: %.6f | p(x): %.6f | Error Real: %.2e\n",...
             val, exacto, aprox, err_real);
end


// ==========================================
// 5. INCISO C: Cotas Puntuales
// ==========================================
// Cota = (M4 / 4!) * |(x-x0)(x-x1)(x-x2)(x-x3)|
mprintf("\n--- (c) Cotas de Error Puntuales ---\n");

for val = puntos_test
    // Calcular producto de nodos
    prod_nodos = 1;
    for node = x_eq
        prod_nodos = prod_nodos * abs(val - node);
    end
    
    cota_puntual = (M4 / Factorial_4) * prod_nodos;
    mprintf("Cota teórica para x=%.2f: %.2e\n", val, cota_puntual);
end


// ==========================================
// 6. INCISO D: Cota Global (Equidistante)
// ==========================================
// Necesitamos el máximo de |(x-x0)...(x-x3)| en [-1, 1].
// Lo estimamos numéricamente recorriendo el intervalo.
xx_grid = linspace(-1, 1, 1000);
w_eq_vals = ones(xx_grid);
for node = x_eq
    w_eq_vals = w_eq_vals .* (xx_grid - node);
end
max_w_eq = max(abs(w_eq_vals));

Cota_Global_Eq = (M4 / Factorial_4) * max_w_eq;

mprintf("\n--- (d) Cota Global Error p(x) en [-1,1] ---\n");
mprintf("Max valor del polinomio nodal: %.4f\n", max_w_eq);
mprintf("Cota Global Teórica: %.2e\n", Cota_Global_Eq);


// ==========================================
// 7. INCISO E: Interpolación Chebyshev (q(x))
// ==========================================
// 4 Nodos (para grado 3)
x_cheb = roots_Cheby(4);
y_cheb = f_exacta(x_cheb);

coefs_q = DiferenciasDivididas(x_cheb, y_cheb);

mprintf("\n--- (e) Polinomio q(x) (Chebyshev) ---\n");
mprintf("Nodos Chebyshev: "); disp(x_cheb);


// ==========================================
// 8. INCISO F: Cota Global (Chebyshev)
// ==========================================
// Fórmula simplificada para Chebyshev en [-1, 1]:
// Max|Error| <= M4 / (2^n * (n+1)!) con n=3 (grado) -> 2^3 = 8
// Denominador: 2^(4-1) * 4! = 8 * 24 = 192
Cota_Global_Cheb = M4 / (8 * Factorial_4);

mprintf("\n--- (f) Cota Global Error q(x) ---\n");
mprintf("Fórmula: M4 / (2^3 * 4!) = %.4f / 192\n", M4);
mprintf("Cota Global Chebyshev: %.2e\n", Cota_Global_Cheb);


// ==========================================
// 9. INCISO G: Gráficas y Comparación
// ==========================================

// Errores reales a lo largo del intervalo
vals_p = EvalPolinomio(x_eq, coefs_p, xx_grid);
vals_q = EvalPolinomio(x_cheb, coefs_q, xx_grid);

err_p = abs(f_exacta(xx_grid) - vals_p);
err_q = abs(f_exacta(xx_grid) - vals_q);

clf();
f3 = scf(2);
f3.figure_size = [1000, 500]; // Ventana ancha

// Graficar curvas de error
plot(xx_grid, err_p, "r-", "Thickness", 2); // Error Equidistante
plot(xx_grid, err_q, "b-", "Thickness", 2); // Error Chebyshev

// Graficar las líneas de las COTAS calculadas (D y F)
plot(xx_grid, ones(xx_grid)*Cota_Global_Eq, "r--", "Thickness", 1);
plot(xx_grid, ones(xx_grid)*Cota_Global_Cheb, "b--", "Thickness", 1);

title("Error Real vs Cotas Teóricas (e^x, grado 3)");
xlabel("x"); ylabel("Magnitud del Error");
legend(["Error Real p(x) (Equi)"; "Error Real q(x) (Cheb)"; 
        "Cota Teórica (Equi)"; "Cota Teórica (Cheb)"], 1); // 1=Arriba Der
xgrid();

mprintf("\n--- (g) Conclusión ---\n");
mprintf("Observa en la gráfica como el error de Chebyshev (azul)\n");
mprintf("es más uniforme y su cota es menor que la equidistante (roja)");

disp("-----------------------SEPARADOR--------------------")
// ==========================================
// 2. EJECUCIÓN DEL EJERCICIO 4- RUNGE.
// ==========================================

// Grilla densa para graficar las curvas suaves y el error
xx = linspace(-5, 5, 500); 
yy_exacta = f_runge(xx);

// Grados solicitados
grados = [2, 4, 6, 10, 14];
colores = [2, 3, 5, 6, 13]; // Azul, Verde, Rojo, Magenta, etc.
textos_legenda = [];

// Preparamos la figura
f4 = scf(3);
f4.figure_size = [1000, 500]; // Ventana ancha

// --- SUBPLOT 1: Función vs Aproximación (Solo n=14 para ver el desastre) ---
subplot(1,2,1);
plot(xx, yy_exacta, "k-", "Thickness", 2); // Función original

// Calculamos n=14
n_max = 14;
nodos_14 = linspace(-5, 5, n_max + 1);
y_nodos_14 = f_runge(nodos_14);
coefs_14 = DiferenciasDivididas(nodos_14, y_nodos_14);
P_14 = ConstruirPoly(nodos_14, coefs_14);
yy_aprox_14 = horner(P_14, xx);

plot(xx, yy_aprox_14, "r--", "Thickness", 1);
plot(nodos_14, y_nodos_14, "r.", "MarkerSize", 2); // Nodos

title("Fenómeno de Runge (n=14)", "fontsize", 3);
legend(["Exacta: 1/(1+x^2)"; "Interpolación (n=14)"], 3); // abajo-izq
xlabel("x"); xgrid();


// --- SUBPLOT 2: Errores para todos los n ---
subplot(1,2,2);
a = gca();
a.auto_clear = "off"; // Permitir superponer gráficas
plot(xx, zeros(xx), "k-"); // Línea cero referencia

for i = 1:length(grados)
    n = grados(i);
    
    // 1. Definir nodos equiespaciados
    nodos = linspace(-5, 5, n + 1);
    
    // 2. Calcular polinomio
    y_nodos = f_runge(nodos);
    coefs = DiferenciasDivididas(nodos, y_nodos);
    P = ConstruirPoly(nodos, coefs);
    
    // 3. Calcular Error: E(x) = f(x) - P(x)
    yy_aprox = horner(P, xx);
    error_vec = yy_exacta - yy_aprox;
    
    // 4. Graficar Error
    plot(xx, error_vec, "color", colores(i), "Thickness", 2);
    
    // Guardar texto para leyenda
    textos_legenda = [textos_legenda; "n = " + string(n)];
end

title("Error de Interpolación (f(x) - Pn(x))", "fontsize", 3);
legend(textos_legenda, 1); // arriba-der
xlabel("x"); ylabel("Error");
xgrid();

mprintf("Gráficas generadas.\n");


// --- CASO B: Chebyshev (La solución) ---
// ==========================================
// 2. COMPARACIÓN: EQUIDISTANTE VS CHEBYSHEV
// ==========================================

// Configuración
a = -5; b = 5;
n = 14; // Grado alto para ver el efecto
xx = linspace(a, b, 500); // Grilla densa para graficar
yy_exacta = f_runge(xx);


// --- CASO A: Equidistante (El problema) ---
x_equi = linspace(a, b, n+1);
y_equi = f_runge(x_equi);
coefs_equi = DiferenciasDivididas(x_equi, y_equi);
yy_equi = EvalPolinomio(x_equi, coefs_equi, xx);


// --- CASO B: Chebyshev (La solución) ---
x_cheb = nodos_chebyshev_ab(n+1, a, b);
y_cheb = f_runge(x_cheb);
coefs_cheb = DiferenciasDivididas(x_cheb, y_cheb);
yy_cheb = EvalPolinomio(x_cheb, coefs_cheb, xx);


// ==========================================
// 3. GRAFICACIÓN DE RESULTADOS
// ==========================================

f5 = scf(4);
f5.figure_size = [1000, 500];

// -- SUBPLOT 1: Las Funciones --
subplot(1,2,1);
plot(xx, yy_exacta, "k-", "Thickness", 3); // Exacta
plot(xx, yy_equi, "r--", "Thickness", 1);  // Equidistante (Mala)
plot(xx, yy_cheb, "b-", "Thickness", 2);   // Chebyshev (Buena)

// Dibujar los nodos sobre las curvas
plot(x_equi, y_equi, "r.", "MarkerSize", 2); 
plot(x_cheb, y_cheb, "b.", "MarkerSize", 3);

title("Comparación de Interpolación (n=" + string(n) + ")", "fontsize", 3);
legend(["Exacta"; "Equidistante (Runge!)"; "Nodos Chebyshev"], 3); // abajo-izq
xlabel("x"); xgrid();


// -- SUBPLOT 2: El Error --
subplot(1,2,2);
err_equi = abs(yy_exacta - yy_equi);
err_cheb = abs(yy_exacta - yy_cheb);

plot(xx, err_equi, "r-", "Thickness", 1);
plot(xx, err_cheb, "b-", "Thickness", 2);

title("Error Absoluto |f(x) - P(x)|", "fontsize", 3);
legend(["Error Equidistante"; "Error Chebyshev"], 2); // arriba-izq
xlabel("x"); ylabel("Magnitud del Error");
xgrid();

mprintf("=== RESULTADOS NUMÉRICOS (Máximo Error) ===\n");
mprintf("Max Error con nodos Equidistantes: %.4f\n", max(err_equi));
mprintf("Max Error con nodos Chebyshev:     %.4f\n", max(err_cheb));
mprintf("-------------------------------------------\n");
mprintf("Conclusión: Chebyshev reduce drásticamente el error en los bordes.\n");



/*
onclusión (Fenómeno de Runge): Al interpolar funciones suaves (como la campana de Runge) usando nodos equiespaciados, aumentar el grado del polinomio NO garantiza disminuir el error. De hecho, el error máximo (norma infinito) diverge hacia infinito en los extremos.

Solución (Dato extra): Esto se soluciona utilizando Nodos de Chebyshev (puntos más concentrados en los bordes y separados en el centro) en lugar de nodos equiespaciados.

Qué observarás en la pantalla?En el Gráfico de la Izquierda:La línea roja (equidistante) se vuelve loca en $-5$ y $5$, alejándose mucho de la curva negra.La línea azul (Chebyshev) sigue casi perfectamente a la curva negra. Si te fijas en los puntos azules (nodos), verás que están muy juntos en los extremos y separados en el centro.En el Gráfico de la Derecha (Errores):El error rojo será gigante (probablemente mayor a 1 o 2).El error azul será una línea casi plana pegada al cero en comparación.En la Consola:Te mostrará los valores numéricos. Es común ver que el error equidistante es, por ejemplo, 3.5 y el de Chebyshev es 0.05. ¡Una mejora de casi 100 veces!
*/
