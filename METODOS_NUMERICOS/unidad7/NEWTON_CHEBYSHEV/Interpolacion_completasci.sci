// =========================================================================
//                           LIBRERÍA DE FUNCIONES
// =========================================================================

// 1. Generador de Nodos (Intervalo General [a, b])
// n_puntos : cantidad de nodos.
function t=nodos_chebyshev_ab(n_puntos, a, b)
    k = 1:n_puntos;
    x_std = cos( ((2*k - 1) ./ (2 * n_puntos)) * %pi );
    t = ((b + a) + x_std .* (b - a)) / 2; //cambio de variable.
endfunction

// 2. Raíces Estándar Chebyshev (Intervalo [-1, 1])
// n: grado polinomio
function w=roots_Cheby(n)
    for i=0:(n-1) do
        w(i+1)=cos((2*i+1)*%pi/(2*n)) //vector
    end
endfunction

//2.5 Raices NO Estándar Chebyshev (Intervalo arbritario [a,b])
function w2 = roots_Cheby_ab(n,a,b)
    for i=0:(n-1) do
        w2(i+1)=cos((2*i+1)*%pi/(2*n))
    end
    w2 = ((b-a)*w2 + (b+a))/2
endfunction


// 3. Polinomio Chebyshev Recursivo (Evaluación de Tn(x))
function val=Cheby(x, n)
    if n==0 then
        val = ones(x);
    elseif n==1 then
        val = x;
    else
        // Recursión: Tn(x) = 2x*Tn-1(x) - Tn-2(x)
        val = 2*x.*Cheby(x,n-1) - Cheby(x,n-2);
    end
endfunction

// 4. Diferencias Divididas (Newton) 
// Se usa para crear el polinomia que pasa por los nodos de Chebyshev
function coefs=DiferenciasDivididas(x, y)
    n = length(x);
    D = zeros(n, n);
    D(:,1) = y'; // Col y
    for j = 2:n
        for i = 1:n-j+1
            D(i,j) = (D(i+1,j-1) - D(i,j-1)) / (x(i+j-1) - x(i));
        end
    end
    coefs = D(1,:);  // Primera fila (Coeficientes a0,a1...)
endfunction

// 5. Evaluación de Polinomio Interpolante - Utiliza forma Newton + Horner.
function val=EvalPolinomio(x_nodos, coefs, x_eval)
    n = length(coefs);
    val = coefs(n) * ones(x_eval); 
    for i = n-1:-1:1
        val = val .* (x_eval - x_nodos(i)) + coefs(i);
    end
endfunction

//6.  Construir el objeto Polinomio desde los coeficientes de Newton
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

// =========================================================================
//                           FUNCIONES EXACTAS
// =========================================================================
function y = f_runge(x)
    y = 1 ./ (1 + x.^2);
endfunction

// Función exacta
function y = f_exacta(x)
    y = exp(x);
endfunction

// =========================================================================
//                        BLOQUE DE EJERCICIOS
// =========================================================================

function resolver_ejercicio_2_formaCotas()
    clc;
    mprintf("\n=== EJERCICIO 2: Cotas de Error (Teórica vs Real) ===\n");
    mprintf("Objetivo: Verificar que el error real es menor a la cota teórica.\n");

    // --- [MODIFICAR AQUÍ] ---
    deff('y=f(x)', 'y = exp(x)'); 
    a = -1; b = 1;
    n_grado = 3;  // Polinomio cúbico (4 nodos)
    
    // COTA TEÓRICA: Necesitamos el maximo de la derivada n+1=4
    // Si f(x)=e^x, f''''(x)=e^x. Max en [-1,1] es e^1.
    M4 = exp(1); 
    fact_4 = 24; // 4!
    // ------------------------

    n_puntos = n_grado + 1;
    xx = linspace(a, b, 1000);
    
    // 1. Interpolación Equidistante
         x_eq = linspace(a, b, n_puntos);
        coefs_eq = DiferenciasDivididas(x_eq, f(x_eq));
        err_real_eq = abs(f(xx) - EvalPolinomio(x_eq, coefs_eq, xx));
    
    // 2. Interpolación Chebyshev
          x_cheb = nodos_chebyshev_ab(n_puntos, a, b);
          coefs_cheb = DiferenciasDivididas(x_cheb, f(x_cheb));
          err_real_cheb = abs(f(xx) - EvalPolinomio(x_cheb, coefs_cheb, xx));

    // 3. Calculo de Cota Teórica Global (Chebyshev)
    // Formula: MaxError <= M4 / (2^n * (n+1)!) para intervalo [-1,1] estándar
    // Nota: Si el intervalo no es [-1,1], se escala.
          cota_teorica_cheb = M4 / (2^n_grado * fact_4); 

    // Graficar
        scf(0); clf();
        plot(xx, err_real_eq, "r-", "Thickness", 1);
        plot(xx, err_real_cheb, "b-", "Thickness", 2);
        // Dibujamos la linea de la cota
        plot(xx, ones(xx)*cota_teorica_cheb, "g--", "Thickness", 2);
        
        legend(["Error Real Equidistante"; "Error Real Chebyshev"; "Cota Teórica Cheby"]);
        title("Ejercicio 2: Error Real vs Cota Teórica");
        xgrid();
        
        mprintf("\nResultados:\n");
        mprintf("Max Error Real (Cheby): %.2e\n", max(err_real_cheb));
        mprintf("Cota Teórica (Formula): %.2e\n", cota_teorica_cheb);
        if max(err_real_cheb) <= cota_teorica_cheb * 1.0001 then // Tolerancia pequeña
            mprintf(">> VERIFICADO: El error real respeta la cota teórica.\n");
        else
            mprintf(">> CUIDADO: Revisa las derivadas o el intervalo.\n");
        end
endfunction

function resolver_ejercicio_10()
    clc;
    mprintf("\n=== EJERCICIO 10: Interpolación e^x en [-1,1] ===\n");
    // --- [MODIFICAR AQUÍ] ---
    deff('y=f(x)', 'y = exp(x)');
    a = -1; b = 1; n_grado = 3;
    // ------------------------
    
    //1 . Hallar nodos y polinomio:
        n = n_grado + 1;
        x_n = nodos_chebyshev_ab(n, a, b); //x_nodos = roots_Cheby_ab(n_nodos,1,-1);  //x_cheb = cos( ((2*k - 1) ./ (2*n)) * %pi );
        coefs = DiferenciasDivididas(x_n, f(x_n)); //polinomio interpolante
        
        mprintf("Nodos de Chebyshev utilizados (Raíces de T4):\n");
        disp(x_n);
        mprintf("\nCoeficientes del Polinomio de Interpolación (Newton):\n");
        disp(coefs);
    
    // 2. Hallar error:
        xx = linspace(a, b, 1000); // Creamos un vector denso para graficar suavemente
        // Calculamos valores exactos y aproximados
        yy_exacta = exp(xx);
        yy_aprox = EvalPolinomio(x_n, coefs, xx);
        
        // Error = Exacta - Aproximada
        error_vec = yy_exacta - yy_aprox;
        mprintf("\nError máximo absoluto en el intervalo: %.2e\n", max(abs(error_vec)));
        
    // 3. Graficar errores:  
     
        fig = scf(1); // Nueva ventana
        fig.figure_size = [1000, 500];
        
        // Subplot 1: Comparación Visual
        subplot(1,2,1);
        plot(xx, yy_exacta, "k-", "Thickness", 2); // e^x
        plot(xx, yy_aprox, "r--", "Thickness", 2); // P3(x)
        plot(x_n, f(x_n), "b.", "MarkerSize", 3); // Los nodos usados
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
endfunction

function resolver_ejercicio_2_COMPLETO()
        mprintf("=== EJERCICIO 2: Interpolación de e^x en [-1, 1] ===\n");
        
        // --- [MODIFICAR AQUÍ] ---
        n_grado = 3;  // Polinomio cúbico (4 nodos)
    
        // COTA TEÓRICA: Necesitamos el maximo de la derivada n+1=4
        // Si f(x)=e^x, f''''(x)=e^x. Max en [-1,1] es e^1.
        M4 = exp(1); 
        fact_4 = 24; // 4!
        
        // 1. Interpolación Equidistante
            x_eq = [-1, -1/3, 1/3, 1]; //nodos uniformes en [-1,1]
            y_eq = f_exacta(x_eq);
            coefs_eq = DiferenciasDivididas(x_eq, y_eq); //coef pol p(x)
            mprintf("\n--- (a) Polinomio p(x) (Equidistante) ---\n");
            mprintf("Nodos: "); disp(x_eq);
            mprintf("Coeficientes Newton: "); disp(coefs_eq);
        
        //2. Evaluación Puntual                
            puntos_test = [-0.9, 0.01];
            
            mprintf("\n--- (b) Evaluación en puntos ---\n");
            for val = puntos_test
                exacto = f_exacta(val);
                aprox  = EvalPolinomio(x_eq, coefs_eq, val);
                err_real = abs(exacto - aprox);
                
                mprintf("x = %.2f | Exacto: %.6f | p(x): %.6f | Error Real: %.2e\n",...
                         val, exacto, aprox, err_real);
            end
            
        //3. Cotas Puntuales    
            // Cota = (M4 / 4!) * |(x-x0)(x-x1)(x-x2)(x-x3)|
            mprintf("\n--- (c) Cotas de Error Puntuales ---\n");
            
            for val = puntos_test
                // Calcular producto de nodos
                prod_nodos = 1;
                for node = x_eq
                    prod_nodos = prod_nodos * abs(val - node);
                end
                
                cota_puntual = (M4 / fact_4) * prod_nodos;
                mprintf("Cota teórica para x=%.2f: %.2e\n", val, cota_puntual);
            end
            
        //4. Cota Global - Equidistante    
            // Necesitamos el máximo de |(x-x0)...(x-x3)| en [-1, 1].
            // Lo estimamos numéricamente recorriendo el intervalo.
            xx_grid = linspace(-1, 1, 1000);
            w_eq_vals = ones(xx_grid);
            for node = x_eq
                w_eq_vals = w_eq_vals .* (xx_grid - node);
            end
            max_w_eq = max(abs(w_eq_vals));
            
            Cota_Global_Eq = (M4 / fact_4) * max_w_eq;
            
            mprintf("\n--- (d) Cota Global Error p(x) en [-1,1] ---\n");
            mprintf("Max valor del polinomio nodal: %.4f\n", max_w_eq);
            mprintf("Cota Global Teórica: %.2e\n", Cota_Global_Eq);


            
        // 5. Interpolación Chebyshev (q(x))
            // 4 Nodos (para grado 3)
            x_cheb = roots_Cheby(4);
            y_cheb = f_exacta(x_cheb);
            
            coefs_q = DiferenciasDivididas(x_cheb, y_cheb);
            
            mprintf("\n--- (e) Polinomio q(x) (Chebyshev) ---\n");
            mprintf("Nodos Chebyshev: "); disp(x_cheb);

        
        // 6. Calculo de Cota Teórica Global (Chebyshev)
            // Formula: Max|Error| <= M4 / (2^n * (n+1)!) para intervalo [-1,1] estándar
            //n=3,  2^3 = 8 , luego Denominador: 2^(4-1) * 4! = 8 * 24 = 192
            // Nota: Si el intervalo no es [-1,1], se escala.
            Cota_Global_Cheb = M4 / (2^n_grado * fact_4); 
            
            mprintf("\n--- (f) Cota Global Error q(x) ---\n");
            mprintf("Fórmula: M4 / (2^3 * 4!) = %.4f / 192\n", M4);
            mprintf("Cota Global Chebyshev: %.2e\n", Cota_Global_Cheb);

     // Graficar
        // Errores reales a lo largo del intervalo
        vals_p = EvalPolinomio(x_eq, coefs_eq, xx_grid);
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

endfunction

function resolver_ejercicio_11()
    clc;
    mprintf("\n=== EJERCICIO 11: cos(t) Equi vs Cheby ===\n");
    // --- [MODIFICAR AQUÍ] ---
    deff('y=f(t)', 'y = cos(t)');
    a = 0; b = %pi/2; n_grado = 3;
    // ------------------------
    n = n_grado + 1;
    t_eq = linspace(a, b, n);
    t_ch = nodos_chebyshev_ab(n, a, b);
    
    tt = linspace(a, b, 500);
    y_eq = EvalPolinomio(t_eq, DiferenciasDivididas(t_eq, f(t_eq)), tt);
    y_ch = EvalPolinomio(t_ch, DiferenciasDivididas(t_ch, f(t_ch)), tt);
    
    scf(2); clf();
    plot(tt, abs(f(tt)-y_eq), "r-");
    plot(tt, abs(f(tt)-y_ch), "b-");
    legend(["Error Equi"; "Error Cheby"]); title("Comparación de Errores"); xgrid();
    mprintf("Error Max Equi: %.2e | Error Max Cheby: %.2e\n", max(abs(f(tt)-y_eq)), max(abs(f(tt)-y_ch)));
endfunction

function resolver_ejercicio_11_EXTENSIVO()
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
endfunction

function resolver_runge_1()
    clc;
    mprintf("\n=== FENÓMENO DE RUNGE (Grado Alto) ===\n");
    // --- [MODIFICAR AQUÍ] ---
    deff('y=f(x)', 'y = 1 ./ (1 + x.^2)');
    a = -5; b = 5; n_grado = 14;
    // ------------------------
    x_ch = nodos_chebyshev_ab(n_grado+1, a, b);
    x_eq = linspace(a, b, n_grado+1);
    xx = linspace(a, b, 500);
    
    y_ch = EvalPolinomio(x_ch, DiferenciasDivididas(x_ch, f(x_ch)), xx);
    y_eq = EvalPolinomio(x_eq, DiferenciasDivididas(x_eq, f(x_eq)), xx);
    
    scf(3); clf();
    plot(xx, f(xx), "k-", "Thickness", 2);
    plot(xx, y_eq, "r-"); plot(xx, y_ch, "b-");
    legend(["Exacta"; "Equidistante (Runge)"; "Chebyshev"]); 
    title("Fenómeno de Runge n="+string(n_grado));set(gca(), "data_bounds", [a -1; b 2]); // límites de los ejes
     xgrid();
endfunction

function resolver_runge2()
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
    Conclusión (Fenómeno de Runge): Al interpolar funciones suaves (como la campana de Runge) usando nodos equiespaciados, aumentar el grado del polinomio NO garantiza disminuir el error. De hecho, el error máximo (norma infinito) diverge hacia infinito en los extremos.
    
    Solución (Dato extra): Esto se soluciona utilizando Nodos de Chebyshev (puntos más concentrados en los bordes y separados en el centro) en lugar de nodos equiespaciados.
    
    Qué observarás en la pantalla?En el Gráfico de la Izquierda:La línea roja (equidistante) se vuelve loca en $-5$ y $5$, alejándose mucho de la curva negra.La línea azul (Chebyshev) sigue casi perfectamente a la curva negra. Si te fijas en los puntos azules (nodos), verás que están muy juntos en los extremos y separados en el centro.En el Gráfico de la Derecha (Errores):El error rojo será gigante (probablemente mayor a 1 o 2).El error azul será una línea casi plana pegada al cero en comparación.En la Consola:Te mostrará los valores numéricos. Es común ver que el error equidistante es, por ejemplo, 3.5 y el de Chebyshev es 0.05. ¡Una mejora de casi 100 veces!
    */

endfunction

function ejemplo_extra_funciones_sin_usar()
    clc;
    mprintf("\n=== EJEMPLO EXTRA: Visualizando T_n(x) ===\n");
    mprintf("Uso de las funciones Cheby (recursiva) y roots_Cheby (estándar).\n");
    
    // Aquí usamos Cheby(x, n) para dibujar los polinomios base T3 y T4
    // Y usamos roots_Cheby(n) para mostrar que las raíces coinciden con el cruce por cero
    
    xx = linspace(-1, 1, 500);
    n_ejemplo = 4; // Vamos a graficar T4(x)
    
    // 1. Evaluar T4(x) usando la función recursiva
    yy_T4 = Cheby(xx, n_ejemplo);
    
    // 2. Obtener las raíces usando la función estándar
    raices = roots_Cheby(n_ejemplo);
    
    // Graficar
    scf(4); clf();
    plot(xx, yy_T4, "b-", "Thickness", 2);  // El Polinomio T4
    plot(xx, zeros(xx), "k-");              // Eje 0
    plot(raices, zeros(raices), "ro", "MarkerSize", 3); // Las Raíces
    
    title("Polinomio de Chebyshev T_" + string(n_ejemplo) + "(x) y sus Raíces");
    legend(["Polinomio T4(x)"; "Eje 0"; "Raíces calculadas con roots_Cheby"]);
    xgrid();
    
    mprintf("\nExplicación:\n");
    mprintf("La curva azul es el polinomio generado recursivamente.\n");
    mprintf("Los círculos rojos son las raíces calculadas con la fórmula del coseno.\n");
    mprintf("¡Deben coincidir perfectamente sobre el eje cero!\n");
endfunction


// =========================================================================
//                             PROGRAMA PRINCIPAL (MAIN)
// =========================================================================

while %t
    mprintf("\n============================================\n");
    mprintf("       MENÚ PARCIAL - MÉTODOS NUMÉRICOS\n");
    mprintf("============================================\n");
    mprintf("1. Ejercicio 10 (Interpolación e^x)\n");
    mprintf("2. Ejercicio 11 (Comparativa cos(t))\n");
    mprintf("3. Ejercicio 2  (Cotas de Error Teóricas vs Reales)\n");
    mprintf("4. Ejercicio 4 - Runge (Interpolación Grado Alto)\n");
    mprintf("5. EXTRA: Test de funciones Cheby y roots\n");
    mprintf("6. Ejercicio 2  (COMPLETO - Equidistante vs Chebyshev)\n");
    mprintf("7. Ejercicio 4 - Runge (Interpolación Grado Alto COMPLETO - REAL VS EQUIDISTANTE VS CHEVYSHEV)\n");
    mprintf("8. Ejercicio 11 -  EQUIDISTANTE VS CHEVYSHEV + errores.)\n");

    mprintf("0. SALIR\n");
    mprintf("============================================\n");
    
    opcion = input("Elige una opción: ");
    
    select opcion
    case 1 then
        resolver_ejercicio_10();
    case 2 then
        resolver_ejercicio_11();
    case 3 then
        resolver_ejercicio_2_formaCotas();
    case 4 then
        resolver_runge_1();
    case 5 then
        ejemplo_extra_funciones_sin_usar();
    case 6 then
        resolver_ejercicio_2_COMPLETO();
    case 7 then
        resolver_runge2();
    case 8 then
         resolver_ejercicio_11_EXTENSIVO();

    case 0 then
        mprintf("\nÉxitos en el examen!\n");
        break;
    else
        mprintf("\nOpción no válida.\n");
    end
end
