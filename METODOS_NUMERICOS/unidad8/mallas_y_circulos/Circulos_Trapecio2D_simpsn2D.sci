clc(); clear();

// ==========================================================
// 1. HERRAMIENTAS GENÉRICAS 2D (Reutilizadas)
// ==========================================================

// Trapecio 2D
function I = Trapecio2D(f, a, b, nx, c, d, ny)
    hx = (b - a) / nx; hy = (d - c) / ny;
    suma = 0;
    for i = 0:nx
        x = a + i*hx;
        wx = 1; if (i>0 & i<nx) then wx=2; end
        for j = 0:ny
            y = c + j*hy;
            wy = 1; if (j>0 & j<ny) then wy=2; end
            suma = suma + wx*wy * f(x, y);
        end
    end
    I = (hx * hy / 4) * suma;
endfunction

// Simpson 2D (Requiere nx, ny pares)
function I = Simpson2D(f, a, b, nx, c, d, ny)
    if (modulo(nx,2)<>0 | modulo(ny,2)<>0) then error("N debe ser par"); end
    hx = (b - a) / nx; hy = (d - c) / ny;
    suma = 0;
    for i = 0:nx
        x = a + i*hx;
        wx = 1;
        if (i>0 & i<nx) then if modulo(i,2)==0 then wx=2; else wx=4; end; end
        for j = 0:ny
            y = c + j*hy;
            wy = 1;
            if (j>0 & j<ny) then if modulo(j,2)==0 then wy=2; else wy=4; end; end
            suma = suma + wx*wy * f(x, y);
        end
    end
    I = (hx * hy / 9) * suma;
endfunction


// ==========================================================
// 2. DEFINICIÓN DE FUNCIONES
// ==========================================================

/* El dominio D es un circulo pero nuestros metodos de trapecio y simpsion 2D funcionan sobre mallas cuadradas, es decir, rectangulos

La ecuacion x^2}y^2<=2x se reescribe completanto cuadrados como (x-1)^2+y^2<=1 ==> circulo de radio 1 centrado en C(1,0)

Hay 2 estragias:

A. FUERZA BRUTA - CAJA ENVOLVENTE - Integramos  sobre un rectángulo que contenga al ciruclo (epor jemeplo [0,2]x[-1,1]) y definimos la función como 1 si esta adentro y 0, si esta afuera.B - Cambio de variable - pasamos a coords´polares desplazadas para convettir el ciruclo en un rectangulo matematico [0,1]x[0,2T]]*/


// --- ESTRATEGIA A: CARTESIANA (Caja) ---
// Dominio: Rectángulo [0, 2] x [-1, 1]
// Función: 1 si está dentro del círculo, 0 si está fuera.
function z = f_indicadora(x, y)
    // Ecuación: (x-1)^2 + y^2 <= 1
    if (x-1)^2 + y^2 <= 1 then
        z = 1;
    else
        z = 0;
    end
endfunction

// --- ESTRATEGIA B: POLAR (Transformada) ---
// Cambio de variable: x = 1 + r*cos(t), y = r*sin(t)
// Dominio: Rectángulo [0, 1] (radio) x [0, 2pi] (ángulo)
// Función a integrar: El Jacobiano (r)
function z = f_polar(r, t)
    z = r; // Integrando el Jacobiano
endfunction


// ==========================================================
// 3. EJECUCIÓN Y COMPARACIÓN
// ==========================================================
function ejercicio6()
    mprintf("\n=================================================\n");
    mprintf("EJERCICIO 6: Área Círculo Unitario (Valor real = PI)\n");
    mprintf("Valor Exacto (pi): %.10f\n", %pi);
    mprintf("=================================================\n");

    // --- CASO 1: MÉTODO CARTESIANO (Rectángulo que encierra) ---
    // Usamos una malla densa (n=50) porque la función es "escalonada" (discontinua)
    // Simpson sufre mucho con discontinuidades.
    nx = 100; ny = 100;
    a = 0; b = 2;
    c = -1; d = 1;
    
    T_cart = Trapecio2D(f_indicadora, a, b, nx, c, d, ny);
    S_cart = Simpson2D(f_indicadora, a, b, nx, c, d, ny);
    
    mprintf("\n--- ESTRATEGIA 1: CARTESIANA (Malla Fina n=%d) ---\n", nx);
    mprintf("Integramos f=1 dentro del círculo, f=0 fuera.\n");
    mprintf("Trapecio: %.6f | Error: %.2e\n", T_cart, abs(%pi - T_cart));
    mprintf("Simpson:  %.6f | Error: %.2e\n", S_cart, abs(%pi - S_cart));
    mprintf(">> NOTA: El error es alto porque la función salta bruscamente de 0 a 1.\n");

    // --- CASO 2: MÉTODO POLAR (Transformación) ---
    // Usamos una malla pequeña (n=10) para demostrar la eficiencia
    // Aquí integramos f(r,t) = r en el rectángulo [0,1]x[0,2pi]
    nx_p = 10; ny_p = 10;
    
    // r va de 0 a 1
    a_p = 0; b_p = 1;
    // theta va de 0 a 2pi
    c_p = 0; d_p = 2*%pi;
    
    T_pol = Trapecio2D(f_polar, a_p, b_p, nx_p, c_p, d_p, ny_p);
    S_pol = Simpson2D(f_polar, a_p, b_p, nx_p, c_p, d_p, ny_p);
    
    mprintf("\n--- ESTRATEGIA 2: POLAR (Malla Gruesa n=%d) ---\n", nx_p);
    mprintf("Integramos el Jacobiano r en un rectángulo matemático.\n");
    mprintf("Trapecio: %.10f | Error: %.2e\n", T_pol, abs(%pi - T_pol));
    mprintf("Simpson:  %.10f | Error: %.2e\n", S_pol, abs(%pi - S_pol));
    mprintf(">> NOTA: Simpson es casi perfecto porque la función f=r es suave (lineal).\n");

endfunction

ejercicio6();

