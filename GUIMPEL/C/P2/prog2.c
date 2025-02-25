#include <stdio.h>
#include <string.h>
#include <math.h>

// 1. Switch

// Ejercicio 1. Escriba un programa que pida por teclado el resultado obtenido al lanzar un
// dado de seis caras y muestre por pantalla el número en letras de la cara opuesta al resultado
// obtenido. En caso que el valor ingresado no sea válido para las caras de un dado, se debe
// mostrar el mensaje: "Número incorrecto".

// int main(){
//     int dado;
//     printf("Ingrese un nro [1..6]\n");
//     scanf("%i",&dado);
//     switch(dado){
//      case 1:
//         printf("6");
//         break;
//         case 2:
//         printf("5");
//         break;
//         case 3:
//         printf("4");
//         break;
//         case 4:
//         printf("3");
//         break;
//         case 5:
//         printf("2");
//         break;
//         case 6:
//         printf("1");
//         break;   
//         default:
//         printf("Nùmero incorrecto. [1..6] DIJE\n");
//     };}

/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/

// Ejercicio 2. En la siguiente tabla se muestra el número de camas de las habitaciones de una
// casa de campo y la planta donde está ubicada cada una de ellas:
// Se pide que escriba un programa que:
// 1. Muestre el listado de las habitaciones de la casa de campo.
// 2. Pida por teclado el número (dato entero) asociado a una habitación.
// 3. Muestre por pantalla la planta y el número de camas de la habitación seleccionada.
// Observación: Si el número introducido por el usuario no está asociado a ninguna habitación,
// se mostrará el mensaje: "Número no asociado a habitación."


// int main(){
//     int habitacion;
//     printf("Habitaciones disponibles: \n 1-Azul \n 2-Roja \n 3-Verde \n 4-Rosa \n 5-Gris\n");
//     printf("Elija una");
//     scanf("%i",&habitacion);
//     switch (habitacion)
//     {
//     case 1:
//         printf("Primera planta, 2 caMAS.\n");
//         break;
//         case 2:
//         printf("Primera planta, 1 caMAS.\n");
//         break;
//         case 3:
//         printf("Segunda planta, 3 caMAS.\n");
//         break;
//         case 4:
//         printf("Segunda planta, 2 caMAS.\n");
//         break;
//         case 5:
//         printf("Tercera planta, 1 caMAS.\n");
//         break;
    
//     default:
//     printf("Nùmero no asociado a ninguna habitaciòn, gil");
//         break;
//     }
// }


/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/

// 2. Estructura For
// Ejercicio 3. Calcule mediante bucles for las siguientes sumatorias

// float f1(){
//     float cont=0;
//     for(float x=1;x<=100;x++){
//         float xd=(1/x);
//         cont+=xd;
//     }
//     return cont;
// }

// float f2(){
//     float cont=0;
//     for(float x=1;x<=30;x++){
//         float xd=(1/(sqrt(x)));
//         cont+=xd;
//     }
//     return cont;
// }
// float f3(){
//     float cont=0;
//     for(float x=1;x<=25;x++){
//         float xd=(1/(pow(x,x)));
//         cont+=xd;
//     }
//     return cont;
// }
// float f4(){
//     float cont=0;
//     for(float x=2;x<=10;x++){
//         float xd=(1+x)*x;
//         cont+=xd;
//     }
//     return cont;
// }



//  int main(){
//     printf("%f\n%f\n%f\n%f\n",f1(),f2(),f3(),f4());

//  }



/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/

// Ejercicio 4. Una terna de números naturales (a, b, c) es una terna pitagórica si a2 + b2 = c2.
// Escriba un programa que imprima todas las ternas pitagóricas con a ≤ 20 y b ≤ 30.

// // int tp(unsigned int a , unsigned int b, unsigned int c){
// //     return pow(a,2)==pow(b,2)+pow(c,2) || pow(b,2)==pow(a,2)+pow(c,2) || pow(c,2)==pow(b,2)+pow(a,2);
// // }

// double main(){
   

//     for(float a=1;a<=20;a++){
//         for (float b=1;b<=30;b++){
//             float c=sqrt(pow(b,2)+pow(a,2));
//             // printf("%i\n",tp(a,b,c));
//             if(floor(c)==c)
//             printf("%0.0f+%0.0f+%0.0f\n",a,b,c);
//         }
//     }

// }

/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/

// Ejercicio 5. ¿Qué hace el siguiente programa?
// 1 # include < stdio .h >
// int main()
// {
//     int x, y;
//     printf(" Ingrese dos enteros dentro del rango [1 ,20]:\n ");
//     scanf("%d%d", &x, &y);
//     if (x >= 1 && y >= 1 && x <= 20 && y <= 20)
//     {
//         for (int i = 1; i <= y; i++)
//         {
//             for (int j = 1; j <= x; j++)
//             {
//                 printf("@");
//             }
//             printf("\n");
//         }
//     }
//     else
//     {
//         printf(" Los enteros no se encuentran en el rango pedido ");
//     }
//     return 0;
// }

/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/

// Ejercicio 6. Escriba un programa que tenga un número secreto entre 0 y 500, el cual estará
// fijo en el código (use #define para esto). El usuario deberá, mediante el ingreso de números,
// adivinar dicho valor. En cada intento el programa debe responder el número es mayor o el
// número es menor, según corresponda. El usuario dispondrá, como máximo, de 15 intentos.

// #define NS 250

// int main(){
//     int r=0,usu=0;
//     while(r<15 && NS!=usu){
//         printf("adivina el valor lol, rango<1000n\n");
//         scanf("%i",&usu);
//         r++;
//         if(usu<NS){
//             printf("n random es mayor\n");
//         }
//          else  if(usu>NS) {
//             printf("n random es menor\n");
//         }
//     }
    
// }

/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/

// Ejercicio 7. Mediante una única instrucción for y un printf genere la siguiente salida. Em-
// plee 3 variables: una para la cadena de texto, un entero y un char:
// b 5 T
// bu 4 s
// buc 3 R
// bucl 2 q
// bucle 1 P

// int main(){
//     char palabra[10], bucle[]="bucle",abc[]="pqrst";
//     int entero=5;
//     for(entero;entero>=1;entero--){
//         palabra[5-entero]=bucle[5-entero];
//         abc[5-entero];
//         printf("%s %i %c\n",palabra,entero,((&abc%2)=0) abc ? lower(abc));
//     }
// }


/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/
/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/



// Ejercicio 21. Escriba una función que reciba una cadena de caracteres y determine si la
// misma es capicúa.


// int main(){
//     char str[100];
//     printf("Ingrse una pàlabra: ");
//     scanf("%s",str);
//     int bandera=1;
//     int largo= strlen(str);
//     for(int x=0;x<largo;x++){
//         if(str[x]!=str[largo-x-1]){
//             bandera=0;
//         }
    
//     }
//     printf("%i\n",bandera);
// }

/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/

// Ejercicio 22. Escriba una función que reciba una cadena de caracteres y determine si es un
// pangrama, es decir, si para escribir la línea se utilizaron todos los caracteres del alfabeto.

// int main(){
//     char str[100];
//     int cache[26]={0}; //all 0
//     int bandera=1;

//     printf("pone una pal here brow\n");
//     scanf("%s",str);

//     int largo=strlen(str);

//     printf("%i\n",str[0]);
    
//     for(int x=0;x<largo;x++){
//         cache[str[x]-97]=1;
//     }
    
//     for(int a=0;a<26;a++){
//         if (cache[a]!=1){
//             bandera=0;
//         }
//         printf("%i",cache[a]);
//     }
//     if (bandera){
//         printf("\nes pangrama\n");
//     }else{
//         printf("\nno bro disculpa\n");
//     }
// }

/*AKDFUJDBGJGTFJHNBJTGNHJTGHJNTGJHNBFTGJHNBGT*/