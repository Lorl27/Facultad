clc; clear;

// ==========================================
// 1. FUNCIONES NECESARIAS
// ==========================================

// Función para calcular la TABLA de diferencias divididas (Coeficientes)
// Devuelve un vector con la diagonal superior (a0, a1, a2...)
function coef = CoeficientesNewton(x, y)
    n = length(x);
    D = zeros(n, n);
    D(:,1) = y'; // Primera columna son las y
    
    for j = 2:n // Para cada orden de diferencia
        for i = 1:n-j+1
            D(i,j) = (D(i+1,j-1) - D(i,j-1)) / (x(i+j-1) - x(i));
        end
    end
    coef = D(1,:); // Retornamos solo la primera fila (la diagonal superior)
endfunction

// Función para evaluar el Polinomio de Newton usando Horner generalizado
function val = EvalNewton(x_nodos, coef, x_eval)
    n = length(coef);
    val = coef(n); // Empezamos desde el último coeficiente (an)
    
    // Algoritmo de Horner: an*(x-xn-1) + an-1 ...
    for i = n-1:-1:1
        val = val .* (x_eval - x_nodos(i)) + coef(i);
    end
endfunction

// Función de Cota de Error Teórico
function error_teorico = CotaError(x_nodos, x_eval, M)
    // Error <= (M / n!) * |(x-x0)(x-x1)...|
    n = length(x_nodos); // Cantidad de puntos (el grado será n-1)
    
    // Calculamos el producto de los términos (x - xi)
    prod_term = 1;
    for i = 1:n
        prod_term = prod_term * abs(x_eval - x_nodos(i));
    end
    
    error_teorico = (M / factorial(n)) * prod_term;
endfunction


// ==========================================
// 2. RESOLUCIÓN DEL EJERCICIO 4
// ==========================================

// Datos de la tabla
x_datos = [2.0, 2.1, 2.2, 2.3, 2.4, 2.5];
y_datos = [0.2239, 0.1666, 0.1104, 0.0555, 0.0025, -0.0484];

// 1. Construir el polinomio (Obtener coeficientes)
// Usamos todos los puntos (Polinomio de grado 5) para máxima precisión
coeficientes = CoeficientesNewton(x_datos, y_datos);

mprintf("=== EJERCICIO 4: Interpolación de Bessel ===\n");
mprintf("Coeficientes de Newton calculados:\n");
disp(coeficientes);

// Cota de la derivada n (para n=6 puntos, derivada 6ta)
// Sabemos que |J0(x)| <= 1 y sus derivadas oscilan decayendo. 
// En x=2, la derivada 6ta es mucho menor a 1, pero usaremos 1 como cota segura.
M_cota = 1; 
Tolerancia = 0.5 * 10^-6;

// --- EVALUACIÓN EN x = 2.15 ---
x1 = 2.15;
val1 = EvalNewton(x_datos, coeficientes, x1);
err1 = CotaError(x_datos, x1, M_cota);

mprintf("\n--- Caso x = %.2f ---\n", x1);
mprintf("Valor interpolado J0(%.2f) = %.9f\n", x1, val1);
mprintf("Cota de error teórica:       %.2e\n", err1);

if err1 < Tolerancia then
    mprintf(">> CONDICIÓN CUMPLIDA: El error es menor a %.1e\n", Tolerancia);
else
    mprintf(">> CUIDADO: El error teórico es mayor a la tolerancia.\n");
end


// --- EVALUACIÓN EN x = 2.35 ---
x2 = 2.35;
val2 = EvalNewton(x_datos, coeficientes, x2);
err2 = CotaError(x_datos, x2, M_cota);

mprintf("\n--- Caso x = %.2f ---\n", x2);
mprintf("Valor interpolado J0(%.2f) = %.9f\n", x2, val2);
mprintf("Cota de error teórica:       %.2e\n", err2);

if err2 < Tolerancia then
    mprintf(">> CONDICIÓN CUMPLIDA: El error es menor a %.1e\n", Tolerancia);
else
    mprintf(">> CUIDADO: El error teórico es mayor a la tolerancia.\n");
end


// ==========================================
// 3. GENERAR EL POLINOMIO SIMBÓLICO (Para ver la fórmula)
// ==========================================
// Esto es solo visual, para mostrar el polinomio "p" como querías
s = poly(0, "x");
P_sym = 0;
n = length(x_datos);
for i = n:-1:1
    if i == 1 then
        term = 1;
    else
        term = 1;
        for k = 1:i-1
            term = term * (s - x_datos(k));
        end
    end
    P_sym = P_sym + coeficientes(i) * term;
end

mprintf("\nPolinomio Interpolante Resultante:\n");
disp(P_sym);
