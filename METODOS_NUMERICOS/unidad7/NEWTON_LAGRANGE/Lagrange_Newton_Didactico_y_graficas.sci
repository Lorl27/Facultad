//clc; clear; xdel(winsid()); // Limpiar todo

// ======================================================
// 1. FUNCIÓN LAGRANGE DIDÁCTICA (Muestra el armado)
// ======================================================
function Pol = LagrangeDidactico(x, y)
    n = length(x);
    Pol = 0;
    x_poly = poly(0, "x"); // Variable simbólica
    
    mprintf("\n=== DETALLE MÉTODO DE LAGRANGE ===\n");
    mprintf("Formula: P(x) = Suma( y_k * L_k(x) )\n\n");
    
    for k = 1:n
        // 1. Construir L_k(x)
        // Numerador: producto de (x - xj) para j != k
        raices = [x(1:k-1) x(k+1:n)];
        Numerador = poly(raices, "x", "roots");
        
        // Denominador: evaluar Numerador en x(k)
        Denominador = horner(Numerador, x(k));
        
        L_k = Numerador / Denominador;
        
        // 2. Termino actual: y_k * L_k
        Termino = y(k) * L_k;
        
        // Mostrar pasos en consola
        mprintf("--- k=%d (Nodo x=%.2f, y=%.4f) ---\n", k, x(k), y(k));
        mprintf("L_%d(x) (coeficientes): ", k); disp(coeff(L_k));
        mprintf("Termino %d agregado al polinomio:\n", k);
        disp(Termino);
        
        // 3. Acumular suma
        Pol = Pol + Termino;
    end
    
    mprintf("\n>> POLINOMIO FINAL LAGRANGE (Simplificado):\n");
    disp(Pol);
endfunction

// ======================================================
// 2. FUNCIÓN NEWTON DIDÁCTICA (Tabla + Formas)
// ======================================================
function Pol = NewtonDidactico(x, y)
    n = length(x);
    // Matriz D para la tabla de diferencias divididas
    // Col 1: orden 0, Col 2: orden 1, etc.
    D = zeros(n, n);
    D(:,1) = y'; 
    
    // Cálculo de la tabla
    for j = 2:n // columnas (orden de diferencia + 1)
        for i = 1:n-j+1 // filas
            // Formula recursiva: (D_abajo - D_arriba) / (x_lejos - x_cerca)
            numerador = D(i+1, j-1) - D(i, j-1);
            denominador = x(i+j-1) - x(i);
            D(i,j) = numerador / denominador;
        end
    end
    
    mprintf("\n=== DETALLE MÉTODO DE NEWTON ===\n");
    mprintf("Tabla de Diferencias Divididas:\n");
    mprintf("(Col 1 = y, Col 2 = 1ras dif, Col 3 = 2das dif...)\n\n");
    disp(D);
    
    // Construcción del Polinomio
    x_poly = poly(0, "x");
    Pol = 0;
    Termino_Acumulado = 1; // Esto será (x-x0)(x-x1)...
    
    // String para mostrar la "Forma Escalonada" visualmente
    str_poly = string(D(1,1)); 
    
    Pol = D(1,1); // Primer término (a0)
    
    for i = 2:n
        // Factor (x - x_{i-1})
        Termino_Acumulado = Termino_Acumulado * (x_poly - x(i-1));
        
        // Coeficiente de la diagonal superior de la tabla
        Coef = D(1, i);
        
        // Sumar al polinomio real (Scilab lo simplificará)
        Pol = Pol + Coef * Termino_Acumulado;
        
        // Construir string para visualización
        signo = "+";
        if Coef < 0 then signo = ""; end // El menos ya viene en el numero
        str_poly = str_poly + sprintf(" %s %.4f", signo, Coef);
        
        // Agregar los factores (x-x0)... al string
        for k=1:i-1
            str_poly = str_poly + sprintf("*(x - %.2f)", x(k));
        end
    end
    
    mprintf("\n>> FORMA ESCALONADA (Newton visual):\n");
    mprintf("P(x) = %s\n", str_poly);
    
    mprintf("\n>> POLINOMIO FINAL NEWTON (Simplificado/Normal):\n");
    disp(Pol);
endfunction


// ======================================================
// 3. EJECUCIÓN CON TUS DATOS (e^x)
// ======================================================

// Datos del ejercicio (puedes cambiarlos aquí)
x_datos = [0, 0.2, 0.4, 0.6]; 
y_datos = [1.0, 1.2214, 1.4918, 1.8221];

// A) Ejecutar Lagrange Didáctico
P_Lagrange = LagrangeDidactico(x_datos, y_datos);

// B) Ejecutar Newton Didáctico
P_Newton = NewtonDidactico(x_datos, y_datos);


// ======================================================
// 4. GRAFICACIÓN
// ======================================================
// Definir rango de ploteo (un poco más amplio que los datos)
rango = linspace(min(x_datos)-0.1, max(x_datos)+0.1, 100);

clf(); // Limpiar figura
plot(rango, horner(P_Lagrange, rango), "r", "Thickness", 2); // Polinomio
plot(x_datos, y_datos, "k.", "MarkerSize", 3); // Puntos originales

// Configuración estética
a = gca();
a.x_location = "origin";
a.y_location = "origin";
title("Polinomio Interpolador (e^x)", "fontsize", 3);
legend(["Polinomio Interpolante"; "Datos (Nodos)"], 2);
xgrid();

mprintf("\n\n-- Grafico generado --\n");
