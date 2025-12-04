// ============================================================
// 🔹 ANALIZADOR DE GERSHGORIN CON GRÁFICO (TOTALMENTE COMPATIBLE)
// ============================================================

// ---------- Función: trasponer matriz ----------
function AT = matriz_traspuesta(A)
    AT = A';
endfunction


// ---------- Función: graficar círculos de Gershgorin ----------
function graficar_gershgorin(A, titulo)
    n = size(A,1);
    scf(0);      // selecciona o crea una nueva ventana gráfica
    clf();       // limpia la figura actual
    xtitle(titulo, "Re(λ)", "Im(λ)");

    // Dibujar círculos uno por uno
    for i = 1:n
        centro = A(i,i);
        radio = sum(abs(A(i,:))) - abs(A(i,i));
        theta = linspace(0, 2*%pi, 200);
        x = real(centro) + radio*cos(theta);
        y = imag(centro) + radio*sin(theta);
        plot(x, y, "b"); // círculo
        // marcar el centro
        plot(real(centro), imag(centro), "ro");
        // escribir el nombre del círculo
        xstring(real(centro) + 0.05, imag(centro), "C_"+string(i));
    end

    legends(["Círculos de Gershgorin"], [1]);
endfunction


// ---------- Función principal ----------
function analizar_gershgorin(A)
    [n, m] = size(A);
    usar = "";
    if n <> m then
        error("La matriz debe ser cuadrada.");
    end

    disp("────────────────────────────────────────────");
    disp("🔹 ANÁLISIS DE GERSHGORIN");
    disp("────────────────────────────────────────────");

    // Calcular radios por filas y columnas
    fila_suma = zeros(n,1);
    col_suma  = zeros(n,1);

    for i = 1:n
        fila_suma(i) = sum(abs(A(i,:))) - abs(A(i,i));
        col_suma(i)  = sum(abs(A(:,i))) - abs(A(i,i));
    end

    // Calcular medias y desviaciones
    mean_f = mean(fila_suma);
    mean_c = mean(col_suma);
    std_f  = stdev(fila_suma);
    std_c  = stdev(col_suma);

    printf("Promedio radios (filas)   = %.4f (desv = %.4f)\n", mean_f, std_f);
    printf("Promedio radios (columnas) = %.4f (desv = %.4f)\n", mean_c, std_c);

    // Medida de simetría
    simetria = norm(A - A', "fro") / norm(A, "fro");
    printf("Medida de simetría (||A - At||/||A||) = %.4e\n", simetria);
    disp("────────────────────────────");

    // Decidir recomendación
    if simetria < 1e-12 then
        disp("✅ La matriz es simétrica → usar A o A^T (equivalente).");
        usar = "A";
    else
        if std_f < std_c then
            disp("📘 Recomendación: usar círculos de Gershgorin por FILAS (A).");
            usar = "A";
        else
            disp("📗 Recomendación: usar círculos de Gershgorin por COLUMNAS (A^T).");
            usar = "AT";
        end
    end

    // Mostrar gráfico
    if usar == "A" then
        graficar_gershgorin(A, "Círculos de Gershgorin por FILAS (A)");
    else
        graficar_gershgorin(A', "Círculos de Gershgorin por COLUMNAS (A^T)");
    end

    disp("────────────────────────────────────────────");
endfunction


// ============================================================
// 🔸 EJEMPLOS DE USO
// ============================================================

// Ejemplo 1: matriz simétrica
A1 = [2 -1 0; -1 2 -1; 0 -1 2];
disp("Ejemplo 1 (matriz simétrica):");
analizar_gershgorin(A1);

// Ejemplo 2: matriz no simétrica
A2 = [1 10; 0.1 1];
disp("Ejemplo 2 (matriz no simétrica):");
analizar_gershgorin(A2);

// Ejemplo 3: matriz desbalanceada
A3 = [4 2 0; 0 3 100; 0 0 1];
disp("Ejemplo 3 (muy no simétrica):");
analizar_gershgorin(A3);

// --- Probar trasposición ---
disp("Traspuesta de A3:");
disp(matriz_traspuesta(A3));
