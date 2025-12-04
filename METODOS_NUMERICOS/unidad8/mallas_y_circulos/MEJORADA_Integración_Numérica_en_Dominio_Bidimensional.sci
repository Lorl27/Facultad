//Integración Numérica en Dominio Bidimensional
//Tu Trapecio2D actual está bien para rectángulos, pero si el enunciado dice "Triángulo de vértices..." o "Región limitada por $y=x^2$ e $y=x$", usa la función nueva(this).
//Tu limitación:Tus funciones Trapecio2D y Simpson2D asumen estrictamente que los límites son constantes (c y d son números).Si te piden integrar sobre un triángulo (ej: $0 \le y \le x$) o un círculo sin usar "fuerza bruta" (caja envolvente), tu código actual no sirve directamente porque hy cambia para cada $x$.Usar la "función indicadora" (poner ceros afuera) como hiciste en el script ResolverCirculoGeneral funciona, pero destruye la precisión de Simpson (el error sube mucho porque la función deja de ser suave en el borde).

// ==========================================================
// SIMPSON 2D PARA LÍMITES VARIABLES (Dominios Generales)
// ==========================================================
// Calcula: Integral de a a b [ Integral de c(x) a d(x) f(x,y) dy ] dx
// f: funcion z=f(x,y)
// a, b: límites constantes en X
// c_func, d_func: funciones que definen los límites en Y (ej: y=x, y=0)
// nx, ny: número de subintervalos (DEBEN SER PARES)

function I = Simpson2D_LimitesVariables(f, a, b, nx, c_func, d_func, ny)
    
    // Validación de paridad
    if (modulo(nx, 2) <> 0) | (modulo(ny, 2) <> 0) then
        error("Simpson requiere nx y ny PARES.");
    end

    hx = (b - a) / nx;
    
    // Vamos a acumular la suma ponderada de las "Integrales Internas"
    // Es decir, aplicamos Simpson en el eje X sobre la función G(x)
    suma_total_X = 0;

    for i = 0:nx
        xi = a + i * hx; // Nodo actual en X
        
        // 1. DETERMINAR LÍMITES EN Y PARA ESTE Xi
        y_min = c_func(xi);
        y_max = d_func(xi);
        
        // Si los límites son iguales (puntas de un triángulo o círculo), la integral es 0
        if abs(y_max - y_min) < 1e-14 then
            integral_interna = 0;
        else
            hy = (y_max - y_min) / ny;
            
            // 2. CALCULAR INTEGRAL INTERNA (Simpson 1D en Y)
            suma_Y = f(xi, y_min) + f(xi, y_max); // Extremos
            
            for j = 1:ny-1
                yj = y_min + j * hy;
                if modulo(j, 2) == 0 then
                    suma_Y = suma_Y + 2 * f(xi, yj); // Par
                else
                    suma_Y = suma_Y + 4 * f(xi, yj); // Impar
                end
            end
            integral_interna = (hy / 3) * suma_Y;
        end

        // 3. ACUMULAR EN LA INTEGRAL EXTERNA (Simpson 1D en X)
        // Peso de Simpson para la dimensión X
        if i == 0 | i == nx then
            wx = 1;
        elseif modulo(i, 2) == 0 then
            wx = 2;
        else
            wx = 4;
        end
        
        suma_total_X = suma_total_X + (wx * integral_interna);
    end

    // Resultado final
    I = (hx / 3) * suma_total_X;

endfunction


//Ejemplo de Uso (Triángulo)Supongamos que te piden calcular:$\int_0^1 \int_0^x (x^2 + y^2) \, dy \, dx$ Aquí $y$ va desde $0$ hasta $x$.

// 1. Definir integrando
function z = mi_func(x,y)
    z = x^2 + y^2;
endfunction

// 2. Definir límites variables en Y
function y = limite_inferior(x)
    y = 0; // c(x) = 0
endfunction

function y = limite_superior(x)
    y = x; // d(x) = x
endfunction

// 3. Parámetros
a = 0; b = 1;
nx = 10; ny = 10; // Malla 10x10

// 4. Calcular
aprox = Simpson2D_LimitesVariables(mi_func, a, b, nx, limite_inferior, limite_superior, ny);

// 5. Comparar con valor exacto (Analítico = 1/3)
valor_exacto = 1/3; // Integral manual: x^3/3 + x^3/3 ... da 1/3
mprintf("Aproximación: %.8f\n", aprox);
mprintf("Exacto:       %.8f\n", valor_exacto);
mprintf("Error:        %.2e\n", abs(valor_exacto - aprox));

/***-----*/
// ==========================================================
// TRAPECIO 2D PARA LÍMITES VARIABLES
// ==========================================================
// Calcula: Integral de a a b [ Integral de c(x) a d(x) f(x,y) dy ] dx
// Sirve para triángulos, círculos, parábolas, etc.
//
// f: función z = f(x,y)
// a, b: límites constantes en X
// nx: subintervalos en X
// c_func, d_func: funciones para los límites en Y
// ny: subintervalos en Y

function I = Trapecio2D_LimitesVariables(f, a, b, nx, c_func, d_func, ny)
    
    hx = (b - a) / nx;
    suma_total_X = 0;

    // Recorremos X desde x0 hasta xn
    for i = 0:nx
        xi = a + i * hx;
        
        // 1. Calcular límites dinámicos de Y para este x específico
        y_min = c_func(xi);
        y_max = d_func(xi);
        
        // Si el intervalo es un punto (ej: vértices del triángulo), la integral es 0
        if abs(y_max - y_min) < 1e-14 then
            integral_interna = 0;
        else
            hy = (y_max - y_min) / ny;
            
            // 2. Trapecio 1D en Y (Calculamos G(xi))
            // Pesos: 1 en extremos, 2 en el medio
            suma_Y = f(xi, y_min) + f(xi, y_max); 
            
            for j = 1:ny-1
                yj = y_min + j * hy;
                suma_Y = suma_Y + 2 * f(xi, yj);
            end
            
            integral_interna = (hy / 2) * suma_Y;
        end

        // 3. Acumular en Trapecio 1D en X
        // Pesos exteriores: 1 si es el primero/último, 2 si es intermedio
        if i == 0 | i == nx then
            wx = 1;
        else
            wx = 2;
        end
        
        suma_total_X = suma_total_X + (wx * integral_interna);
    end

    // Resultado final (h/2 * suma)
    I = (hx / 2) * suma_total_X;

endfunction

//Integral: ∫ de 0 a 1 , ∫ de 0 a x : (x^2 +y^2 )dydx

// 1. Definir Integrando
function z = mi_func(x, y)
    z = x^2 + y^2;
endfunction

// 2. Definir Límites Variables (Triángulo: y va de 0 a x)
function y = lim_inf(x), y = 0; endfunction
function y = lim_sup(x), y = x; endfunction

// 3. Configuración
a = 0; b = 1;
nx = 10; ny = 10; // Simpson requiere pares, Trapecio no, pero usamos pares para comparar igual.

// 4. Calcular
It = Trapecio2D_LimitesVariables(mi_func, a, b, nx, lim_inf, lim_sup, ny);
Is = Simpson2D_LimitesVariables(mi_func, a, b, nx, lim_inf, lim_sup, ny);

// 5. Análisis
valor_exacto = 1/3; // 0.3333...

mprintf("\n=== COMPARACIÓN EN DOMINIO TRIANGULAR ===\n");
mprintf("Malla: %dx%d\n", nx, ny);
mprintf("Valor Exacto: %.8f\n", valor_exacto);
mprintf("-----------------------------------------\n");
mprintf("Trapecio:     %.8f | Error: %.2e\n", It, abs(valor_exacto - It));
mprintf("Simpson:      %.8f | Error: %.2e\n", Is, abs(valor_exacto - Is));
mprintf("-----------------------------------------\n");

if abs(valor_exacto - Is) < abs(valor_exacto - It) then
    mprintf(">> Simpson fue más preciso (esperado para polinomios suaves).\n");
else
    mprintf(">> Trapecio fue más preciso (raro en este caso).\n");
end
