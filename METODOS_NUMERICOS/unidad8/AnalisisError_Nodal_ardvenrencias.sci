// =========================================================================
//        LIBRERÍA "BLINDADA" DE MÉTODOS NUMÉRICOS (FINAL)
// =========================================================================

// -------------------------------------------------------------------------
// 1. HERRAMIENTA DE ERROR (CRÍTICA PARA TEORÍA)
// -------------------------------------------------------------------------
function [max_val, x_peor]=AnalisisError_Nodal(x_nodos, a, b)
    t = linspace(a, b, 2000); 
    prod_vals = ones(t);
    n = length(x_nodos);
    
    // Producto acumulado (x-x0)...(x-xn)
    for i = 1:n
        prod_vals = prod_vals .* (t - x_nodos(i));
    end
    
    prod_vals = abs(prod_vals); 
    [max_val, indice] = max(prod_vals);
    x_peor = t(indice);
    
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
function [coefs, R2]=MinimosCuadrados_Generico(x, y, bases_texto)
    // x, y: vectores datos
    // bases_texto: lista de strings. Ej: ["ones(x)", "x", "exp(x)"]
    
    n = size(x, '*'); // Cuenta elementos totales (fix aplicado)
    m = size(bases_texto, '*'); // Cuenta funciones base (fix aplicado)
    
    // Asegurar columnas
    x = x(:); y = y(:); 
    A = zeros(n, m);
    
    printf("\n--- Mínimos Cuadrados Generalizado ---\n");
    
    // Construcción automática de la Matriz A
    for j = 1:m
        try
            A(:, j) = evstr(bases_texto(j));
        catch
            printf("\nERROR: La función base ''%s'' falló. Revisa sintaxis.\n", bases_texto(j));
            return;
        end
    end
    
    // Ecuaciones Normales
    Matriz_Normal = A' * A;
    Vector_Indep = A' * y;
    
    // Check de singularidad
    if rank(Matriz_Normal) < m then
        printf("\nADVERTENCIA CRÍTICA: La matriz normal es singular o mal condicionada.\n");
        printf("Tus funciones base podrían ser linealmente dependientes.\n");
        coefs = pinv(Matriz_Normal) * Vector_Indep; // Intento de rescate con pseudoinversa
    else
        coefs = Matriz_Normal \ Vector_Indep;
    end
    
    // R2 y Gráfica
    y_pred = A * coefs;
    St = sum((y - mean(y)).^2);
    Sr = sum((y - y_pred).^2);
    R2 = (St - Sr) / St;
    
    printf("\nResultados:\n");
    for j = 1:m
        printf("  C%d * (%s) -> Coef: %f\n", j, bases_texto(j), coefs(j));
    end
    printf("  R2: %f\n", R2);
    
    // Graficar
    xx = linspace(min(x), max(x), 200)';
    A_plot = zeros(200, m);
    x_bkp = x; x = xx; 
    for j=1:m, A_plot(:,j) = evstr(bases_texto(j)); end
    x = x_bkp; 
    yy_plot = A_plot * coefs;
    
    scf(11); clf();
    plot(x_bkp, y, "ro");
    plot(xx, yy_plot, "b-");
    xtitle("Ajuste Generalizado", "x", "y");
    legend(["Datos", "Modelo"]);
endfunction

// -------------------------------------------------------------------------
// 3. INTERPOLACIÓN DE HERMITE (CON DERIVADAS)
// -------------------------------------------------------------------------
function coefs=DiferenciasDivididas_Hermite(x_nodos, y_nodos, y_primas)
    // REGLA DE ORO: x_nodos debe estar ordenado para que los repetidos estén juntos.
    
    n = length(x_nodos);
    D = zeros(n, n);
    D(:,1) = y_nodos(:); 
    
    for j = 2:n 
        for i = 1:n-j+1 
            numerador = D(i+1, j-1) - D(i, j-1);
            denominador = x_nodos(i+j-1) - x_nodos(i);
            
            if abs(denominador) < 1e-10 then
                // Detecta 0/0 -> Aplica derivada
                if j == 2 then 
                    if ~isnan(y_primas(i)) then
                        D(i,j) = y_primas(i);
                    else
                        error("Error: Nodo repetido sin dato de derivada.");
                    end
                else
                    // Derivadas superiores (orden > 1) no soportadas en este script simple
                    D(i,j) = 0; 
                end
            else
                D(i,j) = numerador / denominador;
            end
        end
    end
    coefs = D(1,:); 
    
    s = poly(0, "x");
    P = 0; term = 1;
    for k=1:n
        P = P + coefs(k) * term;
        term = term * (s - x_nodos(k));
    end
    printf("\nPolinomio Resultante:\n"); disp(P);
endfunction
