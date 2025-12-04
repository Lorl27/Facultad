function A = A_eps(eps)
    A = [1 -1 0; -2 4 -2; 0 -1 1+eps];
    x = poly(0, "x");
    p_A = det(eye(3,3)*x - A);
        disp("=======================================");

    disp("El polinomio característico de A es: ");
    disp(p_A);
    disp("Sus raíces son: ");
    disp(roots(p_A));
    disp("Sus auutovalores son: ");
    disp(spec(A));
        disp("=======================================");

endfunction
//--------------=== EJERCICIO 3 -P6-
//3. Dada la siguiente matriz A(ε), para ε = 0.1k con k = 0, 1, . . . , 10:
//A(ε) =
{
//1 −1 0
//−2 4 −2
//0 −1 1 + ε
}
//Utilizar los comandos adecuados de SCILAB para:
//i) encontrar el polinomio caracter´ıstico y aproximar sus ra´ıces
//ii) hallar los autovalores de A(ε).

for k = 0:10
    eps = 0.1 * k;
    A_eps(eps);
end
