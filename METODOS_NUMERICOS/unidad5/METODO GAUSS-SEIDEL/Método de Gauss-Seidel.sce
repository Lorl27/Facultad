// xi^{k+1} = 1/aii (bi - sum_{j=1}^{i-1} aij xj^{k+1} 
//                      - sum_{j=i+1}^{n} aij xj^{k}
//                  )

function x = gauss_seidel(A, b, x0, eps)
    n = size(A, 1);
    cont = 0;
    x = x0;
    xk = x;
    
    for i=1:n
        suma = 0; 
        for j = 1:n
            if (j ~= i)
                suma = suma + A(i,j) * x(j);
            end
        end
        x(i) = 1/A(i,i) * (b(i) - suma);
    end
    cont = cont + 1;
    
    while (norm(x - xk) > eps)
        xk = x;
        for i=1:n
            suma = 0; 
            for j = 1:n
                if (j ~= i)
                    suma = suma + A(i,j) * x(j);
                end
            end
            x(i) = 1/A(i,i) * (b(i) - suma);
        end
        cont = cont + 1;
    end
    
    x0 = x;
    disp(cont);
endfunction


//----
///----------- PARA GAUSS SEIDEL:
function [D, L] = descompDL(A)
    // Verificar si A es cuadrada
    [m, n] = size(A);
    if m <> n then
        error("❌ La matriz debe ser cuadrada para aplicar Gauss-Seidel.");
    end

    // Extraer la diagonal
    D = diag(diag(A));

    // Extraer la parte inferior estricta (debajo de la diagonal)
    L = tril(A, -1);

    // Mostrar resultados
    disp("✅ Matriz D (diagonal):");
    disp(D);
    disp("✅ Matriz L (inferior estricta):");
    disp(L);
endfunction

descompDL([0 2 4 ; 1 -1 -1 ; 1 -1 2])
