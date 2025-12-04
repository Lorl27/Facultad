function[x,a] = gauss_tri_piv(A,b)
    [nA,mA] = size(A)
    [nb,mb] = size(b)
    if nA<>mA then error('La matriz A debe ser cuadrada');
        abort;
    elseif mA<>nb then error('Dimensiones incompatibles entre A y b');
        abort;
    end
    a = [A b];
    n = nA;
    contador = 0;
    
    for k=1:n-1 do
        kpivot = k;
        amax = abs(a(k,k));
        if abs(a(k+1,k)) > amax then 
            temp = a(k+1,:);
            a(k+1,:) = a(k,:);
            a(k,:) = temp;
        end
        for j=k+1:n+1 do
            a(k+1,j) = a(k+1,j)-a(k,j)*a(k+1,k)/a(k,k);
            contador = contador+3;
        end
    end

    x(n) = a(n,n+1)/a(n,n);
    x(n-1) = (a(n-1,n+1)-a(n-1,n)*x(n))/a(n-1,n-1);
    contador = contador+4;
    for i=n-2:-1:1 do
        x(i) = (a(i,n+1)-a(i,i+1)*x(i+1)-a(i,i+2)*x(i+2))/a(i,i);
        contador = contador+5;
    end
    disp(contador);
endfunction
