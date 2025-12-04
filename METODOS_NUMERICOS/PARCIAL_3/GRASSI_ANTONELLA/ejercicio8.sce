// ANTONELLA GRASSI
// PRACTICA 8 - INTEGRACIÒN NUMÈRICA 

//============= FUNCIONES AUXILIARES
//funcprot(0);

//Regla de Simpson compuesta
function w = simpson_comp(f, a, b, n)
    // Validación: n debe ser par para Simpson
    if modulo(n, 2) <> 0 then
        error("El número de intervalos n debe ser PAR para la regla de Simpson.");
    end
    
    h = (b - a)/n;
    w = f(a) + f(b);
    for i = 1 : n-1
        x = a + h*i;
        if modulo(i, 2) == 0 then
            w = w + 2*f(x);
        else
            w = w + 4*f(x);
        end
    end
    w = w*h/3;
endfunction

function analizar_caso_simpson(f, a, b, n, nombre)
        aprox = simpson_comp(f, a, b, n);
        real = intg(a, b, f);
        err_real = abs(real - aprox);
        
        // Cota Teórica Simpson (Usa derivada 4ta)
        M4 = ObtenerCotaMaxima(f, a, b, 4);
        if isinf(M4) then cota = %inf; else cota = ((b-a)^5 / (180 * n^4)) * M4; end
        
        mprintf("\n%s [n=%d]\n", nombre, n);
        mprintf("   Aprox: %.8f | Exacto: %.8f\n", aprox, real);
        mprintf("   Error Real:   %.2e\n", err_real);
        
        if isinf(cota) then
            mprintf("   Cota Teórica: NO EXISTE (Derivada -> Inf)\n")
        // Caso especial para polinomios cubicos donde derivada 4ta es 0 teoricamente
        elseif M4 < 1e-9 then 
            mprintf("   Cota Teórica: 0.00e+00 (Exacto para grado <= 3)\n")
        else
            mprintf("   Cota Teórica: %.2e (M4 approx: %.2f)\n", cota, M4)
            
            if err_real <= cota * 1.01 + 1e-14 then 
                mprintf("   >> Verificación: OK\n")
            else 
                mprintf("   >> Verificación: REVISAR\n")
            end
        end

        
endfunction

// Calcula derivada numérica de orden 'orden' en el punto 'x'
function d = DerivadaNum(f, x, orden)
    h = 0.001; 
    if orden == 2 then
        d = (f(x+h) - 2*f(x) + f(x-h)) / h^2;
    elseif orden == 4 then
        d = (f(x+2*h) - 4*f(x+h) + 6*f(x) - 4*f(x-h) + f(x-2*h)) / h^4;
    else
        d = 0; // Por seguridad
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

    

// === Funciòn definida para el ejercicio:
function y=f(x),y=1/(2*sqrt(x)),endfunction



// ============ RESOLUCIÒN DEL EJERCICIO ===========

a=1 ; b=3; n=4;
valor_real= sqrt(3);

// --- INCISO A : Aproximación de sqrt(3) con n=4 ---


//nota como tenemos el dato que sqrt(3)-1 = integral de a=1 a b=3 de f , entonces realizamos el mètodo de simpson con la integral de a=1 a b=3 de f , y a ese resultado le sumamos 1
//Es decir, estamos haciendo: sqrt(3) = (integral de a=1 a b=3 de f) +1
aproximacion=simpson_comp(f,a,b,n)+1;
mprintf(" Aproximaciòn con n=%d: %.8f (Error: %.2e)\n", n, aproximacion, abs(valor_real - aproximacion));

// --- INCISO B: Determinar n necesaria para que error < 10^6 ---
tol = 10^-6;
    
// Formula Error Simpson: |E| <= ((b-a)^5 * M4) / (180 * n^4)
// Despeje: n^4 >= ((b-a)^5 * M4) / (180 * tol)
//          n >= raiz_cuarta( ... )
M4 = ObtenerCotaMaxima(f, a, b, 4);
mprintf("   M4 calculado (max|f(4)|): %.2f\n", M4);
    
numerador = (b - a)^5 * M4;
denominador = 180 * tol;
    
n_min = (numerador / denominador)^(1/4); // Raíz cuarta
n_final = ceil(n_min); // Redondear hacia arriba
    
// AJUSTE DE PARIDAD: Simpson necesita n PAR
if modulo(n_final, 2) <> 0 then
   n_final = n_final + 1;
   mprintf("   (Ajustando a par: n teórico %.2f -> %d)\n", n_min, n_final);
end
    
    
mprintf("   n teórico > %.4f  --> Usamos n = %d\n", n_min, n_final);
    
    
// --- INCISO C: Comprobar resultado en SCILAB  ---
aprox_check = simpson_comp(f, a, b, n_final)+1;
err_check = abs(valor_real - aprox_check);
mprintf("   Verificación (n=%d) -> Error Real: %.2e\n", n_final, err_check);
    
if err_check < tol then
    mprintf("   >> ÉXITO: El error está por debajo de la tolerancia.\n");
    mprintf("VALOR CALCULADO CON n=%d : %.8f \n",n_final,aprox_check);
else
    mprintf("   >> CUIDADO: El error sigue siendo alto (revisar cálculo).\n");
end

// ============ RESULTADOS OBTENIDOS ==============

//Aproximaciòn con n=4: 1.73228102 (Error: 2.30e-04)
//   M4 calculado (max|f(4)|): 3.28
//   n teórico > 27.6332  --> Usamos n = 28
//   Verificación (n=28) -> Error Real: 1.31e-07
//   >> ÉXITO: El error está por debajo de la tolerancia.
//VALOR CALCULADO CON n=28 : 1.73205094 
