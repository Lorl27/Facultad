function [L, U] = fact_crout(A)
    [nA,mA] = size(A)
    if nA<>mA then
        error('gausselim - La matriz A debe ser cuadrada');
        abort;
    end
    
    L = zeros(nA, nA);
    U = eye(nA, nA);
    L(:, 1) = A(:, 1);
    U(1,:) = A(1,:)/L(1,1);
    for j =2:nA
        L(j:nA, j) = A(j:nA, j) - L(j:nA, 1:j-1)*U(1:j-1, j);
        U(j,j+1:nA) = (A(j,j+1:nA) - L(j, 1:j-1)*U(1:j-1, j+1:nA)) / L(j,j);
    end
    
endfunction
