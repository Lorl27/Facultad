// ===========================================
// Función: companion_matrix
// Dado un polinomio (vector de coeficientes),
// devuelve la matriz compañera asociada.
// ===========================================

function C = companion_matrix(p)
    // p: vector fila o columna de coeficientes del polinomio
    // Ejemplo: p = [1 8 0 0 0 0 0 0 0 1] representa
    // λ^10 + 8λ^9 + 1 = 0

    // Aseguramos que p sea columna
    p = p(:);
    n = length(p) - 1;

    // Verificamos que el coeficiente líder no sea 0
    if p(1) == 0 then
        error("El coeficiente líder no puede ser cero.");
    end

    // Normalizamos para que el coeficiente líder sea 1
    p = p / p(1);

    // Construimos la matriz compañera
    // Forma estándar:
    // [0 0 ... 0 -a_n]
    // [1 0 ... 0 -a_{n-1}]
    // [0 1 ... 0 -a_{n-2}]
    // ...
    // [0 0 ... 1 -a_1]
    C = zeros(n, n);
    for i = 2:n
        C(i, i-1) = 1;
    end
    C(:, n) = -p(2:$);

endfunction


///---
// Polinomio: λ^10 + 8λ^9 + 1 = 0
p = [1 8 0 0 0 0 0 0 0 0 1];
C = companion_matrix(p);
disp(C);

// Ahora podés aplicar tu función de Gershgorin
//[centros, radios, rho_cota, solapados] = gershgorin_analysis_plot(C, %t);
