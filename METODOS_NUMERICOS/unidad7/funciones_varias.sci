// FUNCIONES EXTRAS:!!!!

function [n,h]=hallar_grado_n_tolerancia(a, b, tolerancia, cota_derivada_fija)
    // 1. Hallar el grado $n$ necesario (Diseño por Tolerancia)
    //En los exámenes, suele aparecer como: 
    //"Determine la cantidad de nodos equiespaciados necesarios para interpolar $f(x)$ con un error menor a $10^{-5}$".
    //Este script utiliza la cota de error del Teorema 34: $|f(x) - p_n(x)| \le \frac{\max|\Phi_n(x)|}{(n+1)!} \max|f^{(n+1)}(\xi)|$
    //Nota: Como Scilab no deriva simbólicamente por defecto, este script asume el "peor caso" de $\Phi_n(x)$ para nodos equiespaciados ($h^{n+1}/4$ según tu PDF para $n=1$5, o la cota general $(b-a)^{n+1}$) y pide al usuario (o estima) la cota de la derivada. 

    // Entradas:
    // a, b: Extremos del intervalo
    // tolerancia: Error máximo permitido (ej: 1e-5)
    // cota_derivada_fija: Valor máximo estimado de la derivada f^(n+1). 
    //                     (En exámenes suelen darte una cota global M, ej: M=100)
    
    // Salidas:
    // n: Grado del polinomio (número de intervalos)
    // h: Espaciamiento resultante
    
    printf("--- Buscando grado n para tolerancia %e ---\n", tolerancia);
    
    n = 1;
    error_est = 1.0;
    
    // Iteramos aumentando n hasta cumplir la tolerancia
    while error_est > tolerancia
        n = n + 1;
        
        // Cota teórica del error para nodos equiespaciados:
        // Error <= ( (b-a)^(n+1) * M ) / ( 4 * (n+1)! )  <-- Aprox. conservadora estándar
        // Nota: El PDF acota h^2/4 para lineal[cite: 278]. 
        // Para n general, usamos la cota estándar (b-a)^(n+1) / (4 * n!) a veces es usada,
        // pero usaremos la más segura: Max|Prod(x-xi)| / (n+1)!
        
        // Factorial de (n+1)
        fact = factorial(n+1);
        
        // Estimación de la parte polinómica (b-a)^(n+1) es una cota muy gruesa
        // pero segura. Para equiespaciados se suele usar h^(n+1).
        // Aquí usamos una iterativa basada en longitud de intervalo:
        longitud = (b - a)^(n + 1);
        
        // Cálculo del error teórico
        error_est = (longitud * cota_derivada_fija) / fact;
        
        // Protección contra bucles infinitos
        if n > 100 then
            printf("No convergió en n=100. Revisa la cota de derivada.\n");
            break;
        end
    end
    
    h = (b - a) / n;
    
    printf("Resultado: Se necesita un polinomio de grado n = %d\n", n);
    printf("Cantidad de nodos necesarios: %d\n", n + 1);
    printf("Espaciamiento h = %f\n", h);
    printf("Error teórico estimado: %e\n", error_est);
endfunction

//=============================================================

function [n, error_estimado] = hallar_grado_necesario(a, b, M_bound, tol)
    /*1. Hallar el grado $n$ necesario (Cota de Error Inversa)El problema teórica: El PDF establece que el error es $\frac{\Phi_n(x)}{(n+1)!}f^{(n+1)}(\xi)$3. En un examen, te darán una cota $M$ para la derivada y te pedirán: "¿Qué grado $n$ garantiza un error $< 10^{-5}$?".La solución: Como despejar $n$ de un factorial es difícil algebraicamente, usamos un script iterativo que prueba grados hasta cumplir la tolerancia.*/

//Nota: En un examen riguroso, ajusta max_phi según si te piden nodos de Chebyshev (ver PDF ) o equiespaciados.
    
    
    
    // a, b: Extremos del intervalo
    // M_bound: Cota superior de la derivada |f^(n+1)| (o vector de cotas si varía con n)
    // tol: Tolerancia deseada (ej: 10^-5)
    
    n = 1;
    error_estimado = %inf;
    
    // Iteramos aumentando n hasta que el error sea menor a la tolerancia
    while error_estimado > tol
        // El error máximo con nodos equiespaciados se acota usando h^(n+1)/4
        // Ver PDF [cite: 279-282] para el caso n=1, generalizado aquí.
        // Nota: Una cota más general para (x-x0)...(x-xn) en [a,b] es ((b-a)^(n+1))/(4*(n+1)) aprox
        // Pero usaremos la cota estándar grosera para nodos equiespaciados:
        
        h = (b - a) / n;
        
        // Factorial: (n+1)!
        fact = factorial(n + 1);
        
        // Cota de Phi_n(x). Para equiespaciados suele usarse < h^(n+1) * n! / 4 o similar.
        // Usaremos la cota conservadora del intervalo completo: ((b-a)^(n+1)) / (2^(2n-1)) es para Chebyshev
        // Para equiespaciados, usaremos el peor caso aproximado:
        max_phi = ((b-a)^(n+1)); 
        
        // Calculamos el error teórico
        // Si M_bound es un número fijo, úsalo. Si es una función de n, evalúala.
        if length(M_bound) > 1 then
            M = M_bound(n); // Asume que el usuario pasó un vector de cotas
        else
            M = M_bound;
        end
        
        error_estimado = (max_phi * M) / fact; // Fórmula base 
        
        if error_estimado > tol then
            n = n + 1;
        end
        
        // Seguridad para evitar bucles infinitos
        if n > 20 then
            break; 
        end
    end
    
    printf("Para una tolerancia de %e, se requiere un polinomio de grado n = %d\n", tol, n);
endfunction

//=============================================================

function x_estimado = interpolacion_inversa(x_nodos, y_nodos, y_objetivo)
    //Función Inversa (Hallar raíces de f(x)=k)
    //A veces te piden: "Dada la tabla de valores, estime para qué valor de x la función vale y=0.5". La técnica más directa sugerida por la teoría de Lagrange/Newton es simplemente invertir los ejes: considerar los valores y_i​ como los nodos y los x_i  como los valores de la función, siempre que la función sea monótona en el intervalo.
    
//    .2. Interpolación Inversa (Hallar raíces: $f(x)=k$)El problema: Te dan una tabla de valores y te piden "¿Para qué $x$ la función vale 0.5?".La solución: No necesitas un método nuevo. Simplemente intercambias los ejes. Si $y = f(x)$, entonces $x = f^{-1}(y)$. Construimos un polinomio $P(y)$ usando las $y$ como nodos y las $x$ como valores.

    
    
    // Realiza interpolación inversa intercambiando ejes.
    // x_nodos: vector de nodos originales
    // y_nodos: vector de valores f(xi)
    // y_objetivo: el valor 'y' para el cual queremos hallar 'x' (ej: 0 para raíces)

    // Validar monotonicidad simple (necesario para que la inversa sea función)
    // (Omitido por brevedad, pero en examen verificar que y_nodos crezca o decrezca siempre)

    printf("Calculando x tal que f(x) = %f usando Interpolación Inversa...\n", y_objetivo);
     // Invertimos: Las 'y' son ahora los nodos, las 'x' son los valores
     //=========== todo lo de abajo lo podes saltear si hacemos x_aprox = newton_interp(y_nodes, x_nodes, valor_objetivo);

    // PASO CLAVE: Invertimos los roles de X e Y
    // Ahora 'y_nodos' son nuestros puntos en el eje horizontal
    n = length(y_nodos);
    
    // Calculamos Diferencias Divididas (Newton) para el sistema INVERTIDO
    // Usamos la lógica de Tabla 1 del PDF [cite: 181]
    D = zeros(n, n);
    D(:,1) = x_nodos'; // La primera columna son los x (que ahora son los valores f)
    
    for j = 2:n
        for i = 1:n-j+1
            // f[y_i...y_i+k] = (f[...y_i+1] - f[...y_i]) / (y_i+k - y_i)
            numerador = D(i+1, j-1) - D(i, j-1);
            denominador = y_nodos(i+j-1) - y_nodos(i);
            D(i,j) = numerador / denominador;
        end
    end
    
    // Evaluar el polinomio en y_objetivo usando Horner (Newton)
    // p(y) = a0 + a1(y-y0) + ...
    
    coeficientes = D(1, :); // La diagonal superior contiene los coeficientes a_i [cite: 133-139]
    x_estimado = coeficientes(n);
    
    for i = n-1:-1:1
        x_estimado = x_estimado * (y_objetivo - y_nodos(i)) + coeficientes(i);
    end
    
    printf("Valor estimado: x = %f\n", x_estimado);

endfunction

//=============================================================

function [val, der] = evaluar_polinomio_y_derivada(x_nodos, y_nodos, x_eval)
    /*3. Derivada del Polinomio InterpoladorTe piden: "Aproxime $f'(2.5)$ usando el polinomio interpolador de los datos...".Tu código actual evalúa $P(x)$. Para evaluar $P'(x)$ sin recurrir a diferencias finitas (que introducen error extra), podemos derivar analíticamente la forma de Newton mientras la evaluamos.Basado en la fórmula de multiplicaciones encajadas del PDF6, aplicamos la regla del producto recursiva.Si $P(x) = (\dots((a_n(x-x_{n-1}) + a_{n-1})(x-x_{n-2}) + \dots + a_0$, podemos computar valor y derivada simultáneamente.*/
    
    
    // Calcula P(x) y P'(x) en un punto x_eval usando Diferencias Divididas de Newton.
    
    n = length(x_nodos);
    
    

    
    // 1. Calcular Diferencias Divididas (Coeficientes a_i)
    D = zeros(n, n);
    D(:,1) = y_nodos';
    for j = 2:n
        for i = 1:n-j+1
            D(i,j) = (D(i+1, j-1) - D(i, j-1)) / (x_nodos(i+j-1) - x_nodos(i));
        end
    end
    a = D(1, :); // Coeficientes a0, a1, ..., an
    
    // 2. Algoritmo de Horner Modificado para Derivadas
    // Inicialización
    val = a(n); // El coeficiente de mayor grado
    der = 0;    // La derivada de una constante es 0
    
    // Recorremos hacia atrás desde a_(n-1) hasta a_0
    for i = n-1:-1:1
        // Regla del producto: d/dx [ val * (x - xi) + ai ] 
        // = val' * (x - xi) + val * 1 + 0
        
        der = der * (x_eval - x_nodos(i)) + val;
        val = val * (x_eval - x_nodos(i)) + a(i);
    end
    
    printf("En x = %f:\n", x_eval);
    printf("  P(x)  = %f\n", val);
    printf("  P deriv(x) = %f (Aproximación de la derivada)\n", der);
    
endfunction



/*
Resumen de uso para el examen
¿Cuántos puntos necesito? → Usa hallar_grado_necesario. Necesitas tener una idea de la magnitud de la derivada (usa el valor máximo de f 
(n)
  si te dan la función).

¿Para qué x ocurre este y? → Usa interpolacion_inversa.

¿Velocidad/Tasa de cambio (Derivada)? → Usa evaluar_polinomio_y_derivada. Esto es mucho más preciso que hacer (P(x+h)−P(x))/h.
*/


// --- TEST 1: Hallar Grado n (Caso e^x) ---


// Parámetros del problema
a = 0;
b = 1;
tolerancia = 1e-6; // Queremos mucha precisión
M_bound = exp(1);  // La cota máxima de la derivada de e^x en [0,1] es e^1

printf("=== TEST 1: Cota de Error para e^x ===\n");

// Llamada a tu función
[n_necesario, error_teorico] = hallar_grado_necesario(a, b, M_bound, tolerancia);

// Verificación visual
printf("\nINTERPRETACIÓN:\n");
printf("Para interpolar e^x en [0,1] con error < %e,\n", tolerancia);
printf("tu función dice que necesitas grado n = %d.\n", n_necesario);
printf("(Esto implica usar %d nodos equiespaciados).\n", n_necesario + 1);
printf("--------------------------------------------\n\n");

// 1. Definir parámetros
a = 0;
b = 1;
tol = 1e-6;
cota_derivada = 3; // e^1 es approx 2.718, usamos 3 por seguridad

// 2. Llamar a la función
[n_necesario, h_paso] = hallar_grado_n_tolerancia(a, b, tol, cota_derivada);

// Salida esperada: Scilab te dirá que n es alrededor de 7 u 8.
// Esto significa que necesitás 8 o 9 nodos.

printf("--------------------------------------------\n\n");

// --- TEST 2: Interpolación Inversa (Raíz de 7) ---


// Tabla de datos (y = x^2)
x_datos = [1, 2, 3, 4];
y_datos = [1, 4, 9, 16]; 
y_objetivo = 7; // Queremos saber la raíz de 7

printf("=== TEST 2: Interpolación Inversa ===\n");
printf("Datos conocidos: y = x^2 en puntos 1, 2, 3, 4\n");

// Llamada a tu función
x_calc = interpolacion_inversa(x_datos, y_datos, y_objetivo);

// Comprobación
valor_real = sqrt(7);
error_real = abs(valor_real - x_calc);

printf("\nVERIFICACIÓN:\n");
printf("Valor calculado por interpolación: %f\n", x_calc);
printf("Valor real (sqrt(7)):             %f\n", valor_real);
printf("Diferencia (Error):                %e\n", error_real);
printf("--------------------------------------------\n\n");


// 1. Datos de tabla (La función es monótona creciente, así que es invertible)
x_nodos = [1.5, 2.0, 2.5, 3.0];
y_nodos = [-0.125, 0.693, 1.250, 1.701]; // Supongamos que f(x) cruza el cero cerca de 1.6

// 2. Queremos saber x cuando y = 0.5 (por ejemplo) o y = 0
y_objetivo = 0.5;

// 3. Llamar a la función inversa
raiz_estimada = interpolacion_inversa(x_nodos, y_nodos, y_objetivo);

printf("Para y = %f, el x estimado es %f\n", y_objetivo, raiz_estimada);

printf("--------------------------------------------\n\n");

// --- TEST 3: Valor y Derivada (Ejemplo PDF) ---

// Datos del Ejemplo 2 del PDF
x_nodos = [0, 1, 2];
y_nodos = [1, -1, 7];
x_eval = 1; // Evaluamos en uno de los nodos para verificar fácil

printf("=== TEST 3: Derivada Analítica del Polinomio ===\n");
printf("Polinomio esperado: 5x^2 - 7x + 1\n");
printf("Derivada esperada:  10x - 7\n");
printf("Evaluando en x = %f...\n\n", x_eval);

// Llamada a tu función
[p_val, p_der] = evaluar_polinomio_y_derivada(x_nodos, y_nodos, x_eval);

// Comprobación manual
teorico_val = 5*(x_eval^2) - 7*x_eval + 1;
teorico_der = 10*x_eval - 7;

printf("\nCOMPARACIÓN:\n");
printf("Tu función -> P(x): %f,  P''(x): %f\n", p_val, p_der);
printf("Teórico    -> P(x): %f,  P''(x): %f\n", teorico_val, teorico_der);

if abs(p_der - teorico_der) < 1e-10 then
    printf("\n¡ÉXITO! La derivada coincide perfectamente.\n");
else
    printf("\nCUIDADO: Hay una discrepancia en la derivada.\n");
end
printf("--------------------------------------------\n");

/*Enunciado típico:"Se midió la posición de un proyectil en distintos instantes de tiempo. Aproxime la velocidad instantánea ($v = \frac{dp}{dt}$) en $t = 2.5$ segundos usando un polinomio interpolante."Teoría:En lugar de interpolar y luego derivar numéricamente (lo cual suma error), derivamos la estructura del polinomio de Newton analíticamente mientras lo evaluamos.*/

// 1. Datos del problema (Tiempo vs Posición)
t = [0, 1, 2, 3, 4];       // Nodos (x)
posicion = [0, 10, 28, 56, 90]; // Valores (y)

t_eval = 2.5; // Queremos la velocidad justo acá

// 2. Llamar a la función que devuelve valor y derivada
[p_val, p_der] = evaluar_polinomio_y_derivada(t, posicion, t_eval);

printf("Resultados en t = %f segundos:\n", t_eval);
printf("  Posición estimada: %f metros\n", p_val);
printf("  Velocidad estimada: %f m/s\n", p_der);
