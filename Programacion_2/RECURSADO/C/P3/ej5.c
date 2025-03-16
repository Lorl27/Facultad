// Ejercicio 5. Los Números Complejos

#include <stdio.h>

// 1. Proponer una representación con estructuras para modelar un número complejo: 2 + 5i.

typedef struct nrosC {
    float real;
    float imaginario;
} Complejo;

// 2. Escriba una función de creación de un elemento del tipo Complejo, el cual tome dos datos, la
// parte entera y la parte compleja de un número, y retorne un elemento de tipo Complejo válido.

Complejo crear_Complejo(float entero, float complejo){
    Complejo c={entero,complejo};
    return c;
}

// 3. Escribir una función suma_complejo que reciba dos números complejos y devuelva la suma de
// éstos.

Complejo suma_Complejo(Complejo c1, Complejo c2){
    float partes_im= c1.imaginario + c2.imaginario;
    float partes_Re=c1.real + c2.real;

    Complejo suma={partes_Re,partes_im};

    return suma;
}

// 4. Escribir una función resta_complejos que reciba dos números complejos y devuelva la resta de
// éstos.

Complejo resta_Complejo(Complejo c1, Complejo c2){
    float partes_im= c1.imaginario - c2.imaginario;
    float partes_Re=c1.real - c2.real;

    Complejo resta={partes_Re,partes_im};

    return resta;
}

// 5. Escribir una función multiplica_complejos que reciba dos números complejos y devuelva el producto de éstos.

Complejo multiplica_Complejo(Complejo c1, Complejo c2){
    float multiplicacion_r1=c1.real*c2.real;
    float multiplicacion_r2=c1.imaginario*c2.imaginario; //SE VUELVE REAL!
    float multiplicacion_im1=c1.real*c2.imaginario;
    float multiplicacion_im2=c1.imaginario*c2.real;

    Complejo multiplica={multiplicacion_r1+multiplicacion_r2,multiplicacion_im1+multiplicacion_im2};

    return multiplica;
}

//-------------

void imprimir_C(Complejo c){
    printf("C= %.2f + (%.2f)i \n\n",c.real,c.imaginario);
}

//------------------------------

int main(void){
    float r1,r2,im1,im2;

    printf("Ingrese su Primer Complejo: \n");
    printf("Ingrese la parte REAL: ");
    scanf("%f",&r1);
    printf("Ingrese la parte IMAGINARIA: ");
    scanf("%f",&im1);

    Complejo c1=crear_Complejo(r1,im1);
    printf("Usted ha creado: ");
    imprimir_C(c1);

    printf("Ingrese su Segundo Complejo: \n");
    printf("Ingrese la parte REAL: ");
    scanf("%f",&r2);
    printf("Ingrese la parte IMAGINARIA: ");
    scanf("%f",&im2);

    Complejo c2=crear_Complejo(r2,im2);
    printf("Usted ha creado: ");
    imprimir_C(c2);

    Complejo suma=suma_Complejo(c1,c2);
    printf("La SUMA entre ambos es: \n");
    imprimir_C(suma);

    Complejo resta=resta_Complejo(c1,c2);
    printf("La RESTA entre ambos es: \n");
    imprimir_C(resta);

    Complejo multiplicacion=multiplica_Complejo(c1,c2);
    printf("La multiplicacion entre ambos es: \n");
    imprimir_C(multiplicacion);

    return 0;


}