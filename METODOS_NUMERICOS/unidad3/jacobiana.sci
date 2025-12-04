function jac = jacobiana(fn, val, h) //fn(función), xy(vector de valores iniciales), h(valor para derivadas)
    n = length(val);
    jac = zeros(n, n);
    i = 1;
    while i <= n
        valh = val;
        valh(i) = valh(i) + h;
        jac(:, i) = (fn(valh) - fn(val)) / h;
        i = i + 1;
    end
endfunction

function raiz = newton_multi(fn, val, n, h)
    valn = val;
    i = 1;
    while i <= n
        jac = jacobiana(fn, valn, h);
        delta = jac \ fn(valn);
        valn = valn - delta; 
        i = i + 1;
    end
    raiz = valn;
endfunction


/*Function f = Sistema(v)
  > x = v(1)
  > y = v(2)
  > f = [x^2 + x*y^3 - 9; 3*x^2*y - 4 - y^3];
> Endfunction

h=1e-6;
n = 5 (iteraciones)
> xy0=[1.2;2.5] (valores iniciales) )*/



// P3 - EJ 9 :

function f = Sistema(v)
    x = v(1);
    y = v(2);
    f = [1 + x^2 - y^2 + exp(x)*cos(y);
         2*x*y + exp(x)*sin(y)];
endfunction
/// sistema : 0=1+x2+^2 ... ; 0=2xy + ... 



h = 1e-6;  // error.
n = 5;  //iteraciones
xy0 = [-1; 4];  //valor inicial

resultado = newton_multi(Sistema, xy0, n, h)


// =============================
// EJERCICIO 10
// =============================

// Sistema no lineal
// 0 = x^2 + x*y^3 - 9
// 0 = 3*x^2*y - 4 - y^3
function F = Sistema(v)
    x = v(1);
    y = v(2);
    F = [ x^2 + x*y^3 - 9;
          3*x^2*y - 4 - y^3 ];
endfunction


// Parámetros
h = 1e-6;     // incremento para derivadas numéricas
n = 5;        // cantidad de iteraciones (como pide el enunciado)

// Valores iniciales
inits = [ 1.2,  -2,  -1.2,   2;
          2.5,   2.5, -2.5, -2.5 ];

// Bucle para probar los 4 casos
for i = 1:4
    printf("\nCaso %d:\n", i);
    xy0 = inits(:, i);
    printf("Valor inicial: (x0, y0) = (%.2f, %.2f)\n", xy0(1), xy0(2));

    resultado = newton_multi(Sistema, xy0, n, h);
    printf("Resultado tras %d iteraciones:\n", n);
    printf("  x = %.8f\n", resultado(1));
    printf("  y = %.8f\n", resultado(2));
    printf("  Norma del residuo: %.4e\n", norm(Sistema(resultado), 2));
end

/// ejericcio 12:
// ===============================================
// SISTEMA DEL EJERCICIO 12 (parte a)
// ===============================================

function F = SistemaK(v)
    k1 = v(1);
    k2 = v(2);
    k3 = v(3);

    // Datos conocidos
    r = [1; 2; 3];
    p_obs = [10; 12; 15];

    F = zeros(3,1);
    for i = 1:3
        F(i) = k1*exp(k2*r(i)) + k3*r(i) - p_obs(i);
    end
endfunction

// ===============================================
// RESOLUCIÓN CON NEWTON
// ===============================================
h = 1e-6;
n = 20;
k0 = [1; 0.1; 1]; // valores iniciales razonables

k_sol = newton_multi(SistemaK, k0, n, h);
printf("Solución aproximada:\n");
printf("k1 = %.6f\n", k_sol(1));
printf("k2 = %.6f\n", k_sol(2));
printf("k3 = %.6f\n", k_sol(3));


// =================================================
// PARTE (b) – Buscar r que satisfaga p(r) = 500/(pi*r^2)
// =================================================
function F = SistemaR(v)
    r = v(1);
    k1 = k_sol(1);
    k2 = k_sol(2);
    k3 = k_sol(3);
    F = k1*exp(k2*r) + k3*r - 500/(%pi * r^2);
endfunction

function dF = derivR(v)
    r = v(1);
    k1 = k_sol(1);
    k2 = k_sol(2);
    k3 = k_sol(3);
    dF = k1*k2*exp(k2*r) + k3 + (1000/(%pi*r^3)); // derivada de F(r)
endfunction

// Newton unidimensional
r = 2; // inicial
tol = 1e-8;
for i = 1:100
    Fr = SistemaR(r);
    dFr = derivR(r);
    rnew = r - Fr/dFr;
    if abs(rnew - r) < tol then
        break;
    end
    r = rnew;
end
printf("\nRadio mínimo para sostener 500 lb: r = %.6f pulgadas\n", r);
