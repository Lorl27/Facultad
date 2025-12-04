clc(); clear();

// ==========================================================
// 1. MOTORES DE INTEGRACIÓN (NO TOCAR)
// ==========================================================

function I = Trapecio2D_Gen(func, a, b, nx, c, d, ny, params)
    hx = (b - a) / nx; hy = (d - c) / ny;
    suma = 0;
    for i = 0:nx
        x = a + i*hx;
        wx = 1; if (i>0 & i<nx) then wx=2; end
        for j = 0:ny
            y = c + j*hy;
            wy = 1; if (j>0 & j<ny) then wy=2; end
            // Pasamos 'params' a la función evaluada
            suma = suma + wx*wy * func(x, y, params);
        end
    end
    I = (hx * hy / 4) * suma;
endfunction

function I = Simpson2D_Gen(func, a, b, nx, c, d, ny, params)
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
            suma = suma + wx*wy * func(x, y, params);
        end
    end
    I = (hx * hy / 9) * suma;
endfunction


// ==========================================================
// 2. FUNCIONES DEL MODELO (INTEGRANDOS)
// ==========================================================

// Estrategia A: Función Indicadora (1 dentro, 0 fuera)
// params = [centro_x, centro_y, radio_cuadrado]
function z = f_indicadora_gen(x, y, p)
    h = p(1); k = p(2); r2 = p(3);
    // Ecuación: (x-h)^2 + (y-k)^2 <= r^2
    if (x - h)^2 + (y - k)^2 <= r2 then
        z = 1;
    else
        z = 0;
    end
endfunction

// Estrategia B: Polar (Jacobiano)
// params no se usa aqui, es siempre r
function z = f_polar_gen(r, t, p)
    z = r; 
endfunction


// ==========================================================
// 3. LA "CALCULADORA UNIVERSAL"
// ==========================================================

function ResolverCirculoGeneral(D, E, F, malla_fina, malla_gruesa)
    // Ecuación General: x^2 + y^2 + Dx + Ey + F <= 0
    
    // 1. COMPLETAR CUADRADOS AUTOMÁTICAMENTE
    // (x + D/2)^2 + (y + E/2)^2 <= (D/2)^2 + (E/2)^2 - F
    h = -D / 2;
    k = -E / 2;
    r_cuadrado = h^2 + k^2 - F;
    
    if r_cuadrado <= 0 then
        error("Los coeficientes no forman un círculo real (Radio^2 <= 0).");
    end
    
    r = sqrt(r_cuadrado);
    
    mprintf("\n=======================================================\n");
    mprintf("   ANALIZADOR DE CÍRCULOS Y ÁREAS NUMÉRICAS\n");
    mprintf("=======================================================\n");
    mprintf("Ecuación: x^2 + y^2 + (%g)x + (%g)y + (%g) <= 0\n", D, E, F);
    mprintf(">> Centro detectado: (%.2f, %.2f)\n", h, k);
    mprintf(">> Radio detectado:  %.4f\n", r);
    
    Valor_Exacto = %pi * r_cuadrado;
    mprintf(">> AREA EXACTA (pi*r^2): %.10f\n", Valor_Exacto);
    
    // --- MÉTODO 1: CARTESIANO (CAJA ENVOLVENTE) ---
    // Límites: [h-r, h+r] x [k-r, k+r]
    a = h - r; b = h + r;
    c = k - r; d = k + r;
    
    // Parámetros para la función indicadora
    params_cart = [h, k, r_cuadrado];
    
    nx = malla_fina; ny = malla_fina; // Malla densa para intentar capturar el borde
    
    mprintf("\n-------------------------------------------------------\n");
    mprintf("ESTRATEGIA 1: CARTESIANA (Caja [%.1f,%.1f]x[%.1f,%.1f])\n", a,b,c,d);
    mprintf("N = %d (Malla densa necesaria por discontinuidad)\n", nx);
    
    T_c = Trapecio2D_Gen(f_indicadora_gen, a, b, nx, c, d, ny, params_cart);
    S_c = Simpson2D_Gen(f_indicadora_gen, a, b, nx, c, d, ny, params_cart);
    
    mprintf("Trapecio: %.6f | Error: %.2e\n", T_c, abs(Valor_Exacto - T_c));
    mprintf("Simpson:  %.6f | Error: %.2e\n", S_c, abs(Valor_Exacto - S_c));
    
    
    // --- MÉTODO 2: POLAR (TRANSFORMACIÓN) ---
    // Límites: r en [0, Radio], theta en [0, 2pi]
    a_p = 0; b_p = r;
    c_p = 0; d_p = 2*%pi;
    
    nx_p = malla_gruesa; ny_p = malla_gruesa; // Con pocos puntos basta
    
    mprintf("\n-------------------------------------------------------\n");
    mprintf("ESTRATEGIA 2: POLAR (Transformación Matemática)\n");
    mprintf("N = %d (Malla gruesa es suficiente)\n", nx_p);
    
    T_p = Trapecio2D_Gen(f_polar_gen, a_p, b_p, nx_p, c_p, d_p, ny_p, 0);
    S_p = Simpson2D_Gen(f_polar_gen, a_p, b_p, nx_p, c_p, d_p, ny_p, 0);
    
    mprintf("Trapecio: %.10f | Error: %.2e\n", T_p, abs(Valor_Exacto - T_p));
    mprintf("Simpson:  %.10f | Error: %.2e\n", S_p, abs(Valor_Exacto - S_p));
    mprintf("-------------------------------------------------------\n");

endfunction


// ==========================================================
// 4. ZONA DE USO (AQUÍ PONES TUS DATOS DEL EXAMEN)
// ==========================================================

// EJEMPLO DEL EJERCICIO 6:
// La ecuación era: x^2 + y^2 <= 2x
// Pasando todo a la izquierda: x^2 + y^2 - 2x <= 0
// Coeficientes: D = -2, E = 0, F = 0

D = -2;
E = 0;
F = 0;

// Configuración de mallas (Fina para cartesiano, Gruesa para polar)
n_fina = 100; 
n_gruesa = 10;

// ¡MAGIA!
ResolverCirculoGeneral(D, E, F, n_fina, n_gruesa);

// OTRO EJEMPLO (Círculo unitario centrado en 0):
// x^2 + y^2 <= 1  --> x^2 + y^2 - 1 <= 0
// ResolverCirculoGeneral(0, 0, -1, 100, 10);




//Si te dan una inecuación rara, solo tienes que despejarla para que quede $\dots \le 0$ e identificar $D, E, F$ .

//Ejemplos:
//"Círculo unitario centrado en el origen": $x^2 + y^2 \le 1$
//      Pasa el 1 restando: $x^2 + y^2 - 1 \le 0$
//    D=0, E=0, F=-1
//"Dominio $x^2 + y^2 \le 2x$" :
//    Pasa el $2x$ restando: $x^2 - 2x + y^2 \le 0$
//    D=-2, E=0, F=0
//"Círculo de radio 3 en (2, -1)": 
//    $(x-2)^2 + (y+1)^2 \le 9$
//    Expandes mentalmente: $x^2 - 4x + 4 + y^2 + 2y + 1 - 9 \le 0$
//    $x^2 + y^2 - 4x + 2y - 4 \le 0$
//    D=-4, E=2, F=-4


