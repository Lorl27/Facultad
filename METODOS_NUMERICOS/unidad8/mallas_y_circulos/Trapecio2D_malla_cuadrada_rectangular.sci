clc(); clear();

// ==========================================================
// 1. FUNCIÓN GENÉRICA: TRAPECIO 2D
// ==========================================================
// Aproxima la integral doble de f(x,y) en el rectángulo [a,b]x[c,d]
// nx, ny: número de subintervalos en cada eje
function I = Trapecio2D(f, a, b, nx, c, d, ny)
    hx = (b - a) / nx;
    hy = (d - c) / ny;
    
    suma_total = 0;
    
    // Recorremos la malla de puntos
    for i = 0:nx
        x = a + i*hx;
        // Peso en X: 1 en extremos, 2 en el interior
        if i==0 | i==nx then wx = 1; else wx = 2; end
        
        for j = 0:ny
            y = c + j*hy;
            // Peso en Y: 1 en extremos, 2 en el interior
            if j==0 | j==ny then wy = 1; else wy = 2; end
            
            // El peso conjunto es el producto de pesos (1, 2 o 4)
            peso_nodo = wx * wy;
            
            suma_total = suma_total + peso_nodo * f(x, y);
        end
    end
    
    // Fórmula final: (hx * hy / 4) * SumaPonderada
    I = (hx * hy / 4) * suma_total;
endfunction


// ==========================================================
// 2. FUNCIONES DEL EJERCICO 5
// ==========================================================
function z = f_ej5(x, y)
    z = sin(x + y);
endfunction


// ==========================================================
// 3. RESOLUCIÓN DEL EJERCICIO 5
// ==========================================================

function ejercicio5()
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO 5: Trapecio 2D (Doble Integral)\n");
    mprintf("=================================================\n");
    
    
    //Para resolver este ejercicio de integracion doble numérica, se usa el método del trapecio extendido a 2 dimensiones - inegacion numérca en dominio bidemsional - una integral doble en un dominiio rectangular R=[a,b]x[c,d] se puede approximar aplicando la regla de cuadratura en un eje y, luego, en el otro.Para la Regla del trapecio con una malla regular, la fórmula es una suma ponderada donde los puntos de las esquinas pesan 1, los bordes pesan 2 y los interiores, 4.
    
    /* La ponderación de los nodos funciona asi (producto de pesos del trapecio 1D):
    - Esquinas (0,0)(1,0)... : peso 1x1 = 
    - Bordes(0.5,0),(0,1)...: 2x1=2
    -Centro (0.5,1): Peso 2x2=4
    
    El resultado final se multiplica por (hx*hy)/4  */
    
    // La integral es :  I= integral de 0 a 2 [ integral de 0 a 1 (sin(x+y) dx] dy
    
    // Límites de integración
    // Inner dx: x va de 0 a 1
    a = 0; b = 1; 
    nx = 2; // 2 intervalos en x
    
    // Outer dy: y va de 0 a 2
    c = 0; d = 2; 
    ny = 2; // 2 intervalos en y
    
    // 1. Calcular Aproximación
    aprox = Trapecio2D(f_ej5, a, b, nx, c, d, ny);
    
    // 2. Calcular Valor Exacto (Analítico)
    // Int(sin(x+y) dx) = [-cos(x+y)] de 0 a 1 = cos(y) - cos(y+1)
    // Int((cos(y) - cos(y+1)) dy) de 0 a 2 = [sin(y) - sin(y+1)] de 0 a 2
    // = (sin(2) - sin(3)) - (sin(0) - sin(1)) = sin(2) - sin(3) + sin(1)
    val_real = sin(2) - sin(3) + sin(1);
    
    mprintf("Integral: Int_0^2 Int_0^1 sin(x+y) dx dy\n");
    mprintf("Malla: nx=%d, ny=%d\n\n", nx, ny);
    
    mprintf("   Valor Aproximado (Trapecio 2D): %.8f\n", aprox);
    mprintf("   Valor Exacto (Analítico):       %.8f\n", val_real);
    mprintf("   Error Absoluto:                 %.2e\n", abs(val_real - aprox));
    
    // Detalle de los nodos para que veas qué calculó
    mprintf("\n--- Detalle de la malla calculada ---\n");
    hx=(b-a)/nx; hy=(d-c)/ny;
    mprintf("hx = %.2f, hy = %.2f\n", hx, hy);
    mprintf("Puntos evaluados: (0,0), (0.5,0)... hasta (1,2)\n");

endfunction

// Ejecutar
ejercicio5();
