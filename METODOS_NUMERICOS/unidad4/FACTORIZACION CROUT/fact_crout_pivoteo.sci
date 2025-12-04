// ======================================================
// FACTORIZACIÓN DE CROUT CON PIVOTEO PARCIAL
// ======================================================
function [L, U, P] = fact_crout_pivoteo(A)
    [n, m] = size(A);
    if n <> m then
        error("La matriz A debe ser cuadrada.");
    end

    P = eye(n, n);   // matriz de permutación
    L = zeros(n, n);
    U = eye(n, n);   // Crout define 1s en la diagonal de U

    for j = 1:n
        // --- PIVOTEO ---
        // buscamos el mayor valor absoluto en la columna j (desde la fila j)
        [pivot, fila_max] = max(abs(A(j:n, j)));
        fila_max = fila_max + j - 1;

        if fila_max <> j then
            // intercambiar filas en A y en P
            A([j, fila_max], :) = A([fila_max, j], :);
            P([j, fila_max], :) = P([fila_max, j], :);
            // también intercambiar en L las filas anteriores
            if j > 1 then
                L([j, fila_max], 1:j-1) = L([fila_max, j], 1:j-1);
            end
        end

        // --- Cálculo de la columna j de L ---
        L(j:n, j) = A(j:n, j);
        if j > 1 then
            L(j:n, j) = L(j:n, j) - L(j:n, 1:j-1) * U(1:j-1, j);
        end

        // --- Verificación de pivote ---
        if abs(L(j, j)) < %eps then
            error("Pivote nulo o muy pequeño, matriz singular o mal condicionada.");
        end

        // --- Cálculo de la fila j de U ---
        if j < n then
           if j > 1 then
                U(j, j+1:n) = (A(j, j+1:n) - L(j, 1:j-1) * U(1:j-1, j+1:n)) / L(j, j);
            else
                U(j, j+1:n) = A(j, j+1:n) / L(j, j);
    end


        end
    end
endfunction


//--
// Ejemplo
A = [1 2 -3 4; 4 8 12 -9; 2 3 2 1; -3 -1 1 -4];
b = [3; 60; 1; 5];

[L, U, P] = fact_crout_pivoteo(A);

disp("L ="); disp(L);
disp("U ="); disp(U);
disp("P ="); disp(P);

// Resolver el sistema A·x = b
y = L \ (P * b);  // L*y = P*b
x = U \ y;        // U*x = y
disp("x ="); disp(x);
