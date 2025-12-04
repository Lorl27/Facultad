clc(); clear();

// ================================================================
// 1. FUNCIÓN PARA CALCULAR DERIVADA ENÉSIMA (Numérica)
// ================================================================
// Calcula el valor aproximado de la derivada de orden 'n' en el punto 'x'
// Usa diferencias finitas centrales recursivas.
function d = DerivadaNum(f, x, n)
    h = 0.001; // Paso pequeño (ajustable según la precisión deseada)
    
    if n == 0 then
        d = f(x);
    elseif n == 1 then
        // Primera derivada (Central O(h^2))
        d = (f(x + h) - f(x - h)) / (2*h);
    elseif n == 2 then
        // Segunda derivada
        d = (f(x + h) - 2*f(x) + f(x - h)) / (h^2);
    elseif n == 3 then
        // Tercera derivada
        d = (f(x + 2*h) - 2*f(x + h) + 2*f(x - h) - f(x - 2*h)) / (2 * h^3);
    elseif n == 4 then
        // Cuarta derivada (Usada para el error de Simpson)
        d = (f(x + 2*h) - 4*f(x + h) + 6*f(x) - 4*f(x - h) + f(x - 2*h)) / (h^4);
    else
        // Recursión para órdenes superiores (menos preciso)
        d = (DerivadaNum(f, x+h, n-1) - DerivadaNum(f, x-h, n-1)) / (2*h);
    end
endfunction


// ================================================================
// 2. FUNCIÓN PARA BUSCAR LA COTA MÁXIMA (M) EN [a, b]
// ================================================================
// Barre el intervalo para encontrar el máximo de |f^(n)(x)|
// Útil para hallar M2 (Trapecio) o M4 (Simpson) automáticamente.
function M = ObtenerCotaMaxima(f, a, b, orden_derivada)
    // 1. Crear una malla densa de puntos en el intervalo
    puntos = linspace(a, b, 1000); // 1000 puntos de muestreo
    valores = [];
    
    // 2. Evaluar la derivada en cada punto
    for i = 1:length(puntos)
        x_val = puntos(i);
        val_deriv = DerivadaNum(f, x_val, orden_derivada);
        valores(i) = abs(val_deriv); // Nos interesa el valor absoluto
    end
    
    // 3. Obtener el máximo
    M = max(valores);
    
    // (Opcional) Graficar para verificar visualmente
    // plot(puntos, valores); title("Comportamiento de la Derivada orden " + string(orden_derivada));
endfunction


// ================================================================
// 3. FUNCIÓN COMPARADORA (Trapecio vs Simpson)
// ================================================================
// Calcula ambas integrales, compara con el valor real y recomienda la mejor.
function CompararMetodos(f, a, b, n)
    mprintf("\n=== ANÁLISIS DE INTEGRACIÓN NUMÉRICA ===\n");
    mprintf("Intervalo: [%.2f, %.2f] | Subintervalos n = %d\n", a, b, n);
    
    // 1. Calcular el valor EXACTO (usando función intg de Scilab)
    // Nota: intg puede fallar si la función tiene singularidades, pero para casos normales es el 'gold standard'
    valor_real = intg(a, b, f);
    mprintf("Valor Exacto (intg): %.10f\n\n", valor_real);
    
    // --- MÉTODO TRAPECIO ---
    h = (b - a) / n;
    sum_t = 0;
    for i = 1:n-1
        sum_t = sum_t + f(a + i*h);
    end
    I_trap = (h/2) * (f(a) + 2*sum_t + f(b));
    err_trap = abs(valor_real - I_trap);
    
    // --- MÉTODO SIMPSON ---
    // Simpson requiere n par. Si es impar, avisamos.
    if modulo(n, 2) <> 0 then
        mprintf(">> AVISO: n=%d es impar. Simpson requiere n par.\n", n);
        mprintf(">> Se usará n=%d para Simpson.\n", n+1);
        n_simp = n + 1;
    else
        n_simp = n;
    end
    
    h_s = (b - a) / n_simp;
    sum_pares = 0;
    sum_impares = 0;
    
    // Suma de impares (coeficiente 4)
    for i = 1:2:n_simp-1
        sum_impares = sum_impares + f(a + i*h_s);
    end
    // Suma de pares (coeficiente 2)
    for i = 2:2:n_simp-2
        sum_pares = sum_pares + f(a + i*h_s);
    end
    
    I_simp = (h_s/3) * (f(a) + 4*sum_impares + 2*sum_pares + f(b));
    err_simp = abs(valor_real - I_simp);

    // --- RESULTADOS ---
    mprintf("1. TRAPECIO (n=%d):\n", n);
    mprintf("   Valor: %.10f | Error Real: %.2e\n", I_trap, err_trap);
    
    // Cota teórica Trapecio: (b-a)^3 / (12*n^2) * M2
    M2 = ObtenerCotaMaxima(f, a, b, 2); 
    cota_T = ((b-a)^3 / (12 * n^2)) * M2;
    mprintf("   Cota Teórica (est): %.2e (usando M2 aprox %.2f)\n\n", cota_T, M2);

    mprintf("2. SIMPSON (n=%d):\n", n_simp);
    mprintf("   Valor: %.10f | Error Real: %.2e\n", I_simp, err_simp);
    
    // Cota teórica Simpson: (b-a)^5 / (180*n^4) * M4
    M4 = ObtenerCotaMaxima(f, a, b, 4);
    cota_S = ((b-a)^5 / (180 * n_simp^4)) * M4;
    mprintf("   Cota Teórica (est): %.2e (usando M4 aprox %.2f)\n\n", cota_S, M4);
    
    // --- RECOMENDACIÓN ---
    mprintf(">> CONCLUSIÓN:\n");
    if err_simp < err_trap then
        mprintf("   CONVIENE USAR SIMPSON. Es %.2f veces más preciso.\n", err_trap/err_simp);
    else
        mprintf("   CONVIENE USAR TRAPECIO (Raro, revisa si n es muy pequeño o la función singular).\n");
    end
endfunction


// 1. Define tu función
function y = mi_funcion(x)
    y = x * exp(x);
endfunction

// 2. ¡Haz la magia!
CompararMetodos(mi_funcion, 0, 1, 4);
