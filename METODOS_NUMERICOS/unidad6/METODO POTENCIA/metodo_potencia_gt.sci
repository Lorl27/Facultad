// ==========================================================
// 🔹 MÉTODO DE LA POTENCIA
// ==========================================================

function [lambda_dom, v_dom, iter] = metodo_potencia(A, z0, tol, max_iter)
    n = size(A,1);
    z = z0 / norm(z0, "inf"); // normalizar inicial
    iter = 0;

    disp("Iteración | λ (aprox) | Vector z^n");
    disp("───────────────────────────────");

    while iter < max_iter
        iter = iter + 1;
        w = A * z;
        k = find(abs(w) == max(abs(w)), 1); // índice dominante
        lambda = w(k) / z(k); // estimación del autovalor
        z_next = w / norm(w, "inf");

        printf("%5d | %10.6f | ", iter, lambda);
        disp(z_next');

        if norm(z_next - z, "inf") < tol then
            break;
        end

        z = z_next;
    end

    lambda_dom = lambda;
    v_dom = z_next;
endfunction

// ==========================================================
// 🔸 Ejemplo de uso
// ==========================================================
A = [2 1; 1 3];
z0 = [1; 0];      // vector inicial
tol = 1e-6;
max_iter = 100;

[lambda_dom, v_dom, iter] = metodo_potencia(A, z0, tol, max_iter);

disp("───────────────────────────────");
printf("Autovalor dominante ≈ %.6f\n", lambda_dom);
disp("Autovector asociado (normalizado):");
disp(v_dom);
