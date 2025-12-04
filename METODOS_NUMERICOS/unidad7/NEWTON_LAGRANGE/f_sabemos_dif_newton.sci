clc; clear;

// ==========================================
// 1. DATOS DEL ENUNCIADO
// ==========================================
// Nodos x_i
x_nodos = [-1, 1, 2, 4];

// Diferencias Divididas DADAS (f[x0], f[x0,x1], etc.)
// Estos son directamente los coeficientes a0, a1, a2, a3
coefs = [2, 1, -2, 2]; 

// ==========================================
// 2. INCISO A: Construir Polinomio P3(x)
// ==========================================

// Variable simbólica para armar el polinomio real
x_sym = poly(0, "x"); 

P3 = coefs(1); // Empezamos con a0
termino_acumulado = 1;

// String para mostrar la fórmula visualmente (como en papel)
str_poly = string(coefs(1));

for k = 2:length(coefs)
    // Multiplicamos por (x - x_{k-1})
    // Ojo: k-1 porque el primer nodo en vector es índice 1 pero en fórmula es x0
    nodo_anterior = x_nodos(k-1);
    termino_acumulado = termino_acumulado * (x_sym - nodo_anterior);
    
    // Sumamos al polinomio: ak * (x-x0)...
    P3 = P3 + coefs(k) * termino_acumulado;
    
    // Construcción visual del texto
    signo = "+";
    if coefs(k) < 0 then signo = ""; end // El menos ya viene en el número
    
    parte_nodos = "";
    for j=1:k-1
        parte_nodos = parte_nodos + sprintf("(x - %.0f)", x_nodos(j));
    end
    
    str_poly = str_poly + sprintf(" %s %.0f%s", signo, coefs(k), parte_nodos);
end

mprintf("=== INCISO A: Polinomio Interpolante P3(x) ===\n");
mprintf("Forma de Newton (Visual):\n");
mprintf("P3(x) = %s\n\n", str_poly);

mprintf("Polinomio expandido (Scilab):\n");
disp(P3);


// ==========================================
// 3. INCISO B: Estimar f(0)
// ==========================================
val_eval = 0;
estimacion = horner(P3, val_eval);

mprintf("\n=== INCISO B: Estimación en x = 0 ===\n");
mprintf("f(0) ≈ P3(0) = %.4f\n", estimacion);


// ==========================================
// 4. INCISO C: Cota de Error
// ==========================================
// Datos dados: |f''''(x)| <= 33.6 en [-1, 4]
M4 = 33.6; 
n_grado = 3; // El polinomio es de grado 3

// Formula del error: E <= (M4 / 4!) * |(x-x0)(x-x1)(x-x2)(x-x3)|
// Evaluado en x = 0

// Calculamos el producto de los nodos: |(0 - -1)(0 - 1)(0 - 2)(0 - 4)|
prod_nodos = 1;
for i = 1:length(x_nodos)
    prod_nodos = prod_nodos * abs(val_eval - x_nodos(i));
end

// Factorial de (n+1) = 4!
fact_4 = factorial(n_grado + 1);

Cota = (M4 / fact_4) * prod_nodos;

mprintf("\n=== INCISO C: Cota de Error ===\n");
mprintf("Dato: M4 = %.1f\n", M4);
mprintf("Producto de nodos en x=0: |(0+1)(0-1)(0-2)(0-4)| = %d\n", prod_nodos);
mprintf("Factorial 4! = %d\n", fact_4);
mprintf("Cota Superior = (%.1f / %d) * %d\n", M4, fact_4, prod_nodos);
mprintf(">> ERROR <= %.4f\n", Cota);
