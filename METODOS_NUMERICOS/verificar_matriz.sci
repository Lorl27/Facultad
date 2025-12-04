// ============================================================
// 🔹 Verificar si una matriz es simétrica y definida positiva
// ============================================================
// Entrada:
//   A → matriz cuadrada real
// Salida:
//   Muestra en pantalla si la matriz es:
//   - No cuadrada
//   - No simétrica
//   - Simétrica pero no definida positiva
//   - Simétrica y definida positiva
// ============================================================

function verificar_matriz(A)
    [n, m] = size(A);

    if n <> m then
        disp("❌ La matriz NO es cuadrada.");
        return
    end

    // 1️⃣ Verificar simetría
    if norm(A - A', 'inf') < 1e-10 then
        disp("✅ La matriz es simétrica.");
        simetrica = %t;
    else
        disp("❌ La matriz NO es simétrica.");
        simetrica = %f;
    end

    // 2️⃣ Verificar definida positiva (solo si es simétrica)
    if simetrica then
        // Todos los autovalores deben ser positivos
        autovalores = spec(A);

        if min(autovalores) > 0 then
            disp("✅ La matriz es definida positiva.");
        else
            disp("⚠️ La matriz NO es definida positiva.");
            disp("   Autovalores encontrados:");
            disp(autovalores);
        end
    end
endfunction

// ============================================================
// 🔹 Ejemplo de uso
// ============================================================

// Ejemplo 1: Matriz simétrica y definida positiva
A1 = [2 -1 0; -1 2 -1; 0 -1 2];

// Ejemplo 2: Matriz no simétrica
A2 = [1 2 3; 2 1 0; 3 4 1];

// Ejemplo 3: Simétrica pero no definida positiva
A3 = [0 1; 1 0];

// Pruebas
disp("────────── Ejemplo 1 ──────────");
verificar_matriz(A1);

disp("────────── Ejemplo 2 ──────────");
verificar_matriz(A2);

disp("────────── Ejemplo 3 ──────────");
verificar_matriz(A3);
