INTRO
s={a11x1+a12x2+...+a1nxn=b1;
...
an1x1+an2x2+..+annxn=bn}

a=[a11....a1n;...;an1...ann]
b=[b1;...;bn]

s1=a11x1+0+...+0=b1;
...
0+0+...+annxn=bn}

y se solucional haciendo xi=bi/aii con i de 1 a n

se resuelve con x=b./diag(A))
//-----------------------------------
un sistema triangular es uno / :
a11x1+a22x2+....+a1nxn=b1;
0+a22x2+..+a2nxn=b2;
...
0+0+...ánnxn=bn}


y se soluciona con xn=bn/ann y luego con sus regrasiva obteniendose con

xi=1/aii * (bi - sumatoria de j=i+i a n de aij*xj)

x(n) = b(n)/A(n,n)
for i=n-1:-1:1
x(i) = ( b(i) - A(i,i+1:n)*x(i+1:n) )/A(i,i)
end

//----------------
Implementar en Scilab una funci´on remonte que tome como par´ametros
una matriz A triangular superior y un vector b y resuelva el sistema Ax = b
function x = remonte(A, b)
n = size(A,1)
x=zeros(n,1)
for i = n:-1:1
x(i) = (b(i) - A(i,i+1:n)*x(i+1:n)) / A(i,i)
end
endfunction


A = [2 1 -1;
     0 3 2;
     0 0 4];
b = [1; 2; 8];
x = remonte(A, b)

------

En general, cuando ya hay ceros por debajo de la diagonal, en las
columnas 1, 2, . . . , k − 1 para obtener cero en la posici´on (j, k) se hace la
operaci´on: ej = ej − ajk /akk ∗ ek
Esto lo podemos escribir es Scilab:
mjk = a(j,k)/a(k,k)
A(j, :) = A(j, :) - mjk * A(k, :)
b(j) = b(j) - mjk * b(k)


Si evitamos operar con los elementos que ya se han puesto en cero el esquema de la
triangulaci´on nos queda:
for k = 1:n-1
    for j = k+1:n
        mjk = A(j,k)/A(k,k)
        A(j,k) = 0
        A(j,k+1:n) = A(j,k+1:n) - mjk * A(k,k+1:n)
        b(j) = b(j) - mjk * b(k)
    end
end


Esta factorizaci´on LU permite resolver el sistema a trav´es de 2 sistemas
m´as sencillos
LU = A ←→ 
Ly = b,
Ux = y.
Ambos sistemas son triangulares, por ende f´aciles de resolver.
Este an´alisis es v´alido siempre que existan matrices L y U, triangular
inferior la primera y triangular superior la segunda tales que LU = A.
Existen varios m´etodos para encontrar estas matrices:
• lii = 1, Doolite,
• uii = 1, Crout,
• Si U = L
t
i.e. uii = lii, ∀i, Cholesky.
