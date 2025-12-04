function [x, a, iter] = gausselimPP(A, b)
    [nA, mA] = size(A);
    [nb,  mb] = size(b);

    if nA <> mA then
        error("gausselimPP - La matriz A debe ser cuadrada");
    elseif mA <> nb | mb <> 1 then
        error("gausselimPP - b debe ser un vector columna compatible con A");
    end

    a = [A, b];
    n = nA;
    iter = 0;
    
    for k = 1 : n-1
        [amax, krel] = max(abs(a(k:n, k)));
        kpivot = krel + k - 1;

        if amax == 0 then
            error("gausselimPP - A es singular (pivote nulo)");
        end

        if kpivot <> k then
            temp        = a(k, :);
            a(k, :)     = a(kpivot, :);
            a(kpivot, :)= temp;
        end

        for i = k+1 : n
            m = a(i, k) / a(k, k);
            iter = iter + 1;
            a(i, k) = 0;
            a(i, k+1 : n+1) = a(i, k+1 : n+1) - m * a(k, k+1 : n+1);
        end
    end
    
    x = zeros(n, 1);
    x(n) = a(n, n+1) / a(n, n);
    for i = n-1 : -1 : 1
        suma = a(i, i+1 : n) * x(i+1 : n);
        x(i) = (a(i, n+1) - suma) / a(i, i);
    end
endfunction

