// ===========================================================
// Simulación de conducción de calor 1D (barra de n nodos)
// con factorización LU, tridiagonal o tridiagonal cíclica.
//
// Parámetros:
//   n        → cantidad de puntos de la barra
//   c        → constante física (relacionada con Δt y Δx)
//   x0       → vector inicial de temperaturas (R^n)
//   pasos    → cantidad de pasos de tiempo a simular
//   ciclica  → %t si los extremos están conectados (barra cerrada)
//               %f si los extremos están fijos a 0 °C
//
// Devuelve:
//   A        → matriz del sistema
//   L, U     → factores de LU
//   X_hist   → matriz que guarda x^(k) en cada paso
// ===========================================================
function [A, L, U, X_hist] = conduccion_LU_general(n, c, x0, pasos, ciclica)
    // Validación
    if size(x0,1) <> n then
        error("x0 debe tener longitud n");
    end

    // --- Construcción de la matriz A ---
    A = (1 + 2*c)*eye(n, n) - c*diag(ones(n-1,1), 1) - c*diag(ones(n-1,1), -1);

    // Si la barra es cíclica, conectar los extremos
    if ciclica then
        A(1,n) = -c;
        A(n,1) = -c;
    end

    // --- Factorización LU ---
    [L, U] = lu(A);

    // --- Evolución temporal: Ax(k+1) = x(k) ---
    X_hist = zeros(n, pasos+1);
    X_hist(:,1) = x0;

    for k = 1:pasos
        y = L \ X_hist(:,k);
        X_hist(:,k+1) = U \ y;
    end

    // --- Mostrar resultados ---
    disp("==============================================");
    if ciclica then
        disp("🔄 MATRIZ CÍCLICA (extremos conectados)");
    else
        disp("⛔ MATRIZ TRIDIAGONAL (bordes fijos)");
    end
    disp("==============================================");
    disp("Matriz A:");
    disp(A);
    disp("Matriz L:");
    disp(L);
    disp("Matriz U:");
    disp(U);

    for k = 1:pasos
        mprintf("\nTemperaturas x^(%d):\n", k);
        disp(X_hist(:,k+1));
    end
endfunction

//-----------  caso 1 - bordes fijos (tridiagonal normal)
n = 5;
c = 1;
x0 = [10; 12; 12; 12; 10];
pasos = 4;
ciclica = %f;

[A, L, U, X_hist] = conduccion_LU_general(n, c, x0, pasos, ciclica);

//------------ caso 2 - bordes conectados (tridiagonal criclica)
n = 6;
c = 1;
x0 = [1; 2; 3; 4; 5; 6];
pasos = 3;
ciclica = %t;

[A, L, U, X_hist] = conduccion_LU_general(n, c, x0, pasos, ciclica);

