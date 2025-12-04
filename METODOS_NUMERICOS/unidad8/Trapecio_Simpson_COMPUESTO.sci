// ==========================================
// 0. HERRAMIENTAS DE CÁLCULO DE COTAS 
// ==========================================

// Calcula derivada numérica de orden 'orden' en el punto 'x'
function d = DerivadaNum(f, x, orden)
    h = 0.001; 
    if orden == 2 then
        d = (f(x+h) - 2*f(x) + f(x-h)) / h^2;
    elseif orden == 4 then
        d = (f(x+2*h) - 4*f(x+h) + 6*f(x) - 4*f(x-h) + f(x-2*h)) / h^4;
    else
        d = 0; // Por seguridad
    end
endfunction

// Busca el máximo valor absoluto de la derivada en [a, b]
function M = ObtenerCotaMaxima(f, a, b, orden)
    // Definimos qué consideramos "Infinito" numéricamente
    UMBRAL_GIGANTE = 10000; 
    
    // Muestreamos evitando los bordes exactos por si hay división por cero
    // Usamos logspace cerca de los bordes si a=0 para detectar mejor la subida
    puntos = linspace(a + 1e-4, b - 1e-4, 500);
    
    max_val = 0;
    es_infinito = %f; // Bandera falsa/verdadero
    
    for x_val = puntos
        // Intentamos calcular derivada
        try
            d = abs(DerivadaNum(f, x_val, orden));
        catch
            d = UMBRAL_GIGANTE + 1; // Si falla el cálculo, asumimos singularidad
        end
        
        // Verificamos si es "Gigante", Infinito o NaN (Not a Number)
        if d > UMBRAL_GIGANTE | isinf(d) | isnan(d) then
            es_infinito = %t;
            break; // Cortamos el bucle, ya sabemos que explota
        end
        
        if d > max_val then max_val = d; end
    end
    
    if es_infinito then
        M = %inf; // Devolvemos el objeto "Infinito" de Scilab
    else
        M = max_val;
    end
endfunction



// ==========================================
// 1. DEFINICIÓN DE FUNCIONES 
// ==========================================


//Regla del trapecio compuesto
function w = trapecio_comp(f, a, b, n) //n = cant. de intervalos
    h = (b - a)/n; //longitud de cada intervalo
    w = (f(a) + f(b))/2;
    for (i = 1 : n-1)
        x = a + h*i;
        w = w + f(x);
    end
    w = w*h;
endfunction


//Regla de Simpson compuesta
function w = simpson_comp(f, a, b, n)
    // Validación: n debe ser par para Simpson
    if modulo(n, 2) <> 0 then
        error("El número de intervalos n debe ser PAR para la regla de Simpson.");
    end
    
    h = (b - a)/n;
    w = f(a) + f(b);
    for i = 1 : n-1
        x = a + h*i;
        if modulo(i, 2) == 0 then
            w = w + 2*f(x);
        else
            w = w + 4*f(x);
        end
    end
    w = w*h/3;
endfunction




// ==========================================
// 2. FUNCIONES MATEMÁTICAS DEL EJERCICIO 2 - 4
// ==========================================
function y = f2a(x), y = 1/x, endfunction
function y = f2b(x), y = x^3, endfunction
function y = f2c(x), y = x * (1 + x^2)^(1/2), endfunction
function y = f2d(x), y = sin(%pi * x), endfunction
function y = f2e(x), y = x * sin(x), endfunction
function y = f2f(x), y = x^2 * exp(x), endfunction

// Definición de la función: f(x) = (x + 1)^(-1)
function y = f4(x)
    y = 1 / (x + 1);
endfunction

function y = f_examen(x)
    y = exp(x) * sin(x); //(e^x sin(x))  EJ2_PC
endfunction

function y = f_Si(x)
    y = sin(x) / x;  //EJ3_PC
endfunction

function y = f_examen_1(x)
    y = x / (x^2 + 4);
endfunction

//==********* FUNCION AUXILIAR COTAS:********=
// Función auxiliar para imprimir resultados repetitivos
    function analizar_caso_T(f, a, b, n, nombre)
        aprox = trapecio_comp(f, a, b, n);
        real = intg(a, b, f);
        err_real = abs(real - aprox);
        
        // Cota Teórica Trapecio (Usa derivada 2da)
        M2 = ObtenerCotaMaxima(f, a, b, 2);
        if isinf(M2) then 
            cota = %inf
        else 
            cota = ((b-a)^3 / (12 * n^2)) * M2
        end
        
        mprintf("\n%s [n=%d]\n", nombre, n);
        mprintf("   Aprox: %.8f | Exacto: %.8f\n", aprox, real);
        mprintf("   Error Real:   %.2e\n", err_real);
        
        if isinf(cota) then
        mprintf("   Cota Teórica: NO EXISTE (Derivada -> Inf)\n");
    else
        mprintf("   Cota Teórica: %.2e (M2 approx: %.2f)\n", cota, M2);
    
        if err_real <= cota * 1.01 then // 1.01 margen por error numérico
             mprintf("   >> Verificación: OK (Error < Cota)\n");
        else mprintf("   >> Verificación: REVISAR\n"); end
    end
endfunction


function analizar_caso_simpson(f, a, b, n, nombre)
        aprox = simpson_comp(f, a, b, n);
        real = intg(a, b, f);
        err_real = abs(real - aprox);
        
        // Cota Teórica Simpson (Usa derivada 4ta)
        M4 = ObtenerCotaMaxima(f, a, b, 4);
        if isinf(M4) then cota = %inf; else cota = ((b-a)^5 / (180 * n^4)) * M4; end
        
        mprintf("\n%s [n=%d]\n", nombre, n);
        mprintf("   Aprox: %.8f | Exacto: %.8f\n", aprox, real);
        mprintf("   Error Real:   %.2e\n", err_real);
        
        if isinf(cota) then
            mprintf("   Cota Teórica: NO EXISTE (Derivada -> Inf)\n")
        // Caso especial para polinomios cubicos donde derivada 4ta es 0 teoricamente
        elseif M4 < 1e-9 then 
            mprintf("   Cota Teórica: 0.00e+00 (Exacto para grado <= 3)\n")
        else
            mprintf("   Cota Teórica: %.2e (M4 approx: %.2f)\n", cota, M4)
            
            if err_real <= cota * 1.01 + 1e-14 then 
                mprintf("   >> Verificación: OK\n")
            else 
                mprintf("   >> Verificación: REVISAR\n")
            end
        end

        
endfunction
    
    

// ==========================================
// 3. LÓGICA DEL EJERCICIO 1
// ==========================================    

function ejercicio1()
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO 1: ln(2) = Int(1/x) en [1, 2]\n");
    mprintf("=================================================\n");
    
    a = 1; b = 2;
    // Usamos f2a (que es 1/x) ya definida
    
    
    // -----------------------------------------------------
    // PARTE 1: TRAPECIO
    // -----------------------------------------------------
    mprintf("\n--- 1) MÉTODO TRAPECIO ---\n");
    
    
    // --- INCISO A : Aproximación de In(2) con n=4---
    n = 4;
    aprox = trapecio_comp(f2a, a, b, n);
    val_real = log(2);
    mprintf("\na) Aproximación Trapecio (n=4):\n");
    mprintf("   Aprox: %.8f | Real (ln 2): %.8f\n", aprox, val_real);
    mprintf("   Error: %.2e\n", abs(val_real - aprox));
    
    // --- INCISO B: Determinar n necesaria para que error < 10^6 ---
    tol = 10^-6;
    mprintf("\nb) Determinar n para error < 10^-6:\n");
    
    // 1. Obtener derivada segunda máxima automaticamente
    M2 = ObtenerCotaMaxima(f2a, a, b, 2);
    mprintf("   M2 calculado (max|f''|): %.2f\n", M2);
    
    // 2. Calcular n mínimo teórico
    // Formula: Error <= ((b-a)^3 * M2) / (12 * n^2)
    // Despeje: n > sqrt( ((b-a)^3 * M2) / (12 * tol) )
    n_min = sqrt( ((b-a)^3 * M2) / (12 * tol) ); // f''(x) = 2/x^3, max en 1 es 2
    n_final_T = ceil(n_min); // Redondear hacia arriba
    
    mprintf("   n teórico > %.4f  --> Usamos n = %d\n", n_min, n_final_T);
    
    // 3. Verificación
    aprox_check = trapecio_comp(f2a, a, b, n_final_T);
    err_check = abs(val_real - aprox_check);
    mprintf("   Verificación (n=%d) -> Error Real: %.2e\n", n_final_T, err_check);
    
    if err_check < tol then
        mprintf("   >> ÉXITO: El error está por debajo de la tolerancia.\n");
    else
        mprintf("   >> CUIDADO: El error sigue siendo alto (revisar cálculo).\n");
    end
    mprintf("\n-------------------------------------------------\n");
    
    // -----------------------------------------------------
    // PARTE 2: SIMPSON 
    // -----------------------------------------------------
    mprintf("\n--- 2) MÉTODO SIMPSON ---\n");
    
    // 1. Aproximación con n=4
    aprox_S = simpson_comp(f2a, a, b, n);
    mprintf("1. Aprox con n=%d: %.8f (Error: %.2e)\n", n, aprox_S, abs(val_real - aprox_S));
    
    // 2. Buscar n para error < 10^-6
    // Formula Error Simpson: |E| <= ((b-a)^5 * M4) / (180 * n^4)
    // Despeje: n^4 >= ((b-a)^5 * M4) / (180 * tol)
    //          n >= raiz_cuarta( ... )
    
    M4 = ObtenerCotaMaxima(f2a, a, b, 4); // f''''(x) = 24/x^5, max en 1 es 24
    numerador = (b - a)^5 * M4;
    denominador = 180 * tol;
    
    n_min_S = (numerador / denominador)^(1/4); // Raíz cuarta
    n_final_S = ceil(n_min_S);
    
    // AJUSTE DE PARIDAD: Simpson necesita n PAR
    if modulo(n_final_S, 2) <> 0 then
        n_final_S = n_final_S + 1;
        mprintf("   (Ajustando a par: n teórico %.2f -> %d)\n", n_min_S, n_final_S);
    end
    
    mprintf("2. Búsqueda de n (Error < %.1e):\n", tol);
    mprintf("   M4 (Deriv. 4ta) calculado: %.2f\n", M4);
    mprintf("   n teórico >= %.2f  --> Usamos n = %d\n", n_min_S, n_final_S);
    
    // Verificación
    check_S = simpson_comp(f2a, a, b, n_final_S);
    mprintf("   >> Verificación Simpson (n=%d):  Error Real = %.2e\n", n_final_S, abs(val_real - check_S));
    
    mprintf("\n-------------------------------------------------\n");
    mprintf("CONCLUSIÓN: Simpson requiere n=%d vs Trapecio n=%d para la misma precisión.\n", n_final_S, n_final_T);
    mprintf("-------------------------------------------------\n");
endfunction

// ==========================================
// 3. LÓGICA DEL EJERCICIO 2
// ==========================================
function ejercicio2()
    mprintf("\n-------------------------------------------------\n");
    mprintf("EJERCICIO 2: Trapecio Compuesto vs Scilab (intg)\n");
    mprintf("-------------------------------------------------\n");

    // --- Definición de casos: [a, b, n] ---
    // Usamos listas o vectores para organizar, pero aquí lo haremos secuencial para claridad
    
    // a) Int(1/x) de 1 a 3, n=4
    a=1; b=3; n=4;
    aprox = trapecio_comp(f2a, a, b, n);
    real = intg(a, b, f2a);
    mprintf("\na) Int(1/x) [1, 3], n=%d\n", n);
    mprintf("   Aprox (Trapecio): %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));

    // b) Int(x^3) de 0 a 2, n=4
    a=0; b=2; n=4;
    aprox = trapecio_comp(f2b, a, b, n);
    real = intg(a, b, f2b);
    mprintf("\nb) Int(x^3) [0, 2], n=%d\n", n);
    mprintf("   Aprox (Trapecio): %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));

    // c) Int(x(1+x^2)^0.5) de 0 a 3, n=6
    a=0; b=3; n=6;
    aprox = trapecio_comp(f2c, a, b, n);
    real = intg(a, b, f2c);
    mprintf("\nc) Int(x(1+x^2)^0.5) [0, 3], n=%d\n", n);
    mprintf("   Aprox (Trapecio): %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));

    // d) Int(sin(pi*x)) de 0 a 1, n=8
    a=0; b=1; n=8;
    aprox = trapecio_comp(f2d, a, b, n);
    real = intg(a, b, f2d);
    mprintf("\nd) Int(sin(pi*x)) [0, 1], n=%d\n", n);
    mprintf("   Aprox (Trapecio): %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));

    // e) Int(x*sin(x)) de 0 a 2pi, n=8
    a=0; b=2*%pi; n=8;
    aprox = trapecio_comp(f2e, a, b, n);
    real = intg(a, b, f2e); // Scilab maneja bien la precisión de 2pi
    mprintf("\ne) Int(x*sin(x)) [0, 2pi], n=%d\n", n);
    mprintf("   Aprox (Trapecio): %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));

    // f) Int(x^2*e^x) de 0 a 1, n=8
    a=0; b=1; n=8;
    aprox = trapecio_comp(f2f, a, b, n);
    real = intg(a, b, f2f);
    mprintf("\nf) Int(x^2*e^x) [0, 1], n=%d\n", n);
    mprintf("   Aprox (Trapecio): %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));
    
    mprintf("\n-------------------------------------------------\n");
    
    analizar_caso_T(f2a, 1, 3, 4, "a) Int(1/x)");
    analizar_caso_T(f2b, 0, 2, 4, "b) Int(x^3)");
    analizar_caso_T(f2c, 0, 3, 6, "c) Int(x(1+x^2)^0.5)");
    analizar_caso_T(f2d, 0, 1, 8, "d) Int(sin(pi*x))");
    analizar_caso_T(f2e, 0, 2*%pi, 8, "e) Int(x*sin(x))");
    analizar_caso_T(f2f, 0, 1, 8, "f) Int(x^2*e^x)");
    
    mprintf("\n-------------------------------------------------\n");
    
endfunction

// ==========================================
// 3. LÓGICA DEL EJERCICIO 3 (Simpson)
// ==========================================
function ejercicio3()
    mprintf("\n-------------------------------------------------\n");
    mprintf("EJERCICIO 3: Simpson Compuesto vs Scilab (intg)\n");
    mprintf("-------------------------------------------------\n");

    // a) Int(1/x) de 1 a 3, n=4
    a=1; b=3; n=4;
    aprox = simpson_comp(f2a, a, b, n);
    real = intg(a, b, f2a);
    mprintf("\na) Int(1/x) [1, 3], n=%d\n", n);
    mprintf("   Aprox (Simpson):  %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));

    // b) Int(x^3) de 0 a 2, n=4
    a=0; b=2; n=4;
    aprox = simpson_comp(f2b, a, b, n);
    real = intg(a, b, f2b);
    mprintf("\nb) Int(x^3) [0, 2], n=%d\n", n);
    mprintf("   Aprox (Simpson):  %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));
    mprintf("   (Nota: El error debería ser casi 0 pues Simpson es exacto para grado 3)\n");
    
    /*Cuando ejecutes el inciso b) ($\int x^3 dx$), notarás que el error es extremadamente bajo (del orden de $10^{-16}$, es decir, cero máquina).Esto confirma la teoría del PDF:El término de error de Simpson depende de la derivada cuarta $f^{(4)}(\xi)$2.Si $f(x) = x^3$, entonces $f'(x)=3x^2$, $f''(x)=6x$, $f'''(x)=6$, y $f^{(4)}(x) = 0$.Por lo tanto, la Regla de Simpson es exacta para polinomios cúbicos.*/

    // c) Int(x(1+x^2)^0.5) de 0 a 3, n=6
    a=0; b=3; n=6;
    aprox = simpson_comp(f2c, a, b, n);
    real = intg(a, b, f2c);
    mprintf("\nc) Int(x(1+x^2)^0.5) [0, 3], n=%d\n", n);
    mprintf("   Aprox (Simpson):  %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));

    // d) Int(sin(pi*x)) de 0 a 1, n=8
    a=0; b=1; n=8;
    aprox = simpson_comp(f2d, a, b, n);
    real = intg(a, b, f2d);
    mprintf("\nd) Int(sin(pi*x)) [0, 1], n=%d\n", n);
    mprintf("   Aprox (Simpson):  %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));

    // e) Int(x*sin(x)) de 0 a 2pi, n=8
    a=0; b=2*%pi; n=8;
    aprox = simpson_comp(f2e, a, b, n);
    real = intg(a, b, f2e);
    mprintf("\ne) Int(x*sin(x)) [0, 2pi], n=%d\n", n);
    mprintf("   Aprox (Simpson):  %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));

    // f) Int(x^2*e^x) de 0 a 1, n=8
    a=0; b=1; n=8;
    aprox = simpson_comp(f2f, a, b, n);
    real = intg(a, b, f2f);
    mprintf("\nf) Int(x^2*e^x) [0, 1], n=%d\n", n);
    mprintf("   Aprox (Simpson):  %.8f\n   Exacto (Scilab):  %.8f\n   Error: %.2e\n", aprox, real, abs(real-aprox));
    
    mprintf("\n-------------------------------------------------\n");
    
    
    analizar_caso_simpson(f2a, 1, 3, 4, "a) Int(1/x)");
    analizar_caso_simpson(f2b, 0, 2, 4, "b) Int(x^3)");
    analizar_caso_simpson(f2c, 0, 3, 6, "c) Int(x(1+x^2)^0.5)");
    analizar_caso_simpson(f2d, 0, 1, 8, "d) Int(sin(pi*x))");
    analizar_caso_simpson(f2e, 0, 2*%pi, 8, "e) Int(x*sin(x))");
    analizar_caso_simpson(f2f, 0, 1, 8, "f) Int(x^2*e^x)");

    mprintf("\n-------------------------------------------------\n");
    
endfunction

// ==========================================
// 2. RESOLUCIÓN DEL EJERCICIO 4
// ==========================================
function ejercicio4()
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO 4: Aproximación de I = Integral((x+1)^-1)\n");
    mprintf("Intervalo [0, 1.5] con n = 10\n");
    mprintf("=================================================\n");
    
    // Datos
    a = 0; 
    b = 1.5;
    n = 10;
    
    // Valor dado por el enunciado (para el inciso c)
    I_enunciado = 0.9262907; 
    
    // Valor real matemático: ln(1.5 + 1) - ln(0 + 1) = ln(2.5)
    I_real_scilab = log(2.5);
    
    // --- a) Método del Trapecio Compuesto ---
    aprox_trap = trapecio_comp(f4, a, b, n);
    
    // --- b) Método de Simpson Compuesto ---
    aprox_simp = simpson_comp(f4, a, b, n);
    
    // --- c) Comparación ---
    mprintf("\n1. RESULTADOS NUMÉRICOS:\n");
    mprintf("   Trapecio (n=10): %.8f\n", aprox_trap);
    mprintf("   Simpson  (n=10): %.8f\n", aprox_simp);
    
    mprintf("\n2. COMPARACIÓN CON VALOR DEL ENUNCIADO (I = %.7f):\n", I_enunciado);
    mprintf("   Error Trapecio: %.2e\n", abs(I_enunciado - aprox_trap));
    mprintf("   Error Simpson:  %.2e\n", abs(I_enunciado - aprox_simp));
    
    mprintf("\n3. COMPARACIÓN CON VALOR MATEMÁTICO REAL (ln(2.5) ≈ %.7f):\n", I_real_scilab);
    mprintf("   Error Trapecio: %.2e\n", abs(I_real_scilab - aprox_trap));
    mprintf("   Error Simpson:  %.2e\n", abs(I_real_scilab - aprox_simp));
    
    mprintf("\n>> OBSERVACIÓN:\n");
    if abs(I_real_scilab - I_enunciado) > 0.001 then
        mprintf("   Parece haber un error de tipeo en el enunciado (dice 0.92... y es 0.91...).\n");
        mprintf("   Simpson se acerca mucho más al valor matemático real.\n");
    end

endfunction


// ==========================================
// 6. EJERCICIO 2 (PC)
// ==========================================

function ejercicio_2PC()
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO: Int_1^3 e^x sin(x) dx (Simpson)\n");
    mprintf("Dato: |f''''(x)| < 30 en [1, 3]\n");
    mprintf("Requerimiento: Error < 10^-4\n");
    mprintf("=================================================\n");
    
    a = 1; b = 3;
    M4_dato = 30; // Dato del enunciado
    tol = 10^-4;
    
    // --- INCISO A: Hallar n  / su error < 10^4---
    // Formula Error Simpson: |E| <= ((b-a)^5 * M4) / (180 * n^4)
    // Despeje: n^4 >= ((b-a)^5 * M4) / (180 * tol)
    
    numerador = (b - a)^5 * M4_dato; // (3-1)^5 * 30 = 32 * 30 = 960
    denominador = 180 * tol;
    
    n_min = (numerador / denominador)^(1/4);
    n_final = ceil(n_min);
    
    // Ajuste de paridad para Simpson
    if modulo(n_final, 2) <> 0 then
        n_final = n_final + 1;
        mprintf("   (Ajustando a par: %.2f -> %d)\n", n_min, n_final);
    end
    
    mprintf("\na) Cálculo de n:\n");
    mprintf("   n teórico >= %.4f\n", n_min);
    mprintf("   >> Se usarán n = %d subintervalos.\n", n_final);
    
    
    // --- INCISO B: Calcular Integral, usando ese n ---
    aprox = simpson_comp(f_examen, a, b, n_final);
    
    // Valor real para verificar (opcional)
    val_real = intg(a, b, f_examen); 
    
    mprintf("\nb) Aproximación con Simpson (n=%d):\n", n_final);
    mprintf("   Valor Aproximado: %.8f\n", aprox);
    mprintf("   Valor Real (ref): %.8f\n", val_real);
    mprintf("   Error Real:       %.2e (¿Menor a 10^-4? %s)\n", abs(val_real - aprox), string(abs(val_real - aprox) < tol));
    
    mprintf("\n-------------------------------------------------\n");
endfunction


// ==========================================
// 6. EJERCICIO 3 (PC): Si(b) = Int_1^b sin(x)/x  , con b>1
// ==========================================
function ejercicio_3PC()
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO 3: Integral Si(b) = Int_1^b sin(x)/x dx\n");
    mprintf("=================================================\n");
    
    
    // Inciso a) Función solicitada -
     //entrada:b>1,n
     //salida: resultado de aproximar Si(b) por el método compuesto del trapecio con n subintervalos
    function resultado = Calcular_Si(b, n)
        resultado = trapecio_comp(f_Si, 1, b, n);
    endfunction
    
    // --- INCISO B: Aproximaciones con n=100 y distintos valores de b ---
    n = 100;
    valores_b = [2, 5, 10, %pi*4]; // Ejemplos de b
    
    mprintf("\nb) Aproximaciones con n = %d:\n", n);
    for b = valores_b
        aprox = Calcular_Si(b, n);
        mprintf("   Si(%.2f) ≈ %.8f\n", b, aprox);
    end
    
    // --- INCISO C: Cota de Error (Trapecio) ---
    // Dato: |f''(x)| <= 1 para x > 1.
    // Fórmula Error Trapecio: E <= ((b-a)^3 / 12n^2) * M2
    // Aquí a = 1, M2 = 1.
    
    mprintf("\nc) Cota de Error (Trapecio) en función de b:\n");
    mprintf("   Dato: |f''(x)| <= 1. Intervalo [1, b].\n");
    mprintf("   Fórmula Cota(b) = (b - 1)^3 / (12 * n^2)\n");
    
    mprintf("\n   Ejemplo numérico para n=100:\n");
    for b = valores_b
        cota = ((b - 1)^3) / (12 * n^2);
        mprintf("   b=%.2f -> Cota Error <= %.2e\n", b, cota);
    end
    
    
    // --- EXTRA: SIMPSON (Pedido adicional) ---
    mprintf("\n--- EXTRA: Cálculo con Simpson (n=%d) ---\n", n);
    // Para Simpson necesitamos M4 = max |f''''(x)|. 
    // Usaremos nuestra herramienta automática para estimarlo.
    for b = valores_b
        aprox_S = simpson_comp(f_Si, 1, b, n);
        
        // Estimar M4 en [1, b]
        M4 = ObtenerCotaMaxima(f_Si, 1, b, 4);
        cota_S = ((b - 1)^5 / (180 * n^4)) * M4;
        
        mprintf("   Si(%.2f) ≈ %.8f | Cota Est. Simpson: %.2e\n", b, aprox_S, cota_S);
    end
    
    mprintf("\n-------------------------------------------------\n");
endfunction


// ==========================================
// 7. EJERCICIO EXAMEN 1 : Int_1^5 x/(x^2+4) dx
// ==========================================

function ejercicio3_EXAMEN()
    /* a. utilice el método del trapecio compuesto con 16 subintervalos para calcular el valor de la integral de 1 a 5 con f(x)=x/(x^2+4) dx
    b. determine una cota del error de aporximación. */
    
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO EXAMEN 1: Int_1^5 x/(x^2+4) dx\n");
    mprintf("Comparación Trapecio vs Simpson (n=16)\n");
    mprintf("=================================================\n");
    
    // Configuración
    a = 1; 
    b = 5; 
    n = 16;
    f = f_examen_1;
    
    // Valor real para verificar (Analítica: 0.5 * (ln(29) - ln(5)))
    val_real = intg(a, b, f);
    
    // -----------------------------------------------------
    // PARTE A: TRAPECIO COMPUESTO
    // -----------------------------------------------------
    mprintf("\n--- A) TRAPECIO COMPUESTO ---\n");
    aprox_T = trapecio_comp(f, a, b, n);
    err_real_T = abs(val_real - aprox_T);
    
    // Cota Teórica Trapecio: E <= ((b-a)^3 / 12n^2) * M2
    M2 = ObtenerCotaMaxima(f, a, b, 2);
    cota_T = ((b - a)^3 * M2) / (12 * n^2);
    
    mprintf("   Aprox: %.8f\n", aprox_T);
    mprintf("   Error Real:   %.2e\n", err_real_T);
    mprintf("   Cota Teórica: %.2e (M2 estim: %.4f)\n", cota_T, M2);
    
    if err_real_T <= cota_T * 1.01 then 
        mprintf("   >> Verificación: OK\n"); 
    else 
        mprintf("   >> Verificación: REVISAR\n"); 
    end


    // -----------------------------------------------------
    // PARTE B: SIMPSON COMPUESTO
    // -----------------------------------------------------
    mprintf("\n--- B) SIMPSON COMPUESTO ---\n");
    aprox_S = simpson_comp(f, a, b, n);
    err_real_S = abs(val_real - aprox_S);
    
    // Cota Teórica Simpson: E <= ((b-a)^5 / 180n^4) * M4
    M4 = ObtenerCotaMaxima(f, a, b, 4);
    cota_S = ((b - a)^5 * M4) / (180 * n^4);
    
    mprintf("   Aprox: %.8f\n", aprox_S);
    mprintf("   Error Real:   %.2e\n", err_real_S);
    mprintf("   Cota Teórica: %.2e (M4 estim: %.4f)\n", cota_S, M4);
    
    if err_real_S <= cota_S * 1.01 then 
        mprintf("   >> Verificación: OK\n"); 
    else 
        mprintf("   >> Verificación: REVISAR\n"); 
    end
    
    mprintf("\n-------------------------------------------------\n");
    mprintf("CONCLUSIÓN: Simpson es %.0f veces más preciso aquí.\n", err_real_T / err_real_S);
    mprintf("-------------------------------------------------\n");
    
endfunction

// ==========================================
// 4. MENÚ PRINCIPAL
// ==========================================
while %t
    mprintf("\n==================================================================\n");
    mprintf("          SISTEMA DE INTEGRACIÓN NUMÉRICA (PRÁCTICA 8)           \n");
    mprintf("==================================================================\n");
    mprintf("1. EJ 1: Aproximación de In(2) con método Trapecio/Simsonp en 4 subintervalos / error menor que 10^-6\n");
    mprintf("2. EJ 2: Trapecio Compuesto (6 casos)\n");
    mprintf("3. EJ 3: Simpson Compuesto (6 casos)\n");
    mprintf("4. EJ 4: Trapecio y Simpson Compuesto (10 subintervalos)\n");
    mprintf("5. EJ2 (PC): Aproximar I de 1 a 3 e^x sin(x) con Cota Dada (M4 < 30), para ese n hallado. --  trapecio/simsop\n");
    mprintf("6. EJ 3 (PC): Si(b) (Integral Seno) con b>1 . Buscar aproximaciones y cotas para distintos b -- trapecio/simsopn\n");
    mprintf("7. EJERCICIO EXAMEN 1: Int x/(x^2+4) (Trapecio y simpson n=16 + Cota)\n");
    mprintf("0. SALIR\n");
    mprintf("------------------------------------------------------------------\n");
    
    opcion = input("Elige una opción: ");
    
    select opcion
    case 1 then ejercicio1();
    case 2 then ejercicio2();
    case 3 then ejercicio3();
    case 4 then ejercicio4();
    case 5 then ejercicio_2PC();
    case 6 then ejercicio_3PC();
    case 7 then ejercicio3_EXAMEN();
    case 0 then 
        mprintf("\n¡Éxitos!\n"); 
        break;
    else 
        mprintf("\nOpción no válida.\n");
    end
end
