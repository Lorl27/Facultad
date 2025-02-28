# Para ejecutar el programa:
1. gcc archivo.c
2. ./a.exe

* Si quiero nombrarlo: 
1. gcc archivo.c -o nombre.exe 
2. ./nombre.exe

----
## LIBRERÍAS:
* stdio.h , math.h string.h , stdlib.h

---

''' strlen(c) != char c[10]='hi'; (2 vs 10-1) '''
El fin de cadena es el caracter ‘\0’

**PARA LEER strings:**
1. scanf("%s", string);  **//no se pone el operador  & al leer un  array.**
2.  fgets(mensaje,sizeof(mensaje),stdin); //Utilizamos fgets para poder leer cadenas largas
    mensaje[strcspn(mensaje,"\n")]='\0'; //Eliminamos el salto de línea
3.  scanf(" %[^\n]",nam); //Eliminamos el salto de línea
---
### i++ vs ++i
- I++ : El operador tiene menos precedencia que cualquier 
otro. Por lo tanto, se incrementa la variable luego de usarla
- ++I: Se incrementará la variable ANTES de usarla


#### Punteros y arrays:
char a[10];
a==&a==a[0];

int b;
int *p=b;
*p=5
p[1]=10;

printf("primer %d, sgundo %d",b[0],b[1]);  --> 5 , 10.

---
### PUNTEROS:

**Básico:**
int i=5;
dirrección: printf("&p", %i);

*declaración puntero:* char* p; , int* p;
int* p=&i ; //Guardamos la dirección de memoria del entero, en un puntero.
printf("%d",*p) --> i --> 5


**Ejemplo de USO (en funciones):**
void calcular_edades(float *edad_media) {
    int edad, pacientes_ingresados = 0,suma_Edad=0;
    suma_Edad+= edad;
    pacientes++;

    *edad_media=suma_Edad/pacientes;
}

int main(){
    float edad_media;
    calcular_edades(&edad_media);
}

**Para pedir memorias:**
int* puntero;
puntero= malloc(sizeof(int)*TAM);

for( int x=0; x<TAM;x++){
    puntero[x]=x;    ---> *(puntero+x) == puntero[x]
}

for(intx=0;x<TAM;x++){
    printf("valor: %d",puntero[x]);  --> &p[x] == p+x (dirreccion memoria)
}

free(puntero);

---
## Estructuras:

1. struct Persona{
    char* name;
    int edad;
}; 

2. typedef struct {
    char* name;
    int edad;
} Persona; 

*****
1. struct Persona.p1;   
p1.name="Something";

2. Persona p1;

## Estructuras  y punteros:

struct Persona* p1;
p1=malloc(sizeof(struct Persona));

Para acceder a sus campos: (*p1).nombre == p1->nombre;

