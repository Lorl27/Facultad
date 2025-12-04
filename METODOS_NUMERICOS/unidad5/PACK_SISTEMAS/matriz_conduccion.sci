// =======================================================
// Función que genera la matriz tridiagonal A para un c dado
// =======================================================
function A = matriz_conduccion(c)
    n = 5; // número de puntos interiores de la barra
    A = (1 + 2*c) * eye(n, n) - c * diag(ones(n-1,1), 1) - c * diag(ones(n-1,1), -1);
endfunction

// === Ejemplo de uso ===
c = 1;
A = matriz_conduccion(c);

disp("Matriz A para c =",c);
disp(A);
