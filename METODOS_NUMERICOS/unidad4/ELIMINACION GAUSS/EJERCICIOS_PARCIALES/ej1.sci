//3. con el objetivo de reducir la cantidad de operaciones para ciertos tipos de matrices , se puede adaptar el algoritmo de eliminación de Gauss.
//
//a- implementar en scilab el algoritmo de eliminación de Gauss para el caso particular en que el sistema lineal a resolver tiene una matriz de coeficientes A  tal que se verifica que a sub (ij) = 0  para todo i>(j+1)
//El algoritmo también debe retornar la cantidad de operaciones (+,-,*,/) que se realizaron en el calculo
//
//b- Usando el algoritmo anterior resolver el sistema Ax=b dado por A e R^(nxn)  y b e R^n con elementos
//
//a sub (ij) = { 1 / (i+j-1) para i>(j+1)  ; 0 en otro caso}  y b sub i =  i   . para n=20

//A.
//IDEA: esto es una eliminación de Gauss adaptada para una matriz banda superior de ancho 2, es decir: 𝑎IJ=0 si i>j+1
//solo hay elementos en la diagonal principal y una subdiagonal inmediata (la fila i solo tiene valores hasta la columna i+1.
//Es decir, hay 0 baho la subdiagonal y solo hay que anular a subi,k para i=k+1
//================================
// ============================================================
// 🔹 Eliminación de Gauss adaptada para matrices con banda 2
// (a_ij = 0 para i > j+1)
// ============================================================
// Entrada: 
//   A → matriz (n×n)
//   b → vector (n×1)
// Salida:
//   x → solución del sistema Ax=b
//   ops → estructura con cantidad de operaciones
// ============================================================

function [x, ops] = gauss_banda2(A, b)
    [n, m] = size(A);
    if n <> m then
        error("La matriz A debe ser cuadrada.");
    end

    // Contadores
    suma = 0; resta = 0; mult = 0; divi = 0; total=0;

    // Eliminación progresiva (solo en banda)
    for k = 1:n-1
        if A(k,k) == 0 then
            error("Pivote nulo en fila "+string(k));
        end

        // Solo fila siguiente (banda 2)
        i = k+1;
        if i <= n then
            m_ik = A(i,k) / A(k,k);
            divi = divi + 1;
            A(i,k) = 0;
            A(i,k+1) = A(i,k+1) - m_ik * A(k,k+1);
            resta = resta + 1; mult = mult + 1;
            b(i) = b(i) - m_ik * b(k);
            resta = resta + 1; mult = mult + 1;
        end
    end

    // Sustitución regresiva
    x = zeros(n,1);
    for i = n:-1:1
        if i == n then
            x(i) = b(i) / A(i,i);
            divi = divi + 1;
        else
            x(i) = (b(i) - A(i,i+1)*x(i+1)) / A(i,i);
            mult = mult + 1; resta = resta + 1; divi = divi + 1;
        end
    end

    // Guardar operaciones
    ops = struct("sumas",suma,"restas",resta,"mult",mult,"div",divi);
    total=suma+resta+mult+divi;
    disp("EL TOTAL ES:",total);
endfunction


// ============================================================
// 🔹 Construcción del sistema y resolución para n=20
// ============================================================
n = 20;
A = zeros(n,n);
b = (1:n)'; // bi = i

for i = 1:n
    for j = 1:n
        if i <= j+1 then
            A(i,j) = 1 / (i + j - 1);
        else
            A(i,j) = 0;
        end
    end
end

// Resolver con el método adaptado
[x, ops] = gauss_banda2(A, b);

// Mostrar resultados
disp("───────────────────────────────");
disp("Solución x ≈ ");
disp(x');
disp("───────────────────────────────");
disp("Conteo de operaciones:");
disp(ops);
disp("───────────────────────────────");



// UNA MATRIZ DE BANDA 2 ES AQUELLA QUE TIENE ELEMENTOS DISTITNOS DE CERO EN 
// - LA DIAGONAL PRICIPAL
// - LA SUPERDIAGONAL INMEDIANTA (I=J-1) Y LA SUBDIAGONAL OINMEDIATA (I=J+1))

//ES DECIR:  (n=5)
//1 2 0 0 0;
//1 2 3 0 0;
//0 1 2 3 0;
//0 0 1 2 3;
//0 0 0 1 2

A = [4 1 0 0 0;
     2 3 1 0 0;
     0 1 3 1 0;
     0 0 2 3 1;
     0 0 0 1 2];

disp(A);

// Ver como patrón visual (ceros en blanco)
disp("Matriz de banda 2:");
for i=1:5
    for j=1:5
        if A(i,j) == 0 then
            printf("   . ");
        else
            printf("%4.1f ", A(i,j));
        end
    end
    printf("\n");
end


///B:
// ===========================================
// 🔹 Matriz de banda 2: a(i,j) = 1/(i+j-1) si i <= j+1
// ===========================================
n = 6;
A = zeros(n,n);

for i = 1:n
    for j = 1:n
        if i <= j+1 then
            A(i,j) = 1 / (i + j - 1);
        else
            A(i,j) = 0;
        end
    end
end

// Mostrar matriz numérica
disp("Matriz A:");
disp(A);

// Mostrar patrón visual
disp("───────────────────────────────");
disp("Visualización (. = 0)");
for i = 1:n
    for j = 1:n
        if A(i,j) == 0 then
            printf("   .   ");
        else
            printf("%6.3f ", A(i,j));
        end
    end
    printf("\n");
end
disp("───────────────────────────────");
