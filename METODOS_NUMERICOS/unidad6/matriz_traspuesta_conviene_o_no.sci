// ============================================================
//  Analizador de Gershgorin: ¿usar A o A^T?
// ============================================================

// --- Función para trasponer una matriz ---
function AT = matriz_traspuesta(A)
    AT = A'; // traspuesta en Scilab
endfunction


// --- Función principal ---
function analizar_gershgorin(A)
    [n, m] = size(A);
    if n <> m then
        error("La matriz debe ser cuadrada.");
    end

    disp("────────────────────────────────────────────");
    disp("🔹 ANÁLISIS DE GERSHGORIN");
    disp("────────────────────────────────────────────");

    // Calcular la "desproporción" entre filas y columnas
    fila_suma = zeros(n,1);
    col_suma  = zeros(n,1);

    for i = 1:n
        fila_suma(i) = sum(abs(A(i,:))) - abs(A(i,i)); // radios por filas
        col_suma(i)  = sum(abs(A(:,i))) - abs(A(i,i)); // radios por columnas
    end

    // Medir la media y la desviación
    mean_f = mean(fila_suma);
    mean_c = mean(col_suma);
    std_f  = stdev(fila_suma);
    std_c  = stdev(col_suma);

    // Mostrar los datos
    printf("Promedio de radios por filas   = %.4f (desv = %.4f)\n", mean_f, std_f);
    printf("Promedio de radios por columnas = %.4f (desv = %.4f)\n", mean_c, std_c);
    disp("────────────────────────────");

    // Evaluar si la matriz es aproximadamente simétrica
    simetria = norm(A - A', "fro") / norm(A, "fro");
    printf("Medida de simetría (||A - At||/||A||) = %.4e\n", simetria);

    // --- Decisión ---
    if simetria < 1e-12 then
        disp("✅ La matriz es simétrica → usar A (da lo mismo A^T).");
    else
        if std_f < std_c then
            disp("📘 Recomendación: usar los círculos de Gershgorin por FILAS (A).");
        else
            disp("📗 Recomendación: usar los círculos de Gershgorin por COLUMNAS (A^T).");
        end
    end

    disp("────────────────────────────────────────────");
endfunction


// ============================================================
// 🔸 EJEMPLOS DE USO
// ============================================================

// Ejemplo 1: simétrica
A1 = [2 -1 0; -1 2 -1; 0 -1 2];
disp("Ejemplo 1 (matriz simétrica):");
analizar_gershgorin(A1);

// Ejemplo 2: no simétrica
A2 = [1 10; 0.1 1];
disp("Ejemplo 2 (matriz no simétrica):");
analizar_gershgorin(A2);

// Ejemplo 3: muy asimétrica
A3 = [4 2 0; 0 3 100; 0 0 1];
disp("Ejemplo 3 (matriz no simétrica y desbalanceada):");
analizar_gershgorin(A3);

// --- Probar la función de traspuesta ---
disp("Traspuesta de A3:");
disp(matriz_traspuesta(A3));


disp("======================")
AN=[3 0  -1 ; 1 -2 -2 ; -1 -1 8]
analizar_gershgorin(AN);
