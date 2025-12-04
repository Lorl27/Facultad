// ============================================================
// 🔹 Comparar precisión entre soluciones obtenidas con
//    Cholesky y QR
// ============================================================
// Entrada:
//   A  → matriz del sistema
//   b  → vector del término independiente
//   x1 → solución obtenida por Cholesky
//   x2 → solución obtenida por QR
// ============================================================
// Salida:
//   Muestra los valores de ||A*x1 - b||₂ y ||A*x2 - b||₂
//   e indica cuál tiene el error más pequeño.
// ============================================================

function comparar_errores(A, b, x1, x2)
    // Verificar dimensiones básicas
    [nA, mA] = size(A);
    [nb, mb] = size(b);
    if nA <> nb then
        error("❌ Las dimensiones de A y b no son compatibles.");
    end

    // Calcular residuos
    r1 = A*x1 - b;
    r2 = A*x2 - b;

    // Calcular normas 2
    error1 = norm(r1, 2);
    error2 = norm(r2, 2);

    // Mostrar resultados
    disp("──────────────────────────────");
    disp("🔹 Comparación de errores:");
    printf("‖A*x₁ - b‖₂ (Cholesky) = %.6e\n", error1);
    printf("‖A*x₂ - b‖₂ (QR)       = %.6e\n", error2);
    disp("──────────────────────────────");

    // Determinar cuál es mejor
    if error1 < error2 then
        disp("✅ La solución por **Cholesky** tiene menor error.");
    elseif error2 < error1 then
        disp("✅ La solución por **QR** tiene menor error.");
    else
        disp("⚖️ Ambas soluciones tienen el mismo error (dentro de la tolerancia numérica).");
    end
endfunction

//--
// Datos de ejemplo
A = [4 1; 1 3];
b = [1; 2];

// Supongamos que ya resolviste:
x1 = [0.0909; 0.6364]; // Solución por Cholesky
x2 = [0.0910; 0.6360]; // Solución por QR

// Comparar los errores
comparar_errores(A, b, x1, x2);
