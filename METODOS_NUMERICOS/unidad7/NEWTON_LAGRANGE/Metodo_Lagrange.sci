clc; clear;

// =======================================================
// 1. HERRAMIENTA GENÉRICA (Interpolación Lagrange)
// =======================================================
// Esta función la usamos para reconstruir polinomios intermedios
function y = Lk(x,k)
    [Xn,Xm] = size(x);
    r = [x(1:k-1) x(k+1:Xm)];
    p = poly(r,"x","roots");
    pk = horner(p,x(k));
    y = p / pk;
endfunction

function z = interpolLagrange(x,y)
    [Xn,Xm] = size(x);
    pol = 0;
    for k = 1:Xm
        pol = pol + (Lk(x,k)*y(k));
    end
    z = pol;
endfunction

// =======================================================
// 2. DATOS DEL PROBLEMA (MODIFICAR AQUÍ EN EL PARCIAL)
// =======================================================

/// ==================== FOCO 1 : INTERPOLACION LAGRANGE NORMAL =======

//  ejercicio 1) dados los sig datos de exp(X) , hallar los valores aproximadoes de  exp(1/3) por interpolacion lineal y cubica, usando lagrange . Luego, graficar

// lineal
x1=[0,0.2]
y1=[1,1.2214]
// cubica
x2=[0,0.2,0.4,0.6]
y2=[1,1.2214,1.4918,1.8221]

lineal = interpolLagrange(x1,y1)
cubica = interpolLagrange(x2,y2)

rango = [-2:0.01:2]

//---- graficar ---
plot(rango,horner(lineal,rango),"r")
plot(rango,horner(cubica,rango),"b")
plot(rango,exp(rango),"g")
a=gca();
a.x_location = "origin";
a.y_location = "origin";
h1 = legend("Lineal","Cubico","e^x")

// ================ FOCO 2 : ENCONTRAR P , DADOS OTROS P =======

// A) Nodos (xj = j para j=0,1,2,3)
x_nodos = [0, 1, 2, 3]; 
val_eval = 2.5; // El valor donde queremos calcular el resultado final

// B) Definir los Polinomios DADOS como objetos de Scilab
// P01 = 2x + 1
s = poly(0, "x"); 
P_01 = 2*s + 1; 

// P02 = x + 1
P_02 = s + 1;

// C) Definir los valores puntuales DADOS
// P123 evaluado en 2.5 es 3
Val_P_123 = 3; 

// =======================================================
// 3. RESOLUCIÓN AUTOMÁTICA
// =======================================================

mprintf("=== RESOLUCIÓN PASO A PASO ===\n");

// PASO 1: RECUPERAR LOS VALORES Y (y0, y1, y2...)
// La clave es evaluar los polinomios que nos dan en sus respectivos nodos.

// P_01 interpola x0 y x1
y0 = horner(P_01, x_nodos(1)); // eval en x0
y1 = horner(P_01, x_nodos(2)); // eval en x1

// P_02 interpola x0 y x2
// y0_check = horner(P_02, x_nodos(1)); // Debería dar igual a y0
y2 = horner(P_02, x_nodos(3)); // eval en x2

mprintf("1. Valores recuperados de los polinomios dados:\n");
mprintf("   y0 = %.2f\n", y0);
mprintf("   y1 = %.2f\n", y1);
mprintf("   y2 = %.2f\n", y2);


// PASO 2: CONSTRUIR EL POLINOMIO FALTANTE (P_012)
// Para usar la fórmula final necesitamos P_012 y P_123.
// Ya tenemos P_123 evaluado. Nos falta P_012.
// Como ya tenemos y0, y1, y2, lo construimos con Lagrange normal.

x_sub = [x_nodos(1), x_nodos(2), x_nodos(3)]; // x0, x1, x2
y_sub = [y0, y1, y2];

P_012 = interpolLagrange(x_sub, y_sub);
Val_P_012 = horner(P_012, val_eval);

mprintf("\n2. Polinomio intermedio P_0,1,2 construido:\n");
disp(P_012);
mprintf("   Evaluado en %.2f da: %.4f\n", val_eval, Val_P_012);


// PASO 3: APLICAR FÓRMULA DE RECURRENCIA DE NEVILLE
// Queremos P_0,1,2,3
// Formula: P_0..3(x) = [ (x - x3)*P_0..2(x) - (x - x0)*P_1..3(x) ] / (x0 - x3)
// Nota: Se cruzan los extremos. P_0..2 no tiene x3. P_1..3 no tiene x0.

x0 = x_nodos(1);
x3 = x_nodos(4);

Numerador = (val_eval - x3)*Val_P_012 - (val_eval - x0)*Val_P_123;
Denominador = x0 - x3;

Resultado = Numerador / Denominador;

mprintf("\n3. Aplicando fórmula de recurrencia final:\n");
mprintf("   P_0123(%.1f) = [ (%.1f - %.1f)*%.4f - (%.1f - %.1f)*%.4f ] / (%.1f - %.1f)\n",...
        val_eval, val_eval, x3, Val_P_012, val_eval, x0, Val_P_123, x0, x3);

mprintf("\nRESULTADO FINAL: %.4f\n", Resultado);

// ==== foco 3 : formula de interpolación g+enerica al foco 2:

//----- EJ 5:
//x = [0,1,2,3]
//y = [1,3,3,k]

//P_123(x) =L1(x)*3 + L2(x)*3 + L3(x)* k
//P_123(2.5) =L1(2.5)*3 + L2(2.5)*3 + L3(2.5)* k = 3


x = [1,2,3]
L1 = Lk(x,1)
L2 = Lk(x,2)
L3 = Lk(x,3)

c1 = horner(L1,2.5)*3
c2 = horner(L2,2.5)*3
c3 = horner(L3,2.5)
k = (3-c1-c2)/c3

xx = [0,1,2,3]
yy = [1,3,3,k]

p = interpolLagrange(xx,yy)

res = horner(p,2.5)
