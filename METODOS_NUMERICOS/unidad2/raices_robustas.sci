// EJERICICO 1 -P2  
//Crear una funci´on en Scilab que calcule en forma robusta las ra´ıces de una ecuaci´on cuadr´atica con discriminante positivo. Usar dicha funci´on para evaluar la ra´ız positiva de la ecuaci´on
///cuadr´atica ǫx2 + (1/ǫ)x − ǫ = 0 con ǫ = 0,0001 y estimar su error.


deff('x=discriminante(a,b,c)','x=b*b-4*a*c')

//b>0
deff('x=bp_rn(a,b,c)','x=(-b-sqrt(discriminante(a,b,c)))/(2*a)')
deff('x=bp_rp(a,b,c)','x=(2*c)/(-b-sqrt(discriminante(a,b,c)))')

//b<0
deff('x=bn_rn(a,b,c)','x=(2*c)/(-b+sqrt(discriminante(a,b,c)))')
deff('x=bn_rp(a,b,c)','x=(-b+sqrt(discriminante(a,b,c)))/(2*a)')

//f. principal:
function [x1,x2] = raices_robustas(a,b,c)
    if b > 0 then
        x1 = bp_rn(a,b,c);
        x2 = bp_rp(a,b,c);
    else
        x1 = bn_rn(a,b,c);
        x2 = bn_rp(a,b,c);
    end
endfunction


// evaluamos ǫx2 + (1/ǫ)x − ǫ = 0 con ǫ = 0,0001
q= 0.0001;
a=q;
b=(1/q);
c=-q;

[x1,x2]=raices_robustas(a,b,c);
disp(x1, "Raíz 1:");
disp(x2, "Raíz 2:");

// Comparación con la raíz exacta
x_exacto = (-b + sqrt(discriminante(a,b,c))) / (2*a);
error = abs(x2 - x_exacto);
disp(x_exacto, "Raíz exacta positiva:");
disp(error, "Error en la raíz positiva:");
