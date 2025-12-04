//LISTA DE ERRORES :

// Tabla de valores de h con notación científica y decimal
clc;
clear;

h_vals = [1e-1; 1e-2; 1e-3; 1e-4; 1e-5; 1e-6; 1e-7; 1e-8; 1e-9; 1e-10];
comentarios = [
    "Error grande";
    "";
    "";
    "Muy común en ejercicios";
    "";
    "Precisión alta";
    "";
    "";
    "Precisión extrema";
    "Cuidado con redondeo"
];

// Encabezado
printf("┌──────────────┬────────────────────┬──────────────────────────────┐\n");
printf("│  h (científica) │  h (decimal)       │ Comentario                   │\n");
printf("├──────────────┼────────────────────┼──────────────────────────────┤\n");

// Filas
for i = 1:size(h_vals, "*")
    printf("│  %10.0e   │  %-.14f  │ %-26s │\n", h_vals(i), h_vals(i), comentarios(i));
end

// Pie
printf("└──────────────┴────────────────────┴──────────────────────────────┘\n");

//COMUNMENTE SE USA 1E-4 Y |E-6.
