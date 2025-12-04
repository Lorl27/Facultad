function analizar_matriz(A)
    [n, m] = size(A);
    if n <> m then
        error("❌ La matriz debe ser cuadrada");
    end

    disp("══════════════════════════════════════════════");
    disp("🔎 ANÁLISIS DE LA MATRIZ A");
    disp("══════════════════════════════════════════════");
    disp(A);
    disp("────────────");

    // Polinomio característico
    x = poly(0, "x");
    p_A = det(eye(n, n)*x - A);
    disp("📘 Polinomio característico p(x) = det(xI - A):");
    disp(p_A);
    disp("────────────");

    // Autovalores y autovectores
    [V, D] = spec(A); // D: diagonal con autovalores, V: autovectores columna
    lambda = diag(D);

    disp("📗 Autovalores:");
    disp(lambda);
    disp("────────────");

    disp("📙 Autovectores asociados (columnas de V):");
    for i = 1:n
        printf("v_%d =\n", i);
        disp(V(:,i));
    end
    disp("────────────");

    // Rango
    r = rank(A);
    disp("📏 Rango de A: %d\n");
        disp(r);
        //si r = n entonces li y forman base.
    disp("────────────");

    // Verificación de ortogonalidad entre autovectores
    disp("📐 Producto interno entre autovectores (VᵀV):");
    disp((V'*V)); // redondeado para legibilidad
    if norm(V'*V - eye(n,n)) < 1e-6 then
        disp("✅ Los autovectores son ortogonales (matriz P ortogonal).");
    else
        disp("⚠️ Los autovectores NO son ortogonales.");
    end
    disp("────────────");

    // Multiplicidades algebraicas y geométricas
    disp("📊 Multiplicidades de cada autovalor:");
    unique_lambda = unique(lambda);
    is_diag = %t;
    for i = 1:length(unique_lambda)
        l = unique_lambda(i);
        ma = sum(lambda == l);
        mg = n - rank(A - l*eye(n, n));
        printf("λ = %.6f → MA = %d, MG = %d\n", l, ma, mg);
        if mg < ma then
            is_diag = %f;
        end
    end
    disp("────────────");

    // Diagonalización
    if is_diag then
        disp("✅ La matriz es diagonalizable.");
        disp("   Se cumple MG = MA para todos los autovalores.");
        disp("   A = P D P⁻¹, con P formada por los autovectores.");
    else
        disp("❌ La matriz NO es diagonalizable (algún MG < MA).");
    end

    disp("══════════════════════════════════════════════");
endfunction

//--------
A = [2 1 0; 1 2 1; 0 1 2];
analizar_matriz(A);

B = [2 1 0; 0 2 0; 0 0 3];
analizar_matriz(B);
