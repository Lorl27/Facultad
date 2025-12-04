// =====================================================
// FACTORIZACIÓN DE CHOLESKY (triangular inferior)
// =====================================================
function [L, ind] = cholesky_L(A)
    eps = 1.0e-8;
    n = size(A, 1);
    L = zeros(n, n);
    
    for k = 1:n
       // Calcular el elemento diagonal
        if k == 1 then
            t = A(k, k);
        else
            t = A(k, k) - L(k, 1:k-1) * L(k, 1:k-1)';
        end
        
        if t <= eps then
            printf("Matriz no definida positiva.\n");
            ind = 0;
            return;
        end
        L(k, k) = sqrt(t);
        
        //calcular elementos bajo la diagonal:
        for i = k+1:n
           if k == 1 then
                L(i, k) = A(i, k) / L(k, k);
            else
                L(i, k) = (A(i, k) - L(i, 1:k-1) * L(k, 1:k-1)') / L(k, k);
            end
        end
    end
    
    ind = 1;
endfunction


// =====================================================
// SUSTITUCIÓN HACIA ADELANTE: L*y = b
// =====================================================
function y = sust_inf(L, b)
    n = length(b);
    y = zeros(n, 1);
    for i = 1:n
        y(i) = (b(i) - L(i, 1:i-1) * y(1:i-1)) / L(i, i);
    end
endfunction


// =====================================================
// SUSTITUCIÓN HACIA ATRÁS: Lᵗ*x = y
// =====================================================
function x = sust_sup_trans(L, y)
    n = length(y);
    x = zeros(n, 1);
    for i = n:-1:1
       if i == n then
            x(i) = y(i) / L(i, i);
        else
            x(i) = (y(i) - L(i+1:n, i)' * x(i+1:n)) / L(i, i);
        end
    end
endfunction


// =====================================================
// RESOLVER SISTEMA POR CHOLESKY
// =====================================================
function x = resolver_cholesky(A, b)
    [L, ind] = cholesky_L(A);
    if ind == 0 then
        error("No se puede usar Cholesky: la matriz no es definida positiva.");
    end
    
    disp("Matriz L (triangular inferior):");
    disp(L);
    
    // Resolver L*y = b
    y = sust_inf(L, b);
    
    // Resolver Lᵗ*x = y
    x = sust_sup_trans(L, y);
    
    disp("Vector solución x:");
    disp(x);
endfunction


// =====================================================
// EJERCICIO 12 ( PARTE A)
// =====================================================

//12. (a) Escribir en Scilab una funci´on que resuelva el sistema Ax = b por el m´etodo de
//Cholesky, para el caso de una matriz A definida positiva. Utilizar la funci´on para
//resolver el sistema:
//{
//16 −12 8
//−12 18 −6
//8 −6 8}
//{
//x1
//x2
//x3
//} = {
//76
//−66
//46
//}

A = [16 -12 8;
    -12 18 -6;
      8  -6  8];
b = [76; -66; 46];

x = resolver_cholesky(A, b);


//============================= EJERICICO DE UN PARCIAL.
// =====================================================
// CALCULAR INVERSA USANDO CHOLESKY
// =====================================================
function X = inversa_cholesky(A)
    [L, ind] = cholesky_L(A);
    if ind == 0 then
        error("No se puede calcular la inversa: la matriz no es definida positiva.");
    end

    n = size(A, 1);
    I = eye(n, n);
    X = zeros(n, n);

    // Resolver para cada columna de I
    for k = 1:n
        e = I(:, k);
        y = sust_inf(L, e);
        x = sust_sup_trans(L, y);
        X(:, k) = x;
    end
endfunction

// ========== EJEMPLO DE USO ==========
A = [16 -12 8; -12 18 -6; 8 -6 8];
X = inversa_cholesky(A);

disp("Inversa de A calculada con Cholesky:");
disp(X);

disp("Verificación A * A⁻¹ ≈ I:");
disp(A * X);
