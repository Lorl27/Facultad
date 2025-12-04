function [L, U, P] = fact_LU(A)
    [m, n] = size(A);
    if m <> n then
        error("La matriz A debe ser cuadrada.");
        abort;
    end
    
    U = A;
    L = eye(n, n);
    P = eye(n, n);
    
    for k = 1:m-1
        // Selección del pivote y permutación de filas
        [Amax, i] = max(abs(U(k:m, k)));
        i = i + k - 1;
        
        if i <> k then
            U([k, i], k:m) = U([i, k], k:m);  // Intercambio en U
            P([k, i], :) = P([i, k], :);      // Intercambio en P
            L([k, i], 1:k-1) = L([i, k], 1:k-1);  // Intercambio en L, solo en columnas previas
        end
        
        // Actualización de L y U usando submatrices
        L(k+1:m, k) = U(k+1:m, k) / U(k, k);
        U(k+1:m, k+1:m) = U(k+1:m, k+1:m) - L(k+1:m, k) * U(k, k+1:m);
        U(k+1:m, k) = 0;  // Asegura que el valor debajo del pivote en U sea cero
    end
endfunction


// EJERICICIO 7
//Programar en Scilab el siguiente algoritmo para obtener la factorizaci´on PA = LU a partir
//de la eliminaci´on de Gauss con pivoteo parcial:
//Algoritmo: Eliminaci´on de Gauss con Pivoteo Parcial
//U = A, L = I, P = I
//for k = 1 to m − 1
    //Seleccionar i ≥ k que maximiza |uik|
    //uk,k:m ↔ ui,k:m (intercambio de filas)
    //lk,1:k−1 ↔ li,1:k−1
    //pk,: ↔ pi,:
        //for j = k + 1 to m
        //ljk = ujk/ukk
        //uj,k:m = uj,k:m − ljkuk,k:m
