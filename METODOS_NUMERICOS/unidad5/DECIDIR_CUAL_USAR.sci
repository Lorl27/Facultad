// 1) construir matrices D, L, U
D = diag(diag(A));
L = tril(A, -1);
U = triu(A, 1);

// 2) matrices de iteración
invD = diag(1./diag(D));
BJ = invD*(D - A);         // Jacobi: x^{k+1} = BJ*x^k + invD*b
BGS = inv(D + L) * (-U);   // Gauss-Seidel: x^{k+1} = BGS*x^k + (D+L)\b

// 3) obtener autovalores y radio espectral
evJ = spec(BJ);            // spec devuelve los autovalores (si tu Scilab lo soporta)
rhoJ = max(abs(evJ));
evGS = spec(BGS);
rhoGS = max(abs(evGS));

disp("rho(Jacobi)=" + string(rhoJ));
disp("rho(Gauss-Seidel)=" + string(rhoGS));


//--
//A=[1 -1 0; -1 2 -1 ; 0 -1 1.1]

A=[10 3 1 ; 2 -10 3 ; 1 3 10]
//Si rhoJ >= 1 => no usar Jacobi. Si rhoJ < 1, Jacobi converge pero puede ser más lento que GS.
