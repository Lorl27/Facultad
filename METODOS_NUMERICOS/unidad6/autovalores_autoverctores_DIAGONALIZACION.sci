function check_diagonalizability(A)
    [n, m] = size(A);
    if n <> m then
        error("La matriz debe ser cuadrada");
    end

     disp("----INICIO----");
    // Cálculo de autovalores y autovectores
    [V, D] = spec(A); // V: autovectores, D: diagonal de autovalores
    lambda = diag(D); // vector de autovalores

    disp("🔹 Autovalores:");
    disp(lambda);

    disp("🔹 Autovectores:");
    for i = 1:n
        printf("v_%d =\n", i);
        disp(V(:,i));
    end
    
    disp("--------");

    // Verificamos si los autovectores son linealmente independientes
    r = rank(V);
    disp("🔹 Rango de la matriz de autovectores: ");
    disp(r);
    disp("--------");
    // Agrupamos autovalores únicos
    unique_lambda = gsort(lambda, "g", "i"); // ordenados
    unique_lambda = unique(unique_lambda);

    // Verificamos multiplicidades
    disp("🔹 Multiplicidades algebraicas y geométricas: ");
//    - Multiplicidad algebraica (MA): cuántas veces aparece el autovalor como raíz del polinomio característico.
//    - Multiplicidad geométrica (MG): dimensión del espacio nulo de A-\lambda _iI, o sea, cuántos autovectores LI hay asociados a \lambda _i.

    is_diag = %t;
    for i = 1:length(unique_lambda)
        l = unique_lambda(i);
        ma = sum(lambda == l); // multiplicidad algebraica

        // Espacio nulo de (A - l*I)
        N = null(A - l * eye(n, n));
        mg = n - rank(A - l * eye(n,n)); // dimensión del núcleo

        printf("λ = %f → MA = %d, MG = %d\n", l, ma, mg);
        disp("--------");
            
        if mg < ma then
            is_diag = %f;
        end
    end

    if r == n & is_diag then
        disp("✅ La matriz es diagonalizable.");
    else
        disp("❌ La matriz NO es diagonalizable.");
    end
    
    disp("----FIN----");
endfunction

///---
A = [2 1 0; 0 2 0; 0 0 3]; // autovalor 2 repetido
check_diagonalizability(A);
