// Newton para minimizar f(x1,x2) = 2 x1 + 3 x2^2 + exp(2 x1^2 + x2^2)
// Criterio: ||x_{k+1}-x_k||_2 <= 1e-12

function [g,H] = grad_hess(x)
    x1 = x(1); x2 = x(2);
    phi = 2*x1^2 + x2^2;
    E = exp(phi);
    // gradiente
    g = [ 2 + 4*x1*E;
          6*x2 + 2*x2*E ];
    // hessiana (corregida)
    H = [ E*(16*x1^2 + 4),  E*(8*x1*x2);
          E*(8*x1*x2),      6 + E*(4*x2^2 + 2) ];
endfunction

// Newton loop
x = [1.0; 1.0];       // x^(0)
tol = 1e-12;
maxit = 200;
iter = 0;
while iter < maxit
    iter = iter + 1;
    [g,H] = grad_hess(x);
    if cond(H) > 1e12 then
        disp("H casi singular — abortando");
        break;
    end
    delta = H \ g;
    xnew = x - delta;
    step = norm(xnew - x, 2);
    printf("iter %d: x = (%.12f, %.12f), step = %.3e\n", iter, xnew(1), xnew(2), step);
    x = xnew;
    if step <= tol then
        break;
    end
end

printf("\nResultado final tras %d iteraciones:\n", iter);
printf(" x* = (%.12f, %.12f)\n", x(1), x(2));
[g,H] = grad_hess(x);
printf(" ||grad f(x*)||_2 = %.3e\n", norm(g,2));
ev = spec(H);
printf("Autovalores de H en x*: %.6e  %.6e\n", ev(1), ev(2));
if ev(1) > 0 & ev(2) > 0 then
    disp("Hessiana definida positiva -> mínimo local estricto.");
else
    disp("Hessiana NO es definida positiva.");
end


//----------
// =============================================================
// MÉTODO DE NEWTON GENERAL PARA OPTIMIZACIÓN EN R²
// =============================================================
// Dado f(x1, x2), calcula numéricamente el gradiente y la hessiana
// para encontrar un punto crítico (mínimo, máximo o silla).
// -------------------------------------------------------------
// Entradas:
//   f       : función que recibe un vector x=[x1;x2]
//   x0      : punto inicial [x1_0; x2_0]
//   tol     : tolerancia de convergencia
//   maxit   : número máximo de iteraciones
//   h       : paso para derivadas numéricas
// -------------------------------------------------------------
// Salidas:
//   x*      : punto crítico aproximado
//   info    : estructura con iteraciones, gradiente, autovalores, etc.
// =============================================================

function [x, info] = newton_min_general(f, x0, tol, maxit, h)
    // Funciones auxiliares -------------------------
    function g = gradiente(f, x, h)
        g = zeros(2,1);
        for i = 1:2
            e = zeros(2,1); e(i) = 1;
            g(i) = (f(x + h*e) - f(x - h*e)) / (2*h);
        end
    endfunction

    function H = hessiana(f, x, h)
        H = zeros(2,2);
        for i = 1:2
            for j = 1:2
                ei = zeros(2,1); ej = zeros(2,1);
                ei(i) = 1; ej(j) = 1;
                H(i,j) = ( f(x + h*ei + h*ej) - f(x + h*ei - h*ej) ...
                          - f(x - h*ei + h*ej) + f(x - h*ei - h*ej) ) / (4*h^2);
            end
        end
    endfunction
    // ------------------------------------------------

    x = x0;
    iter = 0;
    while iter < maxit
        iter = iter + 1;
        g = gradiente(f, x, h);
        H = hessiana(f, x, h);
        if cond(H) > 1e12 then
            disp("⚠️ Hessiana casi singular — abortando");
            break;
        end
        delta = H \ g;
        xnew = x - delta;
        step = norm(xnew - x, 2);
        printf("Iter %d: x = (%.12f, %.12f), step = %.3e\n", iter, xnew(1), xnew(2), step);
        x = xnew;
        if step <= tol then
            break;
        end
    end

    // Evaluación final
    g = gradiente(f, x, h);
    H = hessiana(f, x, h);
    ev = spec(H);

    info.iter = iter;
    info.grad_norm = norm(g, 2);
    info.autovalores = ev;
    info.is_min = (ev(1) > 0 & ev(2) > 0);
endfunction


// Ejemplo del ejercicio 11:
function y = f(x)
    x1 = x(1); x2 = x(2);
    y = 2*x1 + 3*x2^2 + exp(2*x1^2 + x2^2);
endfunction

[x_opt, info] = newton_min_general(f, [1;1], 1e-12, 200, 1e-6);

disp("--------------------------------------------------");
disp("Resultado final:");
disp("x* = " + string(x_opt'));
disp("||grad f(x*)|| = " + string(info.grad_norm));
disp("Autovalores de H = " + string(info.autovalores'));
if info.is_min then
    disp("✅ Hessiana definida positiva -> Mínimo local estricto.");
else
    disp("⚠️ No es mínimo local (H no definida positiva).");
end
