/*Considere la sig. integral doble:
integral de -2 a 2 (integral de 0 a 4 de f(x)=x^2-3y^2+xy^2 dx) dy

a) evalue la integral analiticamente
b) aproxime la integral mediante el metodo de simpsion y trapecio simple (con 2 subintervalos))
c) cual es el error de aproximacion de las integrales interiores? justificar
d) cual es el error de aproximacion de las integrales exteriores? justificar
e) repetir el ejercicio para la sig. integral doble: integral de -2 a 2 (integral de 0 a 4 de g(x)=x^2-3y^2+x dx) dy
*/

clc(); clear();

// ==========================================
// 0. HERRAMIENTAS DE CÁLCULO DE COTAS
// ==========================================
function d=DerivadaNum(f, x, orden)
    h = 0.001; 
    if orden == 2 then
        d = (f(x+h) - 2*f(x) + f(x-h)) / h^2;
    elseif orden == 4 then
        d = (f(x+2*h) - 4*f(x+h) + 6*f(x) - 4*f(x-h) + f(x-2*h)) / h^4;
    else
        d = 0; 
    end
endfunction

function M=ObtenerCotaMaxima(f, a, b, orden)
    UMBRAL_GIGANTE = 10000; 
    puntos = linspace(a + 1e-4, b - 1e-4, 500);
    max_val = 0; es_infinito = %f;
    for x_val = puntos
        try d = abs(DerivadaNum(f, x_val, orden));
        catch d = UMBRAL_GIGANTE + 1; end
        if d > UMBRAL_GIGANTE | isinf(d) | isnan(d) then
            es_infinito = %t; break;
        end
        if d > max_val then max_val = d; end
    end
    if es_infinito then M = %inf; else M = max_val; end
endfunction

// Herramienta para calcular valor exacto automáticamente
function valor=IntegralDobleExacta(func, a, b, c, d)
    function r=interna(y), r = intg(a, b, list(func, y)); endfunction
    valor = intg(c, d, interna);
endfunction

// ==========================================
// 1. DEFINICIÓN DE FUNCIONES DE INTEGRACIÓN
// ==========================================
function w=trapecio_comp(f, a, b, n) 
    h = (b - a)/n; 
    w = (f(a) + f(b))/2;
    for i = 1 : n-1
        x = a + h*i;
        w = w + f(x);
    end
    w = w*h;
endfunction

function w=simpson_comp(f, a, b, n)
    if modulo(n, 2) <> 0 then error("Simpson requiere n PAR."); end
    h = (b - a)/n;
    w = f(a) + f(b);
    for i = 1 : n-1
        x = a + h*i;
        if modulo(i, 2) == 0 then w = w + 2*f(x); else w = w + 4*f(x); end
    end
    w = w*h/3;
endfunction

// ==========================================
// 2. FUNCIONES MATEMÁTICAS
// ==========================================

// --- FUNCIONES PARA LA INTEGRAL DOBLE ---
// f(x,y) = x^2 - 3y^2 + xy^2
function z=func_doble_f(x, y)
    z = x^2 - 3*y^2 + x*y^2;
endfunction

// g(x,y) = x^2 - 3y^2 + x
function z=func_doble_g(x, y)
    z = x^2 - 3*y^2 + x;
endfunction

// ==========================================
// 3. AUXILIARES DE ANÁLISIS
// ==========================================
function analizar_caso_T(f, a, b, n, nombre)
    aprox = trapecio_comp(f, a, b, n); real = intg(a, b, f); err_real = abs(real - aprox);
    M2 = ObtenerCotaMaxima(f, a, b, 2);
    if isinf(M2) then cota = %inf; else cota = ((b-a)^3 / (12 * n^2)) * M2; end
    mprintf("\n%s [n=%d]\n   Aprox: %.8f | Err: %.2e | Cota: %.2e (M2~%.2f)\n", nombre, n, aprox, err_real, cota, M2);
endfunction

function analizar_caso_simpson(f, a, b, n, nombre)
    aprox = simpson_comp(f, a, b, n); real = intg(a, b, f); err_real = abs(real - aprox);
    M4 = ObtenerCotaMaxima(f, a, b, 4);
    if isinf(M4) then cota = %inf; else cota = ((b-a)^5 / (180 * n^4)) * M4; end
    if M4 < 1e-9 then cota=0; end
    mprintf("\n%s [n=%d]\n   Aprox: %.8f | Err: %.2e | Cota: %.2e (M4~%.2f)\n", nombre, n, aprox, err_real, cota, M4);
endfunction

// =========================================================================
// 8. EJERCICIO INTEGRAL DOBLE (Evaluación Integral Doble)
// =========================================================================
function ejercicio_doble_integral_examen()
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO DOBLE INTEGRAL: Int_-2^2 Int_0^4 f(x,y) dx dy\n");
    mprintf("Comparación Trapecio vs Simpson (2 subintervalos)\n");
    mprintf("=================================================\n");
    
    // =========================================================
    // === [CONFIGURACIÓN DEL EXAMEN - CAMBIAR AQUÍ] ===
    // =========================================================
    
    // 1. Define tu función f(x,y)
    // Ejemplo actual: f(x)=x^2-3y^2+xy^2
    deff('z=f_examen(x,y)', 'z = x^2 - 3*y^2 + x*y^2'); 
    
    // 2. Define tu función g(x,y) (si hay inciso e, sino ignora)
    // Ejemplo actual: g(x)=x^2-3y^2+x
    deff('z=g_examen(x,y)', 'z = x^2 - 3*y^2 + x');

    // 3. Define los límites de integración
    // Integral interna (dx): de ax a bx
    ax = 0; bx = 4;  //interior X
    // Integral externa (dy): de ay a by
    ay = -2; by = 2;  //exterior Y
    
    // 4. Número de subintervalos (n)
    n = 2;  //simple repetido.
    
    // =========================================================
    // === [FIN DE CONFIGURACIÓN] ===
    // =========================================================


    // --- FUNCIÓN RESOLVER GENÉRICA (Para incisos b y e) ---
    function ResolverCaso(func_xy, nombre)
        mprintf("\n>>> CASO: %s\n", nombre);
        
        // 1. ANALÍTICO
        // Usamos intg anidado para no tener que integrar a mano
        val_analitico = IntegralDobleExacta(func_xy, ax, bx, ay, by);
        mprintf("a) Valor Analítico: %.4f\n", val_analitico);
        
        // 2. TRAPECIO DOBLE (Usando trapecio_comp anidado)
        // Exterior: y va de -2 a 2. Nodos: -2, 0, 2 (n=2)
        hy = (by - ay) / n;
        suma_exterior = 0;
        
        // Iteramos sobre los nodos de Y para calcular las integrales internas
        for i = 0:n
            y_nodo = ay + i*hy;
            
            // Definimos la función de x para este y fijo: g(x) = f(x, y_nodo)
            // Scilab necesita definirla 'on the fly' o usar list, pero para usar
            // TU funcion trapecio_comp que toma f, hacemos un wrapper local:
            deff('z=f_temp(x)', 'z=func_xy(x, ' + string(y_nodo) + ')');
            
            // Calculamos integral interna con Trapecio
            integral_interna = trapecio_comp(f_temp, ax, bx, n);
            
            // Sumamos al Trapecio Exterior
            if i==0 | i==n then peso = 1; else peso = 2; end
            suma_exterior = suma_exterior + peso * integral_interna;
        end
        aprox_trap = (hy / 2) * suma_exterior;
        
        // 3. SIMPSON DOBLE (Usando simpson_comp anidado)
        suma_exterior_S = 0;
        for i = 0:n
            y_nodo = ay + i*hy;
            deff('z=f_temp_s(x)', 'z=func_xy(x, ' + string(y_nodo) + ')');
            
            // Calculamos integral interna con Simpson
            integral_interna_S = simpson_comp(f_temp_s, ax, bx, n);
            
            // Pesos Simpson (1, 4, 1 para n=2)
            if i==0 | i==n then peso = 1; else peso = 4; end // Solo funciona para n=2 simple
            suma_exterior_S = suma_exterior_S + peso * integral_interna_S;
        end
        aprox_simp = (hy / 3) * suma_exterior_S;
        
        mprintf("b) Aproximaciones (n=2x2):\n");
        mprintf("   Trapecio: %.4f (Error: %.2e)\n", aprox_trap, abs(val_analitico - aprox_trap));
        mprintf("   Simpson:  %.4f (Error: %.2e)\n", aprox_simp, abs(val_analitico - aprox_simp));
        
        // JUSTIFICACIONES
        mprintf("c) & d) Justificación de Errores:\n");
        mprintf("   * Simpson es exacto para polinomios de grado <= 3.\n");
        mprintf("   * La función es polinómica de grado 2 en x e y.\n");
        mprintf("   * Por eso el error de Simpson es prácticamente CERO (orden de máquina).\n");
        mprintf("   * Trapecio solo es exacto para rectas (grado 1), por eso tiene error.\n");
        
        //AUTOMATICAS:
        err_s = abs(val_analitico - aprox_simp);
        if err_s < 1e-9 then
            mprintf("   * El error de Simpson es prácticamente CERO.\n");
            mprintf("   * ESTO IMPLICA que f(x,y) es un polinomio de grado <= 3 en ambas variables.\n");
        else
            mprintf("   * El error de Simpson NO es cero.\n");
            mprintf("   * La función tiene grado > 3 o no es polinómica.\n");
        end
    endfunction

    // --- EJECUCIÓN INCISO A, B, C, D (f = x^2 - 3y^2 + xy^2) ---
    // Valor analítico calculado manualmente: 64
    ResolverCaso(func_doble_f, "f(x,y) = x^2 - 3y^2 + xy^2");
    
    // --- EJECUCIÓN INCISO E (g = x^2 - 3y^2 + x) ---
    // Valor analítico calculado: 160/3 = 53.3333...
    ResolverCaso(func_doble_g, "g(x,y) = x^2 - 3y^2 + x");
    
    
    ///c) Error integrales interiores (en $x$): Las funciones $f(x,y)$ y $g(x,y)$ son polinomios de grado 2 respecto a la variable $x$ ($x^2$).
    // La Regla de Simpson es exacta para polinomios de hasta grado 3. Por lo tanto, el error teórico de la integral interior con Simpson es CERO.
    // El método del Trapecio, siendo exacto solo para grado 1, sí presentará error.d) Error integrales exteriores (en $y$):
    // Al integrar respecto a $x$, el resultado sigue siendo un polinomio de grado 2 respecto a $y$ (aparecen términos como $y^2$). 
    //Al aplicar Simpson nuevamente en el eje $y$, como el grado es 2 (< 3), el error de la integral exterior también es CERO.
    
    mprintf("\n-------------------------------------------------\n");
endfunction


// =========================================================================
// 8. EJERCICIO EXAMEN 2: INTEGRAL DOBLE (Manual / Pesos explícitos)
// =========================================================================
function ejercicio_doble_integral_examen_manual()
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO DOBLE INTEGRAL: Int_-2^2 Int_0^4 f(x,y) dx dy\n");
    mprintf("Estrategia: Malla de 2 subintervalos (n=2) en X e Y\n");
    mprintf("=================================================\n");

    // Limites
    ax = 0; bx = 4; // Interior X
    ay = -2; by = 2; // Exterior Y
    
    // Pasos h
    n = 2;
    hx = (bx - ax) / n; // (4-0)/2 = 2
    hy = (by - ay) / n; // (2--2)/2 = 2
    
    // Nodos (Malla 3x3)
    x0 = ax; x1 = ax + hx; x2 = bx;       // 0, 2, 4
    y0 = ay; y1 = ay + hy; y2 = by;       // -2, 0, 2
    
    mprintf("Datos Geométricos:\n");
    mprintf("hx = %.1f, hy = %.1f\n", hx, hy);
    mprintf("Nodos X: %.1f, %.1f, %.1f\n", x0, x1, x2);
    mprintf("Nodos Y: %.1f, %.1f, %.1f\n", y0, y1, y2);

    // --- FUNCIÓN RESOLVER ---
    function ResolverManual(func_z, nombre, val_analitico)
        mprintf("\n>>> CASO: %s\n", nombre);
        
        // Evaluamos la función en los 9 puntos de la malla
        z00 = func_z(x0, y0); z10 = func_z(x1, y0); z20 = func_z(x2, y0);
        z01 = func_z(x0, y1); z11 = func_z(x1, y1); z21 = func_z(x2, y1);
        z02 = func_z(x0, y2); z12 = func_z(x1, y2); z22 = func_z(x2, y2);
        
        // --- MÉTODO 1: TRAPECIO (n=2) ---
        // Pesos Trapecio 1D para n=2: [1, 2, 1]
        // Pesos 2D (producto):
        // 1 2 1
        // 2 4 2
        // 1 2 1
        Suma_T = 1*z00 + 2*z10 + 1*z20 + ...
                 2*z01 + 4*z11 + 2*z21 + ...
                 1*z02 + 2*z12 + 1*z22;
                 
        Aprox_T = (hx * hy / 4) * Suma_T;
        
        // --- MÉTODO 2: SIMPSON (n=2, es decir, Simple) ---
        // Pesos Simpson 1D para n=2: [1, 4, 1]
        // Pesos 2D (producto):
        // 1  4  1
        // 4 16  4
        // 1  4  1
        Suma_S = 1*z00 + 4*z10 + 1*z20 + ...
                 4*z01 + 16*z11 + 4*z21 + ...
                 1*z02 + 4*z12 + 1*z22;
                 
        Aprox_S = (hx * hy / 9) * Suma_S;
        
        // Resultados
        mprintf("a) Valor Analítico: %.4f\n", val_analitico);
        mprintf("b) Aproximaciones:\n");
        mprintf("   Trapecio (n=2): %.4f (Error: %.2e)\n", Aprox_T, abs(val_analitico - Aprox_T));
        mprintf("   Simpson  (n=2): %.4f (Error: %.2e)\n", Aprox_S, abs(val_analitico - Aprox_S));
        
        mprintf("c) & d) Justificación:\n");
        if abs(val_analitico - Aprox_S) < 1e-9 then
            mprintf("   * Error Simpson ~ 0. Función es polinomio grado <= 3.\n");
        else
            mprintf("   * Error Simpson no es cero.\n");
        end
    endfunction

    // Ejecutar para f(x,y)
    ResolverManual(func_doble_f, "f = x^2 - 3y^2 + xy^2", 64);
    
    // Ejecutar para g(x,y)
    ResolverManual(func_doble_g, "g = x^2 - 3y^2 + x", 160/3);
    
    mprintf("\n-------------------------------------------------\n");
endfunction


// ==========================================
// 5. MENÚ PRINCIPAL
// ==========================================
while %t
    mprintf("\n==================================================================\n");
    mprintf("          SISTEMA DE INTEGRACIÓN NUMÉRICA (PRÁCTICA 8)           \n");
    mprintf("==================================================================\n");
    mprintf("8. EXAMEN 2: Integral Doble (Trapecio vs Simpson 2D)\n");
    mprintf("9. EXAMEN 2: Integral Doble MANUAL PASO X PASO (Trapecio vs Simpson 2D)\n");
    mprintf("0. SALIR\n");
    mprintf("------------------------------------------------------------------\n");
    
    opcion = input("Elige una opción: ");
    
    select opcion
    case 8 then ejercicio_doble_integral_examen();
    case 9 then ejercicio_doble_integral_examen_manual();
    case 0 then 
        mprintf("\n¡Éxitos!\n"); 
        break;
    else 
        mprintf("\nOpción no válida.\n");
    end
end
