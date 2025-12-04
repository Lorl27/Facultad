// ----------------------
// Factorizaciones Cholesky (dos formas) y comparación
// ----------------------

function demo_cholesky_dispersa()
    // vector a en R^5 (||a||<1)
    a = [0.10; -0.20; 0.30; -0.10; 0.05];
    n1 = size(a,1);
    n = n1 + 1;

    // Construir A = [1, a^T; a, I]
    A = [1, a';
         a, eye(n1,n1)];

    // RHS de ejemplo (el enunciado usa b,c; aquí usamos unos vectores de prueba)
    b_top = 0;          // escalar
    b_bot = zeros(n1,1); // vector
    RHS = [b_top; b_bot];

    disp("A (completa):");
    disp(A);

    // ---------- Primera factorización ----------
    M = eye(n1,n1) - a*a'; // I - a a^T
    // comprobar SPD
    ev = spec(M);
    if min(abs(ev)) <= 0 then
        error("I - a a^T no es SPD");
    end

    tic();
    R22 = chol(M); // R22 triangular superior (Scilab)
    // Construimos L1 y U1
    L1 = [1*eye(1,1), zeros(1,n1);
          a, R22']; // R22' es triangular inferior
    U1 = [1*eye(1,1), a';
          zeros(n1,1), R22];
    t1 = toc();

    printf("\nPrimera factorización (tiempo chol) = %g s\n", t1);
    disp("L1:");
    disp(L1);
    disp("U1:");
    disp(U1);

    // Resolver A x = RHS usando L1,U1
    tic();
    // Ly = RHS
    y1_top = RHS(1);
    y1_bot = R22' \ (RHS(2:$) - a*RHS(1)); // resolve R22'^T * y_bot = RHS_bot - a*b_top
    // ahora U x = y
    x_bot = R22 \ y1_bot;
    x_top = y1_top - a' * x_bot;
    x1 = [x_top; x_bot];
    tsolve1 = toc();

    printf("Resolución con primera factorización (tiempo) = %g s\n", tsolve1);
    disp("x (primera):");
    disp(x1);

    // ---------- Segunda factorización (reordenando) ----------
    // Reordenar las ecuaciones: permutar filas y columnas para formar [I a; a^T 1]
//////    P = [zeros(n1,1) eye(n1);
//////     matrix(1, 1, 1) zeros(1,n1)];
//////     // forma rápida de ilustración (no necesariamente needed)
//////    // en la práctica hacemos permutación tal que newA = [I a; a^T 1]
//////    A_perm = [eye(n1) , a;
//////              a', 1];
//////
//////    // calculamos s = sqrt(1 - a^T a)
//////    normsq = a' * a;
//////    if (normsq >= 1) then
//////        error("norm(a)^2 >= 1, no se cumple ||a||<1");
//////    end
//////    s = sqrt(1 - normsq);
//////
//////    tic();
//////    // L2 y U2
//////    L2 = [eye(n1) , zeros(n1,1);
//////      matrix(a', 1, n1), matrix(s, 1, 1)];
//////    U2 = [eye(n1) , matrix(a, n1, 1);
//////      zeros(1,n1), s];
//////    t2 = toc();
//////
//////    printf("\nSegunda factorización (construcción) = %g s\n", t2);
//////    disp("L2:");
//////    disp(L2);
//////    disp("U2:");
//////    disp(U2);
//////
//////    // Resolver con factorización 2 (en el orden permutado)
//////    // RHS must be permuted the same way; for demonstration take RHS_perm = [c; b] = [zeros; 0]
//////    RHS_perm = [zeros(n1,1); 0]; // example
//////    tic();
//////    // Ly = RHS_perm
//////    y_top = RHS_perm(1:n1);
//////    y_bot = (RHS_perm(n) - a' * y_top) / s;
//////    // U [v; x] = y  => x = (y_top - a * y_bot) because U top-right is a
//////    x_bot2 = y_top; // because top-left is I and top-right is a -> solve easily
//////    // last comp (scalar) x_last = (y_bot - 0)/s ??? careful with ordering, here only demo
//////    tsolve2 = toc();
//////
//////    printf("Resolución con segunda factorización (tiempo) = %g s (muy pequeño)\n", tsolve2);
//////
//////    // mostrar s y comprobar
//////    printf("\ns = sqrt(1 - ||a||^2) = %g\n", s);
endfunction

// Ejecutar demo
demo_cholesky_dispersa();


//--------
// =======================================================
// SISTEMA DISPERSO - FACTORIZACIONES DE CHOLESKY
// =======================================================
// -------------------------------------------------------

//clc;
//clear;

// === Paso 1: Definir vector a (||a|| < 1) y RHS (b, c) ===
a = [0.10; -0.20; 0.30; -0.10; 0.05];  // vector en R^5
n1 = length(a); 
n = n1 + 1; // tamaño total de la matriz (6x6)

b = 2;                        // escalar (primer componente RHS)
c = [1; 0; -1; 2; 0.5];       // vector (resto RHS)
rhs = [b; c];

// === Paso 2: Construir matriz A del sistema ===
A = [1, a';
     a, eye(n1, n1)];

disp("Matriz A:");
disp(A);

// =======================================================
// PRIMERA FACTORIZACIÓN
// =======================================================
// A = [1  a'; a  I] = [1 0; a R22'] * [1 a'; 0 R22]
// con (I - a a') = R22' * R22
// =======================================================
disp("============================================");
disp(" PRIMERA FACTORIZACIÓN ");
disp("============================================");

M = eye(n1, n1) - a*a'; // I - a a^T

tic();
R22 = chol(M); // Triangular superior
t1 = toc();

disp("R22 (Cholesky de I - a*at):");
disp(R22);
printf("Tiempo de cálculo de R22 = %.6f s\n", t1);

// --- Resolver el sistema usando esta factorización ---
tic();
// Paso 1: L y = RHS
y1 = b;                     // ecuación superior
y2 = R22' \ (c - a*b);      // (R22')*y2 = c - a*b

// Paso 2: U x = y
x2 = R22 \ y2;              // R22 * x2 = y2
x1 = y1 - a' * x2;          // x1 = b - a^T * x
t2 = toc();

sol1 = [x1; x2];

disp("Solución (primera factorización):");
disp(sol1);
printf("Tiempo de resolución = %.6f s\n", t2);

// =======================================================
// SEGUNDA FACTORIZACIÓN (reordenada)
// =======================================================
// [I  a; a'  1] = [I 0; a' s] * [I a; 0 s]
// con s = sqrt(1 - a^T a)
// =======================================================
disp("============================================");
disp(" SEGUNDA FACTORIZACIÓN ");
disp("============================================");

norma2 = a' * a;
if norma2 >= 1 then
    error("||a|| >= 1, no se cumple la condición.");
end
s = sqrt(1 - norma2);

disp("Escalar s = sqrt(1 - a^T a):");
disp(s);

// Reordenamos el sistema (equivalente a permutar filas y columnas)
//Ak2 = [eye(n1), a;
//      a', 1];
//rhs2 = [c; b];
//
//disp("Matriz reordenada A2:");
//disp(Ak2);

// Resolver con la segunda factorización
tic();
// L2 y = rhs2
y_top = c;                       // primeras n1 componentes
y_bot = (b - a' * c) / s;        // escalar

// U2 [v;x] = y
v = y_top;                       // v = y_top (porque I*v = y_top - a*x, pero a*x se ajusta después)
x = (y_bot - a' * v) / s;        // última variable
t3 = toc();

sol2 = [v; x];

disp("Solución (segunda factorización):");
disp(sol2);
printf("Tiempo de resolución = %.6f s\n", t3);

// =======================================================
// COMPARACIÓN FINAL
// =======================================================
disp("============================================");
disp(" COMPARACIÓN DE EFICIENCIA ");
disp("============================================");
printf("Primera factorización -> Costo: Cholesky (O((n-1)^3))\n");
printf("Segunda factorización -> Costo: sólo operaciones con un escalar s\n");
printf("=> La segunda factorización es MUCHO más eficiente.\n");

