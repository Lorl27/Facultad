clc(); clear();

// ==========================================================
// 1. HERRAMIENTA GENÉRICA: SIMPSON 2D
// ==========================================================
// Esta función te sirve para CUALQUIER ejercicio de integral doble
// f: la función z = f(x,y)
// a, b: límites en X
// nx: número de subintervalos en X (DEBE SER PAR)
// c, d: límites en Y
// ny: número de subintervalos en Y (DEBE SER PAR)

function I = Simpson2D(f, a, b, nx, c, d, ny)
    // Validación de paridad
    if (modulo(nx, 2) <> 0) | (modulo(ny, 2) <> 0) then
        error("Simpson 2D requiere que nx y ny sean PARES.");
    end

    hx = (b - a) / nx;
    hy = (d - c) / ny;
    
    suma_total = 0;
    
    // Recorremos la grilla/malla (i para x , j para y)
    for i = 0:nx
        x = a + i*hx;
        
        // Determinar peso en X (Simpson 1D: 1, 4, 2, 4, ..., 1)
        if i == 0 | i == nx then
            wx = 1;
        elseif modulo(i, 2) <> 0 then
            wx = 4; // impar
        else
            wx = 2; // par
        end
        
        for j = 0:ny
            y = c + j*hy;
            
            // Determinar peso en Y (1,4,2,4...1)
            if j == 0 | j == ny then
                wy = 1;
            elseif modulo(j, 2) <> 0 then
                wy = 4; // impar
            else
                wy = 2; // par
            end
            
            // El peso conjunto es el producto
            W = wx * wy;
            
            suma_total = suma_total + W * f(x, y);
        end
    end
    
    // Fórmula final: (hx * hy / 9) * Suma
    I = (hx * hy / 9) * suma_total;
endfunction


// ==========================================================
// 2. HERRAMIENTA PARA "VALOR EXACTO"  de integrales dobles.
// ==========================================================
// Scilab no tiene una función "intg2d" directa simple, pero podemos
// anidar dos intg. Esto calcula el valor real numéricamente.

function valor = IntegralDobleExacta(func, a, b, c, d)
    // Definimos la integral interna como una función de y
    // intg(a, b, f, y) le pasa 'y' como argumento extra a f(x,y)
    function r = interna(y) // r(y)= integral de f(x,y) dx
        r = intg(a, b, list(func, y)); 
    endfunction
    
    // Calculamos la integral externa sobre 'interna'  //r(y) dy)
    valor = intg(c, d, interna);
endfunction


// ==========================================================
// 3. RESOLUCIÓN DEL EJERCICIO 5
// ==========================================================

// Definimos la función del problema: f(x,y) = sin(x + y)
function z = mi_funcion(x, y)
    z = sin(x + y);
endfunction

function ejercicio5_Simpson()
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO 5: Simpson 2D (Doble integral)\n");
    mprintf("=================================================\n");

    // Configuración del problema
    // Integral de 0 a 2 (dy) de la Integral de 0 a 1 (dx)
    // OJO: En la notación matemática Int_0^2 Int_0^1 sin(x+y) dx dy
    // dx es la interna (0 a 1), dy es la externa (0 a 2).
    
    // X (interna) de 0 a 1
    a = 0; b = 1; 
    nx = 2; // Intervalos pares
    
    // Y (externa) de 0 a 2
    c = 0; d = 2; 
    ny = 2; // Intervalos pares
    
    // 1. Calcular con Simpson 2D
    aprox_simp = Simpson2D(mi_funcion, a, b, nx, c, d, ny);
    
    // 2. Calcular "Exacto" usando Scilab (sin hacerlo a mano)
    val_scilab = IntegralDobleExacta(mi_funcion, a, b, c, d);
    
    
    mprintf("Función: sin(x+y)\n");
    mprintf("Dominio: x=[0,1], y=[0,2] con malla 2x2\n\n");
    mprintf("----------------------------------------\n");
    mprintf("Malla: nx=%d, ny=%d\n", nx, ny);
    mprintf("----------------------------------------\n");
    mprintf("Valor Simpson 2D:   %.10f\n", aprox_simp);
    mprintf("Valor Scilab (ref): %.10f\n", val_scilab);
    mprintf("----------------------------------------\n");
    mprintf("Error Absoluto:     %.2e\n", abs(val_scilab - aprox_simp));
     mprintf("\n--- Explicación del cálculo ---\n");
    mprintf("Simpson 2D usa pesos combinados.\n");
    mprintf("Esquinas pesan 1, bordes 4, centro 16 (para n=2).\n");
    mprintf("Factor común: (hx*hy)/9\n");
    
    /*ota sobre los pesos de Simpson 2D:En una malla $2\times2$ (como pide el ejercicio), los pesos que aplica el código son:$\begin{bmatrix} 1 & 4 & 1 \\ 4 & 16 & 4 \\ 1 & 4 & 1 \end{bmatrix}$$*/
    
    /* es mejor simpson 2D porque tiene un error menor (orden h^4} mientras que, trapecio 2d tiene un error de orden h^2*/
    
endfunction

// Ejecutar
ejercicio5_Simpson();
