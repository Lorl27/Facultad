clc(); clear();

// ==========================================
// 0. HERRAMIENTAS AUTOMÁTICAS 
// ==========================================

// Calcula derivada numérica de orden 'n' en el punto 'x'
function d = DerivadaNum(f, x, n)
    h = 0.001; 
    if n == 2 then
        // Segunda derivada (Centrada)
        d = (f(x+h) - 2*f(x) + f(x-h)) / h^2;
    elseif n == 4 then
        // Cuarta derivada (Centrada de 5 puntos)
        d = (f(x+2*h) - 4*f(x+h) + 6*f(x) - 4*f(x-h) + f(x-2*h)) / h^4;
    else
        d = 0; 
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

function Reportar(nombre, aprox, real, cota, M)
        err_real = abs(real - aprox);
        printf("%s: %.8f | Err Real: %.2e | ", nombre, aprox, err_real);
        
        // Aquí está la magia: Si M es infinito, avisamos
        if isinf(M) then
            printf("Cota Teórica: NO EXISTE (Derivada -> Inf)\n");
        else
            printf("Cota Teórica: %.2e (M~%.2f)\n", cota, M);
        end
    endfunction


// ==========================================
// 1. DEFINICIÓN DE FUNCIONES 
// ==========================================

// Aproximación de f en [a,b] mediante Regla del Trapecio (Simple)
function w = Trapecio(a, b, f_func)
    h = b - a;
    w = (h / 2) * (f_func(a) + f_func(b));
endfunction


// Aproximación de f en [a,b] mediante  Regla de Simpson (Simple, h = (b-a)/2)
function w = Simpson(a, b, f_func)
    h = (b - a) / 2;
    x_mid = a + h;
    w = (h / 3) * (f_func(a) + 4 * f_func(x_mid) + f_func(b));
endfunction


// ==========================================
// 2. FUNCIONES MATEMÁTICAS A INTEGRAR
// ==========================================
function y = func_a(x), y = log(x), endfunction
function y = func_b(x), y = x^(1/3), endfunction
function y = func_c(x), y = (sin(x))^2, endfunction

// ==========================================
// 3. RESOLUCIÓN DE LOS INCISOS
// ==========================================

function ejercicio1()
    disp("-------------------------------------------------")
    disp("EJERCICIO 1: Aproximación y Análisis de Error")
    disp("-------------------------------------------------")
    
    disp("a) f(x) = ln(x) y [a,b] = [1,2].")
    // --- CASO A: ln(x) en [1, 2] ---
    a = 1; b = 2;
    val_real = 2*log(2) - 1; // Analítica: x*ln(x) - x | de 1 a 2 
    disp("valor real manual",val_real,"valor con intg",intg(1,2,func_a));
    
    approx_T = Trapecio(a, b, func_a);
    approx_S = Simpson(a, b, func_a);
    
    // Cotas teóricas
    // Trapecio: h=1, max|f''|=1
    h_t = b - a;
   // M2 = 1; 
    M2 = ObtenerCotaMaxima(func_a, a, b, 2);
    cota_T = (h_t^3 / 12) * M2;
    
    // Simpson: h=0.5, max|f4|=6
    h_s = (b - a) / 2;
    //M4 = 6;
    M4 = ObtenerCotaMaxima(func_a, a, b, 4);
    cota_S = (h_s^5 / 90) * M4;
    
    disp("--- CASO A: Integral de ln(x) en [1, 2] ---")
    printf("Valor Real:   %.8f\n", val_real);
    //printf("Trapecio:     %.8f | Error Real: %.2e | Cota Teórica: %.2e\n", approx_T, abs(val_real - approx_T), cota_T);
    //printf("Simpson:      %.8f | Error Real: %.2e | Cota Teórica: %.2e\n", approx_S, abs(val_real - approx_S), cota_S);
    Reportar("Trapecio", Trapecio(a, b, func_a), val_real, cota_T, M2);
    Reportar("Simpson ", Simpson(a, b, func_a), val_real, cota_S, M4);
    disp(" ")
    
     disp("b) f(x) = x^(1/3) y [a,b] = [0,0.1].")
    // --- CASO B: x^(1/3) en [0, 0.1] ---
    a = 0; b = 0.1;
    val_real = (3/4) * (0.1)^(4/3); // Analítica: (3/4)x^(4/3)
    
    approx_T = Trapecio(a, b, func_b);
    approx_S = Simpson(a, b, func_b);
    
    // Intentamos obtener cotas, ahora la función devolverá %inf
    h_t = b - a;   M2 = ObtenerCotaMaxima(func_b, a, b, 2);
    cota_T = (h_t^3 / 12) * M2;
    
    h_s = (b - a)/2; M4 = ObtenerCotaMaxima(func_b, a, b, 4);
    cota_S = (h_s^5 / 90) * M4;
    
    disp("NOTA: No es posible hallar cota teórica. La derivada f''(x) tiende a infinito en x=0.")
    Reportar("Trapecio", Trapecio(a, b, func_b), val_real, cota_T, M2);
    Reportar("Simpson ", Simpson(a, b, func_b), val_real, cota_S, M4);
    
    disp("--- CASO B: Integral de x^(1/3) en [0, 0.1] ---")
    printf("Valor Real:   %.8f\n", val_real);
    printf("Trapecio:     %.8f | Error Real: %.2e\n", approx_T, abs(val_real - approx_T));
    printf("Simpson:      %.8f | Error Real: %.2e\n", approx_S, abs(val_real - approx_S));
    
    disp(" ")
    
     disp("c) f(x) =  sin^2(x) y [a,b] = [0,p1/3].")
    // --- CASO C: sin^2(x) en [0, pi/3] ---
    a = 0; b = %pi / 3;
    // Analítica: integral de sin^2(x) es x/2 - sin(2x)/4
    val_real = (%pi/3)/2 - sin(2*%pi/3)/4; 
    
    approx_T = Trapecio(a, b, func_c);
    approx_S = Simpson(a, b, func_c);
    
    // Cotas teóricas
    // f''(x) = 2cos(2x) -> Max abs = 2
    // f''''(x) = -8cos(2x) -> Max abs = 8
    h_t = b - a;
    //M2 = 2;
    M2 = ObtenerCotaMaxima(func_c, a, b, 2);
    cota_T = (h_t^3 / 12) * M2;
    
    h_s = (b - a) / 2;
    //M4 = 8;
    M4 = ObtenerCotaMaxima(func_c, a, b, 4);
    cota_S = (h_s^5 / 90) * M4;
    
    disp("--- CASO C: Integral de sin^2(x) en [0, pi/3] ---")
    printf("Valor Real:   %.8f\n", val_real);
    printf("Trapecio:     %.8f | Error Real: %.2e | Cota Teórica: %.2e\n", approx_T, abs(val_real - approx_T), cota_T);
    printf("Simpson:      %.8f | Error Real: %.2e | Cota Teórica: %.2e\n", approx_S, abs(val_real - approx_S), cota_S);

endfunction





// .........................................................................
// ........................... MENÚ PRINCIPAL ..............................
// .........................................................................

while %t
    mprintf("\n==================================================================\n");
    mprintf("          SISTEMA EXPERTO DE TRAPECIO Y SIMPSON SIMPLE           \n");
    mprintf("==================================================================\n");
    mprintf("1. EJ 1: 3 integrales - trapecio + simpson : error y cota teorica del error");
   
    mprintf("0. SALIR\n");
    mprintf("------------------------------------------------------------------\n");
    
    opcion = input("Elige una opción: ");
    
    select opcion
    case 1 then ejercicio1();
   
    case 0 then mprintf("\n¡Éxitos en el examen!\n"); break;
    else mprintf("\nOpción no válida.\n");
    end
end
