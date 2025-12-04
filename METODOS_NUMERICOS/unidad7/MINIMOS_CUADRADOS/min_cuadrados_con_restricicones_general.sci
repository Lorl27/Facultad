
// ==========================================
// 1. FUNCIONES AUXILIARES
// ==========================================

// Método de Eliminación Gaussiana con pivoteo parcial
function [x, a] = gausselimPP(A, b)
    [nA, mA] = size(A);
    [nb, mb] = size(b);
    a = [A b]; // Matriz aumentada
    n = nA;    

    // Eliminación
    for k = 1:n-1
        kpivot = k; amax = abs(a(k,k));
        for i = k+1:n
            if abs(a(i,k)) > amax then
                kpivot = i; amax = a(i,k);
            end
        end
        temp = a(kpivot,:); a(kpivot,:) = a(k,:);
        a(k,:) = temp;
        
        for i = k+1:n
            factor = a(i,k)/a(k,k);
            for j = k+1:n+1
                a(i,j) = a(i,j) - a(k,j)*factor;
            end
            a(i,k) = 0;
        end
    end

    // Sustitución regresiva
    x(n) = a(n,n+1)/a(n,n);
    for i = n-1:-1:1
        sumk = 0;
        for k = i+1:n
            sumk = sumk + a(i,k)*x(k);
        end
        x(i) = (a(i,n+1)-sumk)/a(i,i);
    end
endfunction
// ==========================================
// 2. FUNCIÓN MÁGICA: ARMA LA MATRIZ SEGÚN POTENCIAS
// ==========================================
function [poly_final, err] = MinCuad_Selectivo(x_datos, y_datos, potencias)
    // x_datos: vector de nodos
    // y_datos: vector de valores
    // potencias: vector con los exponentes que SI queremos (ej: [0, 2, 4])
    
    n_puntos = length(x_datos);
    n_vars = length(potencias);
    
    // 1. Construir matriz A dinámicamente
    A = [];
    for k = 1:n_vars
        p = potencias(k);
        // Agregamos la columna x^p
        A = [A, (x_datos').^p]; 
    end
    
    // 2. Resolver Sistema Normal (A'A)c = A'y
    Matriz_Normal = A' * A;
    Vector_Indep  = A' * y_datos';
    
    [coefs_calc, dump] = gausselimPP(Matriz_Normal, Vector_Indep);
    
    // 3. Reconstruir el polinomio completo (rellenando ceros)
    grado_max = max(potencias);
    coefs_completo = zeros(1, grado_max + 1); // Lleno de ceros inicialmente
    
    // Scilab usa coefs ordenados: [a0, a1, a2...]
    // La potencia 'p' corresponde al índice 'p+1'
    for k = 1:n_vars
        p = potencias(k);
        coefs_completo(p+1) = coefs_calc(k);
    end
    
    poly_final = poly(coefs_completo, "x", "coeff");
    
    // 4. Calcular error
    y_aprox = horner(poly_final, x_datos);
    err = norm(y_aprox - y_datos);
    
    mprintf("\n>> Ajuste con potencias: %s\n", sci2exp(potencias));
    mprintf("   Coeficientes calculados: "); disp(coefs_calc');
    mprintf("   Polinomio final:\n"); disp(poly_final);
endfunction


// ==========================================
// 3. ZONA DE PRUEBAS (MODIFICAR AQUÍ EN EL EXAMEN)
// ==========================================

// Datos del ejercicio anterior
x = [-2.0, -1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6, 2.0];
y = [1.50, 0.99, 0.61, 0.27, 0.02, -0.0096, 0.065, 0.38, 0.63, 0.98, 1.50];

mprintf("=== PRUEBA DE AJUSTES PERSONALIZADOS ===\n");

// CASO 1: Tu pregunta "a0 si exista pero otro no"
// Ejemplo: Modelo y = a0 + a2*x^2 (función par, simétrica)
// Queremos potencias 0 y 2.
potencias1 = [0, 2]; 
[p1, err1] = MinCuad_Selectivo(x, y, potencias1);


// CASO 2: Tu pregunta "x3 es 0"
// Ejemplo: Modelo y = a0 + a1*x + a2*x^2 + a4*x^4 (saltamos el x^3)
potencias2 = [0, 1, 2, 4];
[p2, err2] = MinCuad_Selectivo(x, y, potencias2);


// CASO 3: El ejercicio original (g(0)=0, g'(0)=0 => sin a0 ni a1)
// Modelo y = a2*x^2 + a3*x^3 + a4*x^4
mprintf("=== EJERCICIO 1: Mínimos Cuadrados con Restricciones ===\n");

/*Este es un excelente ejercicio porque introduce restricciones en el problema de Mínimos Cuadrados.No podemos usar la función estándar A_mc (que genera $1, x, x^2...$) tal cual, porque esa función asume que queremos calcular todos los coeficientes ($a_0, a_1...$).El análisis matemático:El polinomio general es: $p_4(x) = a_0 + a_1 x + a_2 x^2 + a_3 x^3 + a_4 x^4$.Como $g(0) = 0 \implies p_4(0) = 0$, entonces $a_0 = 0$.Como $g'(0) = 0 \implies p'_4(0) = 0$. La derivada es $a_1 + 2a_2x...$, al evaluar en 0, queda $a_1 = 0$.Por lo tanto, el modelo que debemos ajustar es reducido: $p_4(x) = a_2 x^2 + a_3 x^3 + a_4 x^4$ Para resolverlo en Scilab reutilizando tu lógica, construiremos manualmente la matriz $A$ solo con las columnas de $x^2, x^3, x^4$ y usaremos tu función gausselimPP para resolver el sistema normal.*/
//Los datos en la tabla aproximan una funci´on desconocida y = g(x) para la cual se conoce
//que g(0) = 0, y g′(0) = 0.


potencias3 = [2, 3, 4];
[p3, err3] = MinCuad_Selectivo(x, y, potencias3);


// ==========================================
// 4. GRAFICAR COMPARACIÓN
// ==========================================
xx = linspace(min(x), max(x), 500);

clf();
plot(x, y, "k.", "MarkerSize", 15); // Datos
plot(xx, horner(p1, xx), "r-", "Thickness", 2);
plot(xx, horner(p2, xx), "g--", "Thickness", 2);
plot(xx, horner(p3, xx), "b-.", "Thickness", 2);

legend(["Datos"; "Solo a0 y a2 (Par)"; "Sin a3"; "Sin a0 ni a1 (Original)"], 2);
title("Comparación de Modelos con Coeficientes Faltantes");
xgrid();

// ===========================
// 5. CALCULO ERROR: 
// ===============
err_norma = norm(horner(p3, x) - y);
mprintf("\nError de ajuste (Norma 2): %.5f\n", err_norma);
