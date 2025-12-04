function [P,L,U] = egpp(A)
    U = A;
    m = size(A, 1);
    L = eye(m,m);
    P = eye(m,m);
    //A(:,[1 3]) = A(:,[3 1]) <- permutar
    for k = 1:m-1
     [ma,ind] = max(abs(U(k:m,k))) //ind = find(abs(U(k:m,k)) == max(abs(U(k:m,k))),1) //Inicio pivoteo parcial
     ind = ind + (k-1)
     U([k ind],k:m) = U([ind k],k:m)
     L([k ind],1:k-1) = L([ind k],1:k-1)
     P([k ind],:) = P([ind k],:)            //Fin pivoteo parcial
      
     for j = k+1:m
         L(j,k) = U(j,k) / U(k,k)
         U(j,k:m) = U(j,k:m) - L(j,k)*U(k,k:m)
     end 
    end
endfunction


A8=[1.012 -2.132 3.104;
    -2.132 4.096 -7.013;
    3.104 -7.013 0.014];

[P,L,U] = egpp(A8)
disp(P);
disp(L);
disp(U);
