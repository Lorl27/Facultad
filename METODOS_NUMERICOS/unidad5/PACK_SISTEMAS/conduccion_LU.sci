// =======================================================
// Simulación de conducción de calor con factorización LU
// =======================================================
function [A, L, U, X_hist] = conduccion_LU(c, x0, pasos)
    // c: constante física
    // x0: vector columna inicial de temperaturas (R^5)
    // pasos: cantidad de pasos (por ejemplo 4)

    n = 5;
    // Construcción de la matriz A tridiagonal
    A = (1 + 2*c)*eye(n, n) - c*diag(ones(n-1,1), 1) - c*diag(ones(n-1,1), -1);

    // Factorización LU (sin pivoteo)
    [L, U] = lu(A);

    // Inicialización del historial de temperaturas
    X_hist = zeros(n, pasos+1);
    X_hist(:,1) = x0; // x^(0)

    // Iteración para obtener x^(1), x^(2), ...
    for k = 1:pasos
        // Resolver A*x_{k+1} = x_k usando la factorización LU
        y = L \ X_hist(:,k);     // L*y = x_k
        X_hist(:,k+1) = U \ y;   // U*x_{k+1} = y
    end

    // Mostrar resultados
    disp("Matriz L:");
    disp(L);
    disp("Matriz U:");
    disp(U);

    disp("Distribuciones de temperatura (por columnas):");
    for k = 1:pasos
        mprintf("x^(%d):\n", k);
        disp(X_hist(:,k+1));
    end
endfunction

// =======================================================
// Ejemplo de uso
// =======================================================
c = 1;
x0 = [10; 12; 12; 12; 10];
pasos = 4;

[A, L, U, X_hist] = conduccion_LU(c, x0, pasos);

// Mostrar matriz A y determinante
disp("Matriz A:");
disp(A);
mprintf("Determinante de A: %.6f\n", det(A));
