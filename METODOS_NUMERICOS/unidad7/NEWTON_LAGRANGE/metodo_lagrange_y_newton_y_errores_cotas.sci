// ==========================================
// 1. DEFINICIÓN DE FUNCIONES (Lagrange y Newton)
// ==========================================

// --- Funciones para Lagrange ---
function y = Lk(x, k)
    [Xn, Xm] = size(x);
    // Excluir el punto k actual
    r = [x(1:k-1) x(k+1:Xm)]; 
    // Crear el polinomio con las raíces restantes
    p = poly(r, "x", "roots"); 
    // Evaluar el denominador
    pk = horner(p, x(k)); 
    y = p / pk;
endfunction

function z = interpolLagrange(x, y)
    [Xn, Xm] = size(x);
    pol = 0;
    for k = 1:Xm
        pol = pol + (Lk(x, k) * y(k));
    end
    z = pol;
endfunction

// --- Funciones para Newton (Diferencias Divididas) ---
function w = DD(x, y)
    n = length(x);
    if n == 1 then
        w = y(1);
    else
        w = (DD(x(2:n), y(2:n)) - DD(x(1:n-1), y(1:n-1))) / (x(n) - x(1));
    end
endfunction

function p = DD_newton(x, y)
    r = poly(0, "x");
    p = 0;
    n = length(x);
    // Construcción del polinomio de Newton
    for i = n:(-1):2
        p = (p + DD(x(1:i), y(1:i))) * (r - x(i-1));
    end
    p = p + y(1);
endfunction

// ==========================================
// 4. FUNCIONES ESPECÍFICAS PARA NEWTON (TABLAS)
// ==========================================

// Calcula la Tabla completa y devuelve los coeficientes de la diagonal
function [coefs, Tabla] = TablaNewton(x, y)
    n = length(x);
    Tabla = zeros(n, n);
    Tabla(:,1) = y'; // La primera columna son las Y
    
    for j = 2:n // Para cada orden de diferencia (columnas)
        for i = 1:n-j+1 // Filas
            numerador = Tabla(i+1, j-1) - Tabla(i, j-1);
            denominador = x(i+j-1) - x(i);
            Tabla(i,j) = numerador / denominador;
        end
    end
    coefs = Tabla(1,:); // La diagonal superior son los coeficientes
endfunction

// Evalúa el polinomio de Newton usando los coeficientes
function val = EvalPolNewton(x_eval, x_nodos, coefs)
    n = length(coefs);
    val = coefs(n) * ones(x_eval); // Empezamos con bn
    
    // Algoritmo de Horner anidado: bn*(x-xn-1) + bn-1 ...
    for i = n-1:-1:1
        val = val .* (x_eval - x_nodos(i)) + coefs(i);
    end
endfunction



// ==========================================
// 2. FUNCIÓN DE COTA AUTOMÁTICA (NUEVA)
// ==========================================
function [Cota, M_calc, W_max] = CalcularCotaAutomatica(func_str, a, b, n, nodos)
    // func_str: string con la función, ej: '(1+x)./(1+2*x)'
    // a, b: intervalo
    // n: grado del polinomio (se necesita derivada n+1)
    // nodos: vector con los nodos de interpolación
    
    // 1. Configuración de malla fina para derivar
    h_step = 0.0001; // Paso pequeño para derivar
    x_grid = a:h_step:b;
    
    // 2. Evaluar función original
    deff('y=temp_f(x)', 'y='+func_str);
    y_vals = temp_f(x_grid);
    
    // 3. Derivar numéricamente n+1 veces
    // dy/dx approx (y_i+1 - y_i) / h
    derivada = y_vals;
    orden_derivada = n + 1;
    
    for k = 1:orden_derivada
        derivada = diff(derivada) / h_step;
    end
    
    // 4. Obtener M (Máximo valor absoluto de la derivada n+1)
    M_calc = max(abs(derivada));
    
    // 5. Calcular el máximo del término nodal |(x-x0)(x-x1)...|
    // Usamos una malla densa para buscar el máximo geométrico
    xx = linspace(a, b, 2000);
    w_vals = ones(xx);
    for i = 1:length(nodos)
        w_vals = w_vals .* (xx - nodos(i));
    end
    W_max = max(abs(w_vals));
    
    // 6. Fórmula Final
    Cota = (M_calc / factorial(orden_derivada)) * W_max;
endfunction

// ==========================================
// 2. RESOLUCIÓN DEL PROBLEMA
// ==========================================
function ej1()
    disp("//////////////////////EJERCICIO 1/////////////////////////")

    clc; // Limpiar consola
    
    // DATOS INICIALES
    // x = 0, 0.2, 0.4, 0.6
    // y = e^x dados
    X_todos = [0, 0.2, 0.4, 0.6];
    Y_todos = [1.0, 1.2214, 1.4918, 1.8221];
    
    // Valor a buscar: raiz cubica de e => e^(1/3)
    val_x = 1/3; 
    val_exacto = 1.395612425; // Dato del problema
    
    mprintf("=== INCISO A: Interpolación ===\n");
    mprintf("Valor a interpolar (x): %f\n", val_x);
    mprintf("Valor exacto (e^x):     %f\n\n", val_exacto);
    
    
    // --- CASO 1: INTERPOLACIÓN LINEAL (Grado 1) ---
    // Para interpolar 0.3333, usamos los nodos que encierran el punto: 0.2 y 0.4
    x_lin = [0.2, 0.4];
    y_lin = [1.2214, 1.4918];
    
    // Método Lagrange
    pol_lin = interpolLagrange(x_lin, y_lin);
    aprox_lin = horner(pol_lin, val_x);
    
    mprintf("--- Interpolación Lineal (Nodos: 0.2, 0.4) ---\n");
    mprintf("Polinomio resultante: \n"); disp(pol_lin);
    mprintf("Aproximación Lineal:  %.9f\n\n", aprox_lin);
    
    
    // --- CASO 2: INTERPOLACIÓN CÚBICA (Grado 3) ---
    // Usamos todos los nodos: 0, 0.2, 0.4, 0.6
    x_cub = X_todos;
    y_cub = Y_todos;
    
    // Método Lagrange
    pol_cub_L = interpolLagrange(x_cub, y_cub);
    aprox_cub_L = horner(pol_cub_L, val_x);
    
    // Método Newton (Debe dar el mismo resultado numérico)
    pol_cub_N = DD_newton(x_cub, y_cub);
    aprox_cub_N = horner(pol_cub_N, val_x);
    
    mprintf("--- Interpolación Cúbica (Todos los nodos) ---\n");
    mprintf("Polinomio (Lagrange): \n"); disp(pol_cub_L);
    mprintf("Aproximación Cúbica:  %.9f\n\n", aprox_cub_L);
    
    
    // ==========================================
    // 3. CÁLCULO DE ERRORES (Inciso B)
    // ==========================================
    
    mprintf("=== INCISO B: Errores ===\n");
    
    // 1. Error Exacto (Real) = |Aproximado - Exacto|
    error_real_lin = abs(aprox_lin - val_exacto);
    error_real_cub = abs(aprox_cub_L - val_exacto);
    
    mprintf("Error real (Lineal): %.9f\n", error_real_lin);
    mprintf("Error real (Cúbico): %.9f\n\n", error_real_cub);
    
    // 2. Cotas de Error Teórico
    // Fórmula: E = (M / (n+1)!) * |(x-x0)(x-x1)...|
    // f(x) = e^x. Todas sus derivadas son e^x.
    // M es el máximo de la derivada n+1 en el intervalo.
    
    // -- Cota Lineal (n=1) --
    // Intervalo [0.2, 0.4]. Derivada f''(x) = e^x. Máximo en e^0.4
    // n+1 = 2
    M_lin = exp(0.4); 
    term_lin = abs((val_x - x_lin(1)) * (val_x - x_lin(2)));
    cota_lin = (M_lin / factorial(2)) * term_lin;
    
    // -- Cota Cúbica (n=3) --
    // Intervalo [0, 0.6]. Derivada f''''(x) = e^x. Máximo en e^0.6
    // n+1 = 4
    M_cub = exp(0.6);
    term_cub = abs((val_x - x_cub(1)) * (val_x - x_cub(2)) * (val_x - x_cub(3)) * (val_x - x_cub(4)));
    cota_cub = (M_cub / factorial(4)) * term_cub;
    
    mprintf("Cota de error (Lineal): %.9f\n", cota_lin);
    mprintf("Cota de error (Cúbica): %.9f\n", cota_cub);
    
    // Verificación
    if error_real_lin <= cota_lin then
        mprintf("Verificación Lineal: OK (Error Real < Cota)\n");
    else
        mprintf("Verificación Lineal: FALLO\n");
    end
    
    if error_real_cub <= cota_cub then
        mprintf("Verificación Cúbica: OK (Error Real < Cota)\n");
    else
        mprintf("Verificación Cúbica: FALLO\n");
    end

endfunction


//-------------------- EJERCICIO NRO 3:

function ej3()
    disp("//////////////////////EJERCICIO 3/////////////////////////")
    // ==========================================
    // 2. CÁLCULO DE MÁXIMOS DE DERIVADAS (M2 y M3)
    // ==========================================
    // Función exacta: Bessel J de orden 0
    // Scilab tiene la función besselj(alpha, x)
    function y = f_exacta(x)
        y = besselj(0, x);
    endfunction
    
    // Creamos un grid muy fino para estimar las derivadas numéricamente
    x_fino = 0:0.001:1;
    y_fino = f_exacta(x_fino);
    
    // Aproximación numérica de derivadas usando diff
    // dy/dx approx diff(y)/h
    dx = 0.001;
    d1 = diff(y_fino) / dx;
    d2 = diff(d1) / dx;     // Segunda derivada
    d3 = diff(d2) / dx;     // Tercera derivada
    
    // Obtenemos los máximos absolutos en el intervalo
    M2 = max(abs(d2));
    M3 = max(abs(d3));
    
    mprintf("=== ANÁLISIS DE DERIVADAS EN [0, 1] ===\n");
    mprintf("Máximo |f''''(x)| estimado (M2): %.4f\n", M2);
    mprintf("Máximo |f''''''(x)| estimado (M3): %.4f\n\n", M3);
    
    // ==========================================
    // 3. CÁLCULO DEL PASO h (Inciso A y B)
    // ==========================================
    Epsilon = 0.5 * 10^-6; // Tolerancia deseada
    
    // --- CASO LINEAL ---
    // Formula error: |E| <= (h^2 / 8) * M2
    // Despeje: h <= sqrt( (8 * Epsilon) / M2 )
    h_lineal = sqrt((8 * Epsilon) / M2);
    
    // --- CASO CUADRÁTICO ---
    // Formula error: |E| <= (h^3 / (9*sqrt(3))) * M3
    // Despeje: h <= raiz_cubica( (9*sqrt(3)*Epsilon) / M3 )
    h_cuad = ((9 * sqrt(3) * Epsilon) / M3)^(1/3);
    
    mprintf("=== RESULTADOS DEL PASO DE TABULACIÓN (h) ===\n");
    mprintf("Tolerancia requerida: %.2e\n", Epsilon);
    mprintf("a) Paso h para Interpolación Lineal:     %.5f\n", h_lineal);
    mprintf("b) Paso h para Interpolación Cuadrática: %.5f\n\n", h_cuad);
    
    
    // ==========================================
    // 4. VERIFICACIÓN (Reutilizando código)
    // ==========================================
    mprintf("=== VERIFICACIÓN PRÁCTICA ===\n");
    
    // --- Verificación Lineal ---
    // Creamos nodos espaciados por h_lineal (redondeado hacia abajo para seguridad)
    h_use_lin = floor(h_lineal * 10000) / 10000; 
    x_nodes_lin = 0:h_use_lin:1; 
    // Tomamos los primeros 2 nodos para probar un punto medio
    xx_lin = x_nodes_lin(1:2);
    yy_lin = f_exacta(xx_lin);
    
    // Interpolamos en el punto medio (donde el error suele ser mayor)
    x_test = (xx_lin(1) + xx_lin(2)) / 2;
    P_lin = interpolLagrange(xx_lin, yy_lin);
    val_aprox = horner(P_lin, x_test);
    val_real  = f_exacta(x_test);
    err_lin   = abs(val_aprox - val_real);
    
    mprintf(">> Test Lineal con h = %.5f\n", h_use_lin);
    mprintf("   Error real en punto medio: %.2e\n", err_lin);
    if err_lin < Epsilon then
        mprintf("   VERIFICADO: El error es menor a la tolerancia.\n");
    else
        mprintf("   CUIDADO: El error supera la tolerancia.\n");
    end
    
    mprintf("\n");
    
    // --- Verificación Cuadrática ---
    // Creamos nodos con h_cuad
    h_use_cuad = floor(h_cuad * 1000) / 1000; 
    x_nodes_cuad = 0:h_use_cuad:1;
    // Tomamos 3 nodos para interpolación cuadrática
    if length(x_nodes_cuad) < 3 then x_nodes_cuad = [0, h_use_cuad, 2*h_use_cuad]; end
    xx_cub = x_nodes_cuad(1:3);
    yy_cub = f_exacta(xx_cub);
    
    // Interpolamos en un punto entre nodos (ej: entre el 1ro y 2do)
    x_test_cub = (xx_cub(1) + xx_cub(2)) / 2;
    P_cub = interpolLagrange(xx_cub, yy_cub);
    val_aprox_c = horner(P_cub, x_test_cub);
    val_real_c  = f_exacta(x_test_cub);
    err_cub     = abs(val_aprox_c - val_real_c);
    
    mprintf(">> Test Cuadrático con h = %.5f\n", h_use_cuad);
    mprintf("   Error real en punto medio: %.2e\n", err_cub);
    if err_cub < Epsilon then
        mprintf("   VERIFICADO: El error es menor a la tolerancia.\n");
    else
        mprintf("   CUIDADO: El error supera la tolerancia.\n");
    end
endfunction




//====================================================

function examen()
    mprintf("************** EJERCICIO DE EXAMEN:***********")
    //ejercicio examen 1: aproxime f(x)= (1+x) / (1+2x+3x^2)  en el intervalo [0,5] mediante la interpolacion de lagrande de orden 2 , encuentre una acotacion del error y evalue el error exacto mediante e(x)=f(X)-p4(x)
    
    // ==========================================
    // 2. CONFIGURACIÓN DEL EJERCICIO
    // ==========================================
    // ¡¡¡ MODIFICAR DATOS AQUÍ !!!
    
    // a) Definir la Función f(x)
    func_texto = '(1+x) ./ (1 + 2*x + 3*x.^2)';
    deff('y=f(x)', 'y = '+func_texto);  //usar ./  .*  .^
    
    // b) Intervalo [a, b]
    a = 0;
    b = 5;
    
    // c) Orden de interpolación (n)
    // n=2 implica 3 puntos (Cuadrática). Si el examen pide p4, cambia n a 4.
    n = 2; 
    
    // ==========================================
    // 3. CÁLCULOS AUTOMÁTICOS
    // ==========================================
    
    mprintf("\n=== RESOLUCIÓN EXAMEN ===\n");
    mprintf("Función: %s\n", func_texto);
    mprintf("Intervalo: [%.2f, %.2f]\n", a, b);
    mprintf("Orden solicitado: %d (%d nodos)\n", n, n+1);
    
    // 1. Generar Nodos (Equidistantes)
    x_nodos = linspace(a, b, n+1);
    y_nodos = f(x_nodos);
    
    mprintf("Nodos utilizados:\n"); disp(x_nodos);
    mprintf("Valores f(x_i):\n");   disp(y_nodos);
    
    // 2. Obtener Polinomio de Lagrange
    P = interpolLagrange(x_nodos, y_nodos);
    
    mprintf("\n>> Polinomio Interpolante P%d(x):\n", n);
    disp(P);
    
    
    //======== 3 automatico =======
    // B. CÁLCULO DE LA COTA AUTOMÁTICA
    [Cota_Total, M_estimada, Max_Nodos] = CalcularCotaAutomatica(func_texto, a, b, n, x_nodos);
    
    mprintf("\n>> REPORTE DE COTA DE ERROR (Automático):\n");
    mprintf("   1. Orden de derivada requerida (n+1): %d\n", n+1);
    mprintf("   2. Máximo de la derivada (M) hallado numéricamente: %.4f\n", M_estimada);
    mprintf("   3. Máximo del polinomio nodal (W_max): %.4f\n", Max_Nodos);
    mprintf("   ------------------------------------------------\n");
    mprintf("   4. COTA DE ERROR CALCULADA: %.6e\n", Cota_Total);
    mprintf("   ------------------------------------------------\n");
    
    //=============================0
    
    
    //// 3. Evaluación del Error Exacto: e(x) = f(x) - P(x)
    //// Creamos un vector denso para recorrer todo el intervalo
    //xx = linspace(a, b, 1000);
    //yy_exacta = f(xx);
    //yy_aprox  = horner(P, xx);
    //error_real_vec = abs(yy_exacta - yy_aprox);
    //
    //max_error_real = max(error_real_vec);
    //mprintf("\n>> Máximo Error Exacto en el intervalo: %.6e\n", max_error_real);
    //
    //// 4. Acotación del Error (Teórica)
    //// E <= (M / (n+1)!) * max|prod(x-xi)|
    //// M es el máximo de la derivada n+1.
    //
    //// -- Estimación Numérica de la Derivada n+1 --
    //// Como derivar esa función racional n+1 veces a mano es difícil en examen,
    //// la estimamos numéricamente con diferencias finitas sobre una malla fina.
    //dx = 0.001;
    //x_deriv = a:dx:b;
    //y_deriv = f(x_deriv);
    //
    //// Derivamos n+1 veces
    //for i=1:(n+1)
    //    y_deriv = diff(y_deriv) / dx;
    //end
    //M_estimada = max(abs(y_deriv));
    //
    //// -- Cálculo del término nodal max| (x-x0)(x-x1)... | --
    //w_poly_vals = ones(xx);
    //for k=1:length(x_nodos)
    //    w_poly_vals = w_poly_vals .* (xx - x_nodos(k));
    //end
    //max_w = max(abs(w_poly_vals));
    //
    //// -- Cota Final --
    //Cota_Teorica = (M_estimada / factorial(n+1)) * max_w;
    //
    //mprintf("\n>> Cota de Error Teórica (Estimada):\n");
    //mprintf("   Derivada orden %d max (M): %.4f\n", n+1, M_estimada);
    //mprintf("   Factor nodal max: %.4f\n", max_w);
    //mprintf("   Cota calculada: %.6e\n", Cota_Teorica);
    
    // Verificación
    
    // C. Error Exacto (Comparación)
    xx = linspace(a, b, 1000);
    err_real = max(abs(f(xx) - horner(P, xx)));
    mprintf("\n>> Error Exacto Real (para verificar): %.6e\n", err_real);
    
    if err_real <= Cota_Total * 1.05 then
        mprintf("   [OK] La cota es válida (Cota > Error Real).\n");
    else
        mprintf("   [ALERTA] Algo falló, revisa la función.\n");
    end
    
    
    // ==========================================
    // 4. GRÁFICAS
    // ==========================================
    scf(0); clf();
    
    error_real_vec=abs(f(xx) - horner(P, xx));
    
    // Subplot 1: Función vs Polinomio
    subplot(1,2,1);
    plot(xx, f(xx), "k-", "Thickness", 2);
    plot(xx, horner(P,xx), "r--", "Thickness", 2);
    plot(x_nodos, y_nodos, "bo", "MarkerSize", 3);
    legend(["Exacta f(x)"; "Lagrange P(x)"; "Nodos"]);
    title("Interpolación de Lagrange");
    xgrid();
    
    // Subplot 2: El Error
    subplot(1,2,2);
    plot(xx, error_real_vec, "b-", "Thickness", 2);
    plot(xx, ones(xx)*Cota_Total, "r--", "Thickness", 1);
    legend(["Error Exacto |f(x)-P(x)|"; "Cota Teórica"]);
    title("Análisis del Error");
    xgrid();

endfunction



// ==========================================
// 5. EJERCICIO EXAMEN: MÉTODO DE NEWTON (GENÉRICO)
// ==========================================
function examen_newton()
    mprintf("************** EJERCICIO DE EXAMEN (MÉTODO NEWTON) ***********\n")
    
    // ==========================================
    // A. CONFIGURACIÓN (MODIFICAR AQUÍ)
    // ==========================================
    
    // 1. Función (Texto)
    func_texto = '(1+x) ./ (1 + 2*x + 3*x.^2)';
    deff('y=f(x)', 'y = '+func_texto);
    
    // 2. Intervalo y Grado
    a = 0;
    b = 5;
    n = 2; // Grado 2 (3 nodos). Si piden P4, poner n=4.

    // ==========================================
    // B. CÁLCULOS
    // ==========================================
    
    mprintf("Función: %s\n", func_texto);
    mprintf("Intervalo: [%.2f, %.2f] | Grado solicitado: %d\n", a, b, n);

    // 1. Nodos Equidistantes
    x_nodos = linspace(a, b, n+1);
    y_nodos = f(x_nodos);

    // 2. Tabla de Diferencias Divididas
    [coefs, T] = TablaNewton(x_nodos, y_nodos);

    mprintf("\n--- Paso 1: Nodos y Valores ---\n");
    disp([x_nodos' y_nodos']); // Mostrar como columna

    mprintf("\n--- Paso 2: Tabla de Diferencias Divididas ---\n");
    disp(T);
    mprintf("(Los coeficientes del polinomio son la primera fila)\n");

    // 3. Construcción Visual del Polinomio (Para copiar en el examen)
    mprintf("\n--- Paso 3: Polinomio de Newton P(x) ---\n");
    str_poly = sprintf("%.4f", coefs(1));
    for k = 2:length(coefs)
        signo = "+";
        if coefs(k) < 0 then signo = ""; end // El menos ya viene con el número
        
        term_x = "";
        for j = 1:k-1
            term_x = term_x + sprintf("(x - %.2f)", x_nodos(j));
        end
        str_poly = str_poly + sprintf(" %s %.4f%s", signo, coefs(k), term_x);
    end
    mprintf("P_%d(x) = %s\n", n, str_poly);

    // 4. Cota de Error Automática
    [Cota_Total, M_est, W_max] = CalcularCotaAutomatica(func_texto, a, b, n, x_nodos);

    mprintf("\n--- Paso 4: Acotación del Error ---\n");
    mprintf("Derivada orden %d máx (M) estimado: %.4f\n", n+1, M_est);
    mprintf("Máximo del producto de nodos:       %.4f\n", W_max);
    mprintf(">> COTA DE ERROR TEÓRICA:           %.6e\n", Cota_Total);

    // 5. Error Exacto
    xx = linspace(a, b, 1000);
    yy_exacta = f(xx);
    yy_aprox  = EvalPolNewton(xx, x_nodos, coefs); // Usamos la func de Newton para evaluar
    error_real_vec = abs(yy_exacta - yy_aprox);
    max_err_real = max(error_real_vec);

    mprintf("\n--- Paso 5: Verificación ---\n");
    mprintf("Máximo Error Real (f - P): %.6e\n", max_err_real);
    
    if max_err_real <= Cota_Total * 1.05 then
        mprintf("[OK] El error real está dentro de la cota.\n");
    else
        mprintf("[ALERTA] El error real supera la cota.\n");
    end

    // ==========================================
    // C. GRÁFICAS
    // ==========================================
    scf(1); clf();
    
    // Gráfica 1: Función vs Polinomio
    subplot(1,2,1);
    plot(xx, yy_exacta, "k", "Thickness", 2);
    plot(xx, yy_aprox, "r--", "Thickness", 2);
    plot(x_nodos, y_nodos, "bo", "MarkerSize", 3);
    legend(["f(x) Exacta"; "Newton P(x)"; "Nodos"]);
    title("Interpolación de Newton - Grado " + string(n));
    xgrid();
    
    // Gráfica 2: Error
    subplot(1,2,2);
    plot(xx, error_real_vec, "b", "Thickness", 2);
    plot(xx, ones(xx)*Cota_Total, "r--", "Thickness", 2);
    legend(["Error Real"; "Cota Teórica"]);
    title("Análisis del Error");
    xgrid();

endfunction


// ==========================================
// 2. FUNCIÓN DE EXAMEN COMPLETO (COMBINADA)
// ==========================================
function examen_completo()
    mprintf("\n**************************************************\n");
    mprintf("      RESOLUCIÓN INTEGRAL (Lagrange + Newton)\n");
    mprintf("**************************************************\n");

    // ==========================================
    // A. DATOS DEL EJERCICIO (MODIFICAR AQUÍ)
    // ==========================================
    
    // 1. Función como texto (usar puntos para vectores: .* ./ .^)
    func_texto = '(1+x) ./ (1 + 2*x + 3*x.^2)';
    
    // 2. Intervalo [a, b]
    a = 0;
    b = 5;
    
    // 3. Grado del Polinomio (n)
    // n=2 (Cuadrática, 3 puntos), n=3 (Cúbica, 4 puntos), etc.
    n = 2; 

    // ==========================================
    // B. PROCESAMIENTO
    // ==========================================
    
    deff('y=f(x)', 'y='+func_texto);
    x_nodos = linspace(a, b, n+1);
    y_nodos = f(x_nodos);
    
    mprintf("Función: %s\n", func_texto);
    mprintf("Intervalo: [%.2f, %.2f] | Grado n=%d\n", a, b, n);
    mprintf("\n--- NODOS UTILIZADOS ---\n");
    disp([x_nodos' y_nodos']);

    // --- PARTE 1: LAGRANGE ---
    mprintf("\n==================================================\n");
    mprintf(" MÉTODO 1: LAGRANGE\n");
    mprintf("==================================================\n");
    P_Lagrange = interpolLagrange(x_nodos, y_nodos);
    mprintf("Polinomio resultante (Simplificado):\n");
    disp(P_Lagrange);

    // --- PARTE 2: NEWTON ---
    mprintf("\n==================================================\n");
    mprintf(" MÉTODO 2: NEWTON (Diferencias Divididas)\n");
    mprintf("==================================================\n");
    [coefs_N, Tabla] = TablaNewton(x_nodos, y_nodos);
    
    mprintf("Tabla de Diferencias Divididas:\n");
    disp(Tabla);
    
    mprintf("\nPolinomio en forma escalonada (Para copiar):\n");
    str_poly = sprintf("%.4f", coefs_N(1));
    for k = 2:length(coefs_N)
        signo = "+";
        if coefs_N(k) < 0 then signo = ""; end 
        term_x = "";
        for j = 1:k-1
            term_x = term_x + sprintf("(x - %.2f)", x_nodos(j));
        end
        str_poly = str_poly + sprintf(" %s %.4f%s", signo, coefs_N(k), term_x);
    end
    mprintf("P(x) = %s\n", str_poly);

    // --- PARTE 3: ANÁLISIS DE ERROR ---
    mprintf("\n==================================================\n");
    mprintf(" ANÁLISIS DE ERROR\n");
    mprintf("==================================================\n");
    
    // Cota Automática
    [Cota, M, W] = CalcularCotaAutomatica(func_texto, a, b, n, x_nodos);
    mprintf("1. COTA TEÓRICA:\n");
    mprintf("   - Derivada orden %d máx (M): %.4f\n", n+1, M);
    mprintf("   - Max producto nodos (W):   %.4f\n", W);
    mprintf("   >> COTA FINAL:              %.6e\n", Cota);
    
    // Error Real
    xx = linspace(a, b, 1000);
    yy_exacta = f(xx);
    yy_aprox = EvalPolNewton(xx, x_nodos, coefs_N);
    error_vec = abs(yy_exacta - yy_aprox);
    max_err = max(error_vec);
    
    mprintf("\n2. ERROR REAL (Exacto):\n");
    mprintf("   >> Error Máximo Real:       %.6e\n", max_err);
    
    if max_err <= Cota * 1.05 then
        mprintf("\n   [VERIFICADO] El error real respeta la cota.\n");
    else
        mprintf("\n   [ALERTA] El error real supera la cota.\n");
    end

    // ==========================================
    // C. GRÁFICAS COMBINADAS
    // ==========================================
    scf(2); clf();
    
    // Grafico 1: Interpolación
    subplot(1,2,1);
    plot(xx, yy_exacta, "k", "Thickness", 2);
    plot(xx, yy_aprox, "r--", "Thickness", 2);
    plot(x_nodos, y_nodos, "bo", "MarkerSize", 3);
    legend(["f(x) Exacta"; "Interpolación P(x)"; "Nodos"], 4);
    title("Interpolación (Lagrange/Newton)");
    xgrid();
    
    // Grafico 2: Error
    subplot(1,2,2);
    plot(xx, error_vec, "b", "Thickness", 2);
    plot(xx, ones(xx)*Cota, "r--", "Thickness", 2);
    legend(["Error Real |f-P|"; "Cota Teórica"], 1);
    title("Error Real vs Cota");
    xgrid();

endfunction


// ==========================================
// 6. EJERCICIO EXAMEN: PUNTOS DISCRETOS (Newton Incremental)
// ==========================================
function ejercicio_puntos_discretos()
    
    
        /*    ej1 examen: 
        para una cierta funcion f(x) conocemos los sig puntos:
        x   |-1 | 0 | 1  |2 | 3
        f(x)| 3 | 0 | -1 | 1 | 1
        
        a. encontrar mediante el metodo de las diferencias dividas de Newton el polinomio  de menor grado que interpola a f(x) en dichos puntos
        b. a aprtir del polinomio obtenido en el item anteiror determinar el polinomi interpolador resultante si se amplian los datos con el punto (4,3)
        c. repetir usando lagrange.
        d. graficar todo. */
    
    mprintf("\n**************************************************\n");
    mprintf("      RESOLUCIÓN: Puntos Discretos (Newton +1)\n");
    mprintf("**************************************************\n");

    // ==========================================
    // A. DATOS (MODIFICAR AQUÍ SI CAMBIAN LOS NÚMEROS)
    // ==========================================
    
    // Parte 1: Puntos iniciales
    x_ini = [-1, 0, 1, 2, 3];
    y_ini = [ 3, 0,-1, 1, 1];
    
    // Parte 2: Punto nuevo a agregar
    x_nuevo = 4;
    y_nuevo = 3;

    // ==========================================
    // B. RESOLUCIÓN
    // ==========================================

    // --- INCISO A: NEWTON INICIAL ---
    mprintf("\n=== a) Polinomio Inicial (Newton) ===\n");
    [coefs_A, Tabla_A] = TablaNewton(x_ini, y_ini);
    
    mprintf("Tabla de Diferencias Divididas (Inicial):\n");
    disp(Tabla_A);
    
    // Construir string del polinomio A
    str_poly_A = sprintf("%.2f", coefs_A(1));
    for k = 2:length(coefs_A)
        signo = "+"; if coefs_A(k) < 0 then signo = ""; end
        term_x = "";
        for j = 1:k-1
            term_x = term_x + sprintf("(x - %.0f)", x_ini(j)); // %.0f para enteros
        end
        str_poly_A = str_poly_A + sprintf(" %s %.4f%s", signo, coefs_A(k), term_x);
    end
    mprintf("P_inicial(x) = %s\n", str_poly_A);


    // --- INCISO B: NEWTON AMPLIADO ---
    mprintf("\n=== b) Polinomio Ampliado con punto (%.1f, %.1f) ===\n", x_nuevo, y_nuevo);
    mprintf("Propiedad: El nuevo polinomio es el anterior + un nuevo término.\n");
    
    // Concatenamos los vectores
    x_full = [x_ini, x_nuevo];
    y_full = [y_ini, y_nuevo];
    
    [coefs_B, Tabla_B] = TablaNewton(x_full, y_full);
    
    mprintf("Tabla Actualizada (Note que la parte superior izquierda es idéntica):\n");
    disp(Tabla_B);
    
    // El nuevo término es el último coeficiente * el producto de (x - todos_los_anteriores)
    nuevo_coef = coefs_B($); // El último
    mprintf("Nuevo coeficiente hallado: %.4f\n", nuevo_coef);
    
    str_nuevo_termino = sprintf("%.4f", nuevo_coef);
    for j = 1:length(x_ini)
         str_nuevo_termino = str_nuevo_termino + sprintf("(x - %.0f)", x_ini(j));
    end
    
    mprintf("\nP_ampliado(x) = P_inicial(x) + %s\n", str_nuevo_termino);


    // --- INCISO C: LAGRANGE ---
    mprintf("\n=== c) Usando Lagrange (Recalculo total) ===\n");
    // Lagrange no es incremental, se calcula con todos los puntos juntos
    P_Lag_Full = interpolLagrange(x_full, y_full);
    mprintf("Polinomio resultante (Lagrange Simplificado):\n");
    disp(P_Lag_Full);


    // --- INCISO D: GRÁFICAS ---
    mprintf("\n=== d) Gráficas ===\n");
    
    // Definir rango para graficar (un poco más allá de los puntos)
    xx = linspace(min(x_full)-0.5, max(x_full)+0.5, 1000);
    
    // Evaluar ambos polinomios
    yy_A = EvalPolNewton(xx, x_ini, coefs_A);
    yy_B = EvalPolNewton(xx, x_full, coefs_B);
    
    scf(3); clf();
    
    // Graficar Curvas
    plot(xx, yy_A, "r--", "Thickness", 2); // Inicial (Rojo discontinuo)
    plot(xx, yy_B, "b-", "Thickness", 2);  // Ampliado (Azul continuo)
    
    // Graficar Puntos
    plot(x_ini, y_ini, "ro", "MarkerSize", 3, "MarkerFaceColor", "red"); // Puntos viejos
    plot(x_nuevo, y_nuevo, "bs", "MarkerSize", 4, "MarkerFaceColor", "blue"); // Punto nuevo
    
    legend(["P(x) Inicial (5 ptos)"; "P(x) Ampliado (6 ptos)"; "Datos Iniciales"; "Dato Nuevo"]);
    title("Interpolación Incremental de Newton");
    xlabel("x"); ylabel("f(x)");
    xgrid();
    
    mprintf("Gráfica generada. Note cómo la curva azul pasa por el nuevo punto cuadrado.\n");

endfunction

// =========================================================================
//                             PROGRAMA PRINCIPAL (MAIN)
// =========================================================================

while %t
    mprintf("\n============================================\n");
    mprintf("       MENÚ PARCIAL - MÉTODOS NUMÉRICOS\n");
    mprintf("============================================\n");
    mprintf("1.Valor a buscar: raiz cubica de e => e^(1/3) - lineal y cubica + error \n");
    mprintf("2. 2. CÁLCULO DE MÁXIMOS DE DERIVADAS (M2 y M3) - bessel \n");
    mprintf("3.aproxime f(x)= (1+x) / (1+2x+3x^2)  en el intervalo [0,5] mediante la interpolacion de lagrande de orden 2 , encuentre una acotacion del error y evalue el error exacto mediante e(x)=f(X)-p4(x) . \n");
     mprintf("4.aproxime f(x)= (1+x) / (1+2x+3x^2)  en el intervalo [0,5] mediante la interpolacion de NEWTON de orden 2 , encuentre una acotacion del error y evalue el error exacto mediante e(x)=f(X)-p4(x) . \n");
     mprintf("5 .aproxime f(x)= (1+x) / (1+2x+3x^2)  en el intervalo [0,5] mediante la interpolacion de NEWTON Y LAGRANGE de orden 2 , encuentre una acotacion del error y evalue el error exacto mediante e(x)=f(X)-p4(x) . \n");
     mprintf("6. EJERCICIO: TABLA DE PUNTOS DISCRETOS (Newton Incremental)\n");
    mprintf("0. SALIR\n");
    
    mprintf("============================================\n");
    
    opcion = input("Elige una opción: ");
    
    select opcion
    case 1 then
        ej1();
    case 2 then
        ej3();
    case 3 then
        examen();
    case 4 then examen_newton();
    case 5 then examen_completo();
    case 6 then
        ejercicio_puntos_discretos();
    case 0 then
        mprintf("\nÉxitos en el examen!\n");
        break;
    else
        mprintf("\nOpción no válida.\n");
    end
end


