function invA = inversa_matriz(A)
    // Verificar si A es cuadrada
    [n, m] = size(A);
    if n <> m then
        error("❌ Error: la matriz no es cuadrada, no se puede calcular la inversa.");
        return
    end

    // Verificar si el determinante es distinto de cero
    detA = det(A);
    if detA == 0 then
        error("❌ Error: la matriz es singular (determinante = 0), no tiene inversa.");
        return
    end

    // Si pasa las comprobaciones, calcular la inversa
    invA = inv(A);
    disp("✅ La matriz es invertible. Su inversa es:");
    disp(invA);
endfunction

//-------------

A=[1 -1 0 ; -1 2 -1 ; 0 -1 1.1];

D=[1 0 0; -1 2 0 ; 0 -1 1.1]

invA=inversa_matriz(D)

n=invA*A

disp("A:",A,"N",D,"invesa DE N:",invA,"INV N * A",n)

//----------------------
function norma_inf = normaInfinito(A)
    // Obtener dimensiones de A
    [m, n] = size(A)
    
    // Calcular la suma de los valores absolutos por fila
    suma_filas = zeros(m, 1)
    for i = 1:m
        suma_filas(i) = sum(abs(A(i, :)))
    end
    
    // La norma infinito es el máximo de esas sumas
    norma_inf = max(suma_filas)
    
    // Mostrar el resultado
    disp("✅ La norma infinito de la matriz es: " + string(norma_inf))
endfunction

//------------
///disp(normaInfinito(I-n))

invA=inversa_matriz([1 0 0 ; 0 1 0; 0 0 1])
