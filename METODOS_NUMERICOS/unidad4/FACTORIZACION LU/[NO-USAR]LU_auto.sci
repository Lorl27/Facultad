// =====================================================
// Factorización LU automática con detección de pivote nulo
// Si se detecta pivote pequeño -> usa pivoteo parcial
// =====================================================

function [L, U, P, pivoteo_usado,intercambios] = LU_auto(A)
    [n, m] = size(A);
    if n <> m then
        error('La matriz A debe ser cuadrada');
        abort;
    end

    U = A;
    L = eye(n, n);
    P = eye(n, n);
    pivoteo_usado = 0;
    intercambios = 0;
    tol = 1e-12;

    for k = 1:n-1
        // Detección automática de pivote pequeño o nulo
////        mprintf("DEBUG: U(%d,%d) = %e\n", k, k, U(k,k));
        if abs(U(k, k)) <= tol then
            [maxval, ind] = max(abs(U(k:n, k)));
            ind = ind + k - 1;
            if maxval == 0 then
                error('LU_auto: matriz singular (columna nula)');
            end
            // Intercambio de filas
            U([k ind], :) = U([ind k], :);
            P([k ind], :) = P([ind k], :);
            L([k ind], 1:k-1) = L([ind k], 1:k-1);
            pivoteo_usado = 1;
            intercambios = intercambios + 1;
        end

        // Eliminación
        for i = k+1:n
            L(i, k) = U(i, k) / U(k, k);
            U(i, :) = U(i, :) - L(i, k) * U(k, :);
        end
    end
    
////    if pivoteo_usado then
////    disp("DEBUG: pivoteo_usado = 1 dentro de LU_auto");
////    end
endfunction


// =====================================================
// Sustitución hacia adelante (L*y = b)
// =====================================================
function y = sust_inf(L, b)
    n = length(b);
    y = zeros(n, 1);
    for i = 1:n
        y(i) = (b(i) - L(i, 1:i-1) * y(1:i-1)) / L(i, i);
    end
endfunction


// =====================================================
// Sustitución hacia atrás (U*x = y)
// =====================================================
function x = sust_sup(U, y)
    n = length(y);
    x = zeros(n, 1);
    for i = n:-1:1
        if i == n then
            x(i) = y(i) / U(i, i);
        else
            if i+1 <= n then
                x(i) = (y(i) - U(i, i+1:n) * x(i+1:n)) / U(i, i);
            else
                x(i) = y(i) / U(i, i);
            end
        end
    end
endfunction


// =====================================================
// Función principal: resuelve A*x = b automáticamente
// =====================================================
function x = resolver_LU_auto(A, b)
    [L, U, P, pivoteo_usado,intercambios] = LU_auto(A);

////    disp("DEBUG: pivoteo_usado recibido = " + string(pivoteo_usado));
    
    if pivoteo_usado then
        disp("Se detectó pivote pequeño: se aplicó pivoteo parcial (PA = LU).");
        c = P * b;
    else
        disp("Pivotes válidos: se usó factorización LU sin pivoteo.");
        c = b;
    end
    
////    disp(pivoteo_usado);

    y = sust_inf(L, c);
    x = sust_sup(U, y);
    
// Determinante
    detA = prod(diag(U));
    if pivoteo_usado then
        detA = detA * (-1)^intercambios;
    end


    // Mostrar resultados
    mprintf("\n--- RESULTADOS ---\n");
    disp("Matriz L:");
    disp(L);
    disp("Matriz U:");
    disp(U);
    if pivoteo_usado then
        disp("Matriz P (permutación):");
        disp(P);
    end
    disp("Solución del sistema:");
    disp(x);
    mprintf("Determinante de A: %f\n", detA);

endfunction


// =====================================================
// PRUEBAS
// =====================================================

// Caso 1: pivote inicial nulo → requiere pivoteo
A = [0 2 3; 2 0 3; 8 16 -1];
b = [7; 13; -3];
x = resolver_LU_auto(A, b);

// Separador visual
mprintf("\n============================\n");
// Separador visual
mprintf("\n============================\n");


// Caso 2: pivotes válidos → sin pivoteo
A = [2 1 1 0;
     4 3 3 1;
     8 7 9 5;
     6 7 9 8];
b = [4; 7; 11; 9];
x = resolver_LU_auto(A, b);


//NO USAR ESTE!!! USAR LU_AUTOMATICO_PIVOTEO... ETC.
