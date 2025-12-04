// xi^{k+1} = 1/aii (bi - sum_{j=1, j/=i}^{n} aij xj^{k})
function x = jacobi(A, b, x0, eps)
    n = size(A, 1);
    cont = 0;
    x = x0;
    xk = x;
    
    for i=1:n
        suma = 0; 
        for j = 1:n
            if (j ~= i)
                suma = suma + A(i,j) * xk(j);
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
                    suma = suma + A(i,j) * xk(j);
                end
            end
            x(i) = 1/A(i,i) * (b(i) - suma);
        end
        cont = cont + 1;
    end
    disp(cont);
endfunction


//---
//A=[1 -1 0; -1 2 -1 ; 0 -1 1.1]
//b=[0 ; 1 ; 0]
//x0=[0 ;1/2 ;0]
//x=jacobi(A,b,x0,0.01)


A=[10 3 1 ; 2 -10 3 ; 1 3 10]
b=[14 ; -5 ; 14]
x0=[0 ;0 ;0]
x=jacobi(A,b,x0,0.01)

//============

A=[2 -1 0 ; -2 -5 -1 ; -1 0 3]
b=[1 ; -6 ; 2]
x0=[0 ;0 ;0]
x=jacobi(A,b,x0,0.01)
