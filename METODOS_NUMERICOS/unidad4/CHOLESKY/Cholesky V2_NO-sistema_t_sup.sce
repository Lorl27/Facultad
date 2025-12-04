function [U,ind] = cholesky(A)
// Factorización de Cholesky.
// Trabaja únicamente con la parte triangular superior.
//
// ind = 1  si se obtuvo la factorización de Cholesky.
//     = 0  si A no es definida positiva
//
//******************
eps = 1.0e-8
//******************

n = size(A,1)
U = zeros(n,n)

t = A(1,1)
if t <= eps then
    printf('Matriz no definida positiva.\n')
    ind = 0
    return
end
U(1,1) = sqrt(t)
for j = 2:n
    U(1,j) = A(1,j)/U(1,1)
end
    
for k = 2:n
    t = A(k,k) - U(1:k-1,k)'*U(1:k-1,k)
    if t <= eps then
        printf('Matriz no definida positiva.\n')
        ind = 0
        return
    end
    U(k,k) = sqrt(t)
    for j = k+1:n
        U(k,j) = ( A(k,j) - U(1:k-1,k)'*U(1:k-1,j) )/U(k,k)
    end
end
ind = 1

endfunction

//=============  EJEMPLOS:

A = [4 1 1; 8 2 2; 1 2 3]

[U,ind] = cholesky(A)
disp(U)
disp(ind)


B = [5 2 1 0; 2 5 2 0; 1 2 5 2; 0 0 2 5]
disp(B)
[U,ind] = cholesky(B)
disp(U)
disp(ind)

C = [5 2 1 0; 2 -4 2 0; 1 2 2 2; 0 0 2 5]
disp(C)
[U,ind] = cholesky(C)



//========================================== ejercicio 11:
//11. Se provee la factorizaci´on de Cholesky, programada en Scilab en la funci´on Cholesky.
//(a) Estudiar el c´odigo de la funci´on Cholesky.
//(b) Aplicar la funci´on para factorizar las siguientes matrices. En todos los casos verificar
//que la factorizaci´on es correcta.
//A ={
//16 −12 8 −16
//−12 18 −6 9
//8 −6 5 −10
//−16 9 −10 46
//} , B =
//{
//4 1 1
//8 2 2
//1 2 3}
// , C =
//{
//1 2
//2 4 }


A = [16 -12 8 -16;
     -12 18 -6 9;
      8 -6 5 -10;
     -16 9 -10 46];

B = [4 1 1;
     8 2 2;
     1 2 3];

C = [1 2;
     2 4];

disp("=== Matriz A ===");
[UA, indA] = cholesky(A);
if indA == 1 then
    disp("U(A) =",UA);
    disp( "Verificación UT * U =A",UA'*UA);
end

disp("=== Matriz B ===");
[UB, indB] = cholesky(B);
if indB == 1 then
    disp( "U(B) =",UB);
    disp("Verificación UT * U =B",UB'*UB);
end

disp("=== Matriz C ===");
[UC, indC] = cholesky(C);
if indC == 1 then
    disp("U(C) =",UC);
    disp("Verificación UT * U =C",UC'*UC);
end


