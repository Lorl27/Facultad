// ----------------------------
// jacobiana: diferencias finitas (columna i = df/dx_i)
// ----------------------------
function J = alter_jacobiana(fn, x, h)
    n = length(x);
    J = zeros(n, n);
    fx = fn(x);
    for i = 1:n
        xh = x;
        xh(i) = xh(i) + h;
        J(:, i) = (fn(xh) - fx) / h;
    end
endfunction

// ----------------------------
// newton_multi: Newton para sistemas
// Devuelve [xr, info] donde info es una estructura con campos:
// info.converged (boolean), info.iter (nº iteraciones), info.message (string)
// Parámetros: fn (función que recibe vector y devuelve vector), x0 (vector inicial),
// tol (tolerancia en norma 2 del paso), maxit, h (paso para jacobiana numérica)
// ----------------------------
function [xr, info] = alter_newton_multi(fn, x0, tol, maxit, h)
    xr = x0;
    info.converged = %f;
    info.iter = 0;
    info.message = "No iterado aún";
    for k = 1:maxit
        J = alter_jacobiana(fn, xr, h);
        F = fn(xr);
        // intentamos resolver J * delta = F
        // usamos operador \ que es más estable que inv(J)
        // comprobamos si J está cerca de singular
        if cond(J) > 1e12 then
            info.message = "Jacobian near singular (cond>1e12) en iteración " + string(k);
            break;
        end
        delta = J \ F;      // solve J delta = F
        xr_new = xr - delta;
        info.iter = k;
        // criterio de parada: norma del paso
        if norm(xr_new - xr, 2) <= tol then
            xr = xr_new;
            info.converged = %t;
            info.message = "Convergió";
            return;
        end
        xr = xr_new;
    end
    // si salió del for sin converger:
    if info.converged == %f then
        info.message = "No convergió en maxit";
    end
endfunction

// ----------------------------
// Definición del sistema pedido (Ej 10)
// F(x,y) = [ x^2 + x*y^3 - 9 ; 3*x^2*y - 4 - y^3 ]
// ----------------------------
function F = Sistema(v)
    x = v(1);
    y = v(2);
    F = [ x^2 + x*y^3 - 9;
          3*x^2*y - 4 - y^3 ];
endfunction

// ----------------------------
// Script que corre Newton para los 4 inicios pedidos
// ----------------------------
h = 1e-6;        // paso para jacobiana numérica
tol = 1e-10;     // tolerancia en la norma del paso
maxit = 50;      // máximo de iteraciones

inits = [ 1.2,  -2,  -1.2,  2;
          2.5,  2.5, -2.5, -2.5 ]; // cada columna es un vector inicial

for i = 1:size(inits, 2)
    x0 = inits(:, i);
    printf("\n--- Inicial %d: (%.4f, %.4f) ---\n", i, x0(1), x0(2));
    [xr, info] = alter_newton_multi(Sistema, x0, tol, maxit, h);
    if info.converged then
        printf("Convergió en %d iteraciones.\n", info.iter);
    else
        printf("No convergió en %d iteraciones. Mensaje: %s\n", maxit, info.message);
    end
    printf("  Solución aproximada: x = %.8f, y = %.8f\n", xr(1), xr(2));
    printf("  Residuo ||F(x)||_2 = %.3e\n", norm(Sistema(xr),2));
end
