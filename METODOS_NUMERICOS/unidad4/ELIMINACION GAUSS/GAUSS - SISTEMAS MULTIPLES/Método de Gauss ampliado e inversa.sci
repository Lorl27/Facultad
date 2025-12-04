function [X, A_aum] = gauss_amp(A, B)
    [nA, mA] = size(A);
    [nB, mB] = size(B);
    
    if nA <> mA then
        error("La matriz A debe ser cuadrada");
        abort;
    elseif nB <> mB then
        error("La matriz B debe ser cuadrada");
        abort;
    end
    
    A_aum = [A,B];
    
    for i = 1:(nA-1) do
        for j = (i + 1):nA do
            mji = A_aum(j, i) / A_aum(i, i);
            A_aum(j, i) = 0;
            A_aum(j, (i+1):(mA+mB)) = A_aum(j,(i+1):(mA+mB))-mji*A_aum(i,(i+1):(mA+mB));
        end
    end
    X(nA,1:mB) = A_aum(nA, (nA+1):(nA+mB))./A_aum(nA,nA);
    for i = (nA-1):-1:1 do
        X(i, 1:mB) = (A_aum(i, (mA+1):(mA+mB))-A_aum(i,(i+1):mA)*X((i+1):mA,1:mB))./A_aum(i,i);
    end
endfunction

function salida = inversa(A)
    n = size(A, 1);
    [X, A_aum] = Gauss_amp(A, eye(n(1),n(1)));
    salida = X;
endfunction
