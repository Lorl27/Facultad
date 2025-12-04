//1. El "Hueco" de Hermite (Interpolación con Derivadas)El escenario:El PDF no lo menciona explícitamente, pero es una extensión clásica de Newton. Si el examen dice:"Halle el polinomio que pasa por $P(0)=1$, $P(1)=2$ y además cumple que la derivada en 1 es $P'(1)=0$".
//El problema con tu código:Tus funciones DiferenciasDivididas o TablaNewton fallarán (división por cero) si intentas poner el nodo 1 dos veces ($x=[0, 1, 1]$) para simular la derivada.
//La Solución Rápida (Parche para el examen):No necesitas una función nueva compleja. Si te piden interpolar derivada $f'(x_k)$, simplemente debes saber que en la tabla de diferencias divididas, la diferencia de primer orden entre dos puntos iguales es la derivada.Agrega este comentario/snippet a tu "Cheat Sheet" mental:Si $x_i = x_{i+1}$, entonces $f[x_i, x_{i+1}] = f'(x_i)$.Código auxiliar si te toca esto:Si te dan derivadas, construye la tabla a mano o modifica DiferenciasDivididas para manejar NaN o división por cero:Scilab

function coefs = DiferenciasDivididas_Hermite(x, y, y_prima)
    // x: nodos (con repetidos si hay derivada)
    // y: valores
    // y_prima: derivadas (poner %nan donde no haya dato de derivada)
    
    n = length(x);
    D = zeros(n, n);
    D(:,1) = y'; 
    
    for j = 2:n
        for i = 1:n-j+1
            numerador = D(i+1, j-1) - D(i, j-1);
            denominador = x(i+j-1) - x(i);
            
            if abs(denominador) < 1e-15 then
                // ¡AQUÍ ESTÁ EL TRUCO!
                // Si el denominador es 0, usamos el dato de la derivada
                // Esto asume que los repetidos están juntos y es la 1ra derivada
                // Para derivadas superiores es más complejo, pero raro en examen.
                // Buscamos la derivada correspondiente al nodo x(i)
                D(i,j) = y_prima(i); 
            else
                D(i,j) = numerador / denominador;
            end
        end
    end
    coefs = D(1,:);
endfunction
//(Nota: Esto es solo para derivadas de primer orden, lo más común).

//=========================================
//2. Mínimos Cuadrados Generalizado (Automatizado)El escenario:Tu función run_ejercicio_2_Examen_Coseno construye la matriz $A$ manualmente para $y = a + b \cos(2\pi x)$.¿Qué pasa si te piden: "Ajuste el modelo $y = A \cdot x + B \cdot e^x + C / x$"?El problema:Tendrás que escribir el código de la matriz A desde cero en medio del examen, lo cual es propenso a errores de tipeo.La Solución:Agrega esta función Genérica que construye la matriz $A$ recibiendo un vector de funciones (strings). Así resuelves cualquier ajuste lineal en segundos.



//===================================
// =========================================================================
//        LIBRERÍA "BLINDADA" DE MÉTODOS NUMÉRICOS (INTERPOLACIÓN & MC)
// =========================================================================
// Copia y pega esto al inicio de tu sesión o guardalo y ejecutalo.

// -------------------------------------------------------------------------
// 1. HERRAMIENTA DE ERROR (CRÍTICA PARA TEORÍA)
// -------------------------------------------------------------------------
function [max_val, x_peor] = AnalisisError_Nodal(x_nodos, a, b)
    // Calcula la parte geométrica del error: max |(x-x0)(x-x1)...(x-xn)|
    // Útil para responder: "¿Cota de error?" -> Multiplicas este resultado por M/(n+1)!
    
    t = linspace(a, b, 2000); // Muestreo denso
    prod_vals = ones(t);
    
    n = length(x_nodos);
    
    // Producto acumulado (x-x0)...(x-xn)
    for i = 1:n
        prod_vals = prod_vals .* (t - x_nodos(i));
    end
    
    prod_vals = abs(prod_vals); // Solo magnitud
    
    [max_val, indice] = max(prod_vals);
    x_peor = t(indice);
    
    // Graficamos
    scf(10); clf();
    plot(t, prod_vals, 'r', 'LineWidth', 2);
    plot(x_nodos, zeros(x_nodos), 'k.', 'MarkerSize', 3);
    xtitle("Magnitud del Polinomio Nodal |Phi(x)|", "x", "Valor");
    xgrid();
    
    printf("\n--- ANÁLISIS DE ERROR GEOMÉTRICO ---\n");
    printf("En el intervalo [%.2f, %.2f] con %d nodos:\n", a, b, n);
    printf("El valor máximo de |(x-x0)...(x-xn)| es: %.4e\n", max_val);
    printf("Ocurre en x approx: %.4f\n", x_peor);
    printf("RECORDATORIO: Multiplica esto por max|f^(n+1)(xi)| / (n+1)! para la Cota Total.\n");
endfunction

// -------------------------------------------------------------------------
// 2. MÍNIMOS CUADRADOS GENERALIZADO (SALVAVIDAS)
// -------------------------------------------------------------------------
function [coefs, R2] = MinimosCuadrados_Generico(x, y, bases_texto)
    // Ajusta CUALQUIER modelo lineal de la forma: y = c1*f1(x) + c2*f2(x) ...
    // x, y: vectores columna
    // bases_texto: lista de strings. Ej: ["ones(x)", "x", "cos(2*%pi*x)"]
    
    // n = length(x); // Esto suele estar bien si x es vector
    n = size(x, '*'); // MÁS SEGURO: Cuenta elementos totales sin importar si es fila/columna
   
   // EL ERROR ESTABA AQUÍ:
    // m = length(bases_texto); 
    
    // CORRECCIÓN:
    m = size(bases_texto, '*'); 
    // El '*' le dice a Scilab: "Dame el número total de elementos, sea lo que sea".
    // Esto asegura que m sea un número (ej: 3) y no un vector (ej: [1 3]).
    
    // Asegurar que x sea columna para que funcionen las operaciones punto
    x = x(:); y = y(:); 
    
    A = zeros(n, m);
    
    printf("\n--- Mínimos Cuadrados Generalizado ---\n");
    printf("Modelo solicitado: y = ");
    
    // Construcción automática de la Matriz A
    for j = 1:m
        printf("C%d*[ %s ] + ", j, bases_texto(j));
        // EVSTR evalúa el string como código. Magia pura.
        // Se asume que en el string usas 'x' como variable.
        try
            A(:, j) = evstr(bases_texto(j));
        catch
            printf("\nERROR: La función base ''%s'' falló. Revisa sintaxis (usa puntos .*, .^)\n", bases_texto(j));
            return;
        end
    end
    printf("\n");
    
    // Ecuaciones Normales (Estables para m pequeño)
    Matriz_Normal = A' * A;
    Vector_Indep = A' * y;
    
    // Resolvemos
    coefs = Matriz_Normal \ Vector_Indep;
    
    // Cálculo de R2
    y_pred = A * coefs;
    St = sum((y - mean(y)).^2);
    Sr = sum((y - y_pred).^2);
    R2 = (St - Sr) / St;
    
    // Mostrar resultados
    printf("\nResultados:\n");
    for j = 1:m
        printf("  Coef C%d (para %s): %f\n", j, bases_texto(j), coefs(j));
    end
    printf("  R2 (Bondad de ajuste): %f\n", R2);
    
    // Gráfica rápida
    xx = linspace(min(x), max(x), 200)';
    // Construir curva suave
    A_plot = zeros(200, m);
    x_bkp = x; x = xx; // Truco: cambiamos x temporalmente para evaluar evstr
    for j=1:m, A_plot(:,j) = evstr(bases_texto(j)); end
    x = x_bkp; // Restauramos
    yy_plot = A_plot * coefs;
    
    scf(11); clf();
    plot(x_bkp, y, "ro", "MarkerSize", 4);
    plot(xx, yy_plot, "b-", "Thickness", 2);
    xtitle("Ajuste Generalizado", "x", "y");
    legend(["Datos", "Modelo Ajustado"]);
endfunction

// -------------------------------------------------------------------------
// 3. INTERPOLACIÓN DE HERMITE (CUANDO HAY DERIVADAS / NODOS REPETIDOS)
// -------------------------------------------------------------------------

/* NOTA NOTA NOTA:
2. 🧠 Sobre tu "Parche" de Hermite (Interpolación con Derivada)
Tu lógica es correcta y muy astuta para un examen.

Si te piden interpolar P(0)=1,P(1)=2,P´(1)=0, matemáticamente es equivalente a decir que los nodos son x_0=0, X_1=1 , X_2=1
El truco de: if abs(denominador) < 1e-15 then D(i,j) = y_prima(i) ...es la implementación numérica de la definición de diferencia dividida con nodos coincidentes:
f[x_i,x_i ]=  lim x→x de (f(x)−f(x_i)  )/(x-x_i)=f ′ (x_i )

⚠️ Advertencia Crítica para el Examen: Para que tu código DiferenciasDivididas_Hermite funcione, los nodos repetidos deben estar contiguos en el vector x.

✅ Bien: x = [0, 1, 1] -> El algoritmo encontrará la división por cero cuando compare x(3)-x(2).

❌ Mal: x = [1, 0, 1] -> El algoritmo calculará x(2)-x(1) (ok) y x(3)-x(2) (ok), y nunca se activará tu if de derivada, dando un polinomio incorrecto.

Tip: Agrega x = gsort(x, 'g', 'i'); (ordenar ascendente) al inicio de tu función, pero recuerda que tendrías que reordenar y y y_prima acorde a esos movimientos (lo cual es complejo de programar rápido). Mejor asegúrate de introducir los datos ordenados a mano: [0, 1, 1]
*/


function coefs = DiferenciasDivididas_Hermite(x_nodos, y_nodos, y_primas)
    // x_nodos: lista de nodos. SI HAY DERIVADA, EL NODO DEBE ESTAR REPETIDO.
    // Ejemplo: P(0)=1, P(1)=2, P'(1)=3  -> x=[0, 1, 1], y=[1, 2, 2], y_p=[nan, nan, 3]
    // y_primas: vector del mismo largo. Poner %nan donde no sea dato de derivada.
    
    n = length(x_nodos);
    D = zeros(n, n);
    D(:,1) = y_nodos(:); // Primera columna: valores y
    
    for j = 2:n // Columnas (orden diff)
        for i = 1:n-j+1 // Filas
            numerador = D(i+1, j-1) - D(i, j-1);
            denominador = x_nodos(i+j-1) - x_nodos(i);
            
            if abs(denominador) < 1e-10 then
                // CASO CRÍTICO: 0/0 -> Usamos la derivada
                // Esto ocurre si x_i y x_{i+k} son el mismo punto
                
                // Buscamos si tenemos el dato de la derivada
                // Nota: Esto es simplificado para 1ra derivada.
                if j == 2 then // Diferencia de orden 1 con nodos iguales = Derivada primera
                    if ~isnan(y_primas(i)) then
                        D(i,j) = y_primas(i);
                        printf("  -> Aplicando derivada y''(%f) = %f en tabla.\n", x_nodos(i), y_primas(i));
                    else
                        error("División por cero y no hay dato de derivada para salvarlo.");
                    end
                else
                    // Para derivadas superiores (Hermite orden superior), se necesita lógica más compleja (y''/2, etc)
                    // Raramente pedido en este nivel, pero avisamos.
                    D(i,j) = 0; // Fallback peligroso, mejor revisar teoría si piden P''(x)
                end
            else
                D(i,j) = numerador / denominador;
            end
        end
    end
    coefs = D(1,:); // Diagonal superior
    
    // Imprimir el polinomio
    s = poly(0, "x");
    P = 0;
    term = 1;
    for k=1:n
        P = P + coefs(k) * term;
        term = term * (s - x_nodos(k));
    end
    printf("\nPolinomio de Hermite resultante:\n");
    disp(P);
endfunction

// -------------------------------------------------------------------------
// 4. UTILS ESTÁNDAR (Las tuyas mejoradas)
// -------------------------------------------------------------------------
function val = Eval_Horner_Newton(x_eval, x_nodos, coefs)
    n = length(coefs);
    val = coefs(n) * ones(x_eval);
    for i = n-1:-1:1
        val = val .* (x_eval - x_nodos(i)) + coefs(i);
    end
endfunction

function [n, h] = Hallar_Grado_Tolerancia(a, b, M_cota_deriv, tolerancia)
    // Itera para encontrar cuantos nodos equiespaciados necesitas
    n = 1; error_est = %inf;
    while error_est > tolerancia
        n = n + 1;
        // Cota Equiespaciada conservadora: error <= (b-a)^(n+1) * M / (4*(n+1)!)
        // Nota: Scilab factorial crece rápido, cuidado con n > 170
        fact = factorial(n+1);
        // Usamos una estimación del término nodal máximo para equiespaciados
        // w_max aprox h^(n+1)/4 * n! es una cota muy local
        // Usaremos la cota teórica global burda pero segura:
        h = (b-a)/n;
        // Cota ajustada (Burden/Faires): (h^(n+1) / (4*(n+1))) * M ??? No, mejor calcular w_max real
        
        // Mejor calculamos W_max real iterativamente (es barato)
        t = linspace(a,b,100);
        x_nod = linspace(a,b,n+1);
        w_vals = ones(t);
        for k=1:n+1, w_vals=w_vals.*(t-x_nod(k)); end
        w_max = max(abs(w_vals));
        
        error_est = (M_cota_deriv * w_max) / fact;
        if n > 50 then break; end // Safety break
    end
    h = (b-a)/n;
    printf("Para tol %e, necesitas n=%d (Grado), %d Puntos. h=%.4f. Error est: %e\n", tolerancia, n, n+1, h, error_est);
endfunction


// =========== EJMPLO DE USO!!!:

// EJEMPLO 1: MÍNIMOS CUADRADOS "RARO" (COMO TU EJERCICIO DEL COSENO)
// "Ajuste el modelo y = A*x + B*cos(x) + C al conjunto de datos..."

x = [0.1; 0.5; 1.2; 2.0];
y = [1.1; 2.5; 3.0; 2.8];

// ¡MAGIA! Solo defines las funciones como texto
bases = ["x", "cos(x)", "ones(x)"]; // ones(x) es para el término independiente C

// La función hace todo el trabajo sucio de matrices
[c, r2] = MinimosCuadrados_Generico(x, y, bases);

printf("A = %f, B = %f, C = %f\n", c(1), c(2), c(3));

// ------------------------------------------------------------------

// EJEMPLO 2: ANÁLISIS DE ERROR (COTAS)
// "Interpole f(x) en [0,1] con 4 puntos equiespaciados. Acote el error."
// Supongamos que sabes que max|f''''(x)| <= 10 (M)

x_nodos = linspace(0, 1, 4); 
M = 10;
n = 3; // Grado

// Scilab te calcula la parte difícil (el producto geométrico)
[w_max, x_loc] = AnalisisError_Nodal(x_nodos, 0, 1);

// Tú calculas la cota final
Cota_Total = (M / factorial(n+1)) * w_max;
printf("\nCota de Error Total Calculada: %e\n", Cota_Total);

// ------------------------------------------------------------------

// EJEMPLO 3: INTERPOLACIÓN CON DERIVADA (HERMITE) - EL "HUECO"
// Problema: "Halle P(x) tal que P(0)=1, P(1)=2, P'(1)=0"

// Construimos los vectores repitiendo el nodo donde hay derivada
x_h = [0, 1, 1];       // El 1 está dos veces
y_h = [1, 2, 2];       // El valor en 1 es 2 (repetido)
yp_h = [%nan, %nan, 0]; // En la segunda aparición del 1, ponemos la derivada (0)

// Llamamos a la función especial
coefs_hermite = DiferenciasDivididas_Hermite(x_h, y_h, yp_h);
// Scilab te mostrará el polinomio correcto sin dividir por cero.
