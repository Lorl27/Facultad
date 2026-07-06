
// Calcula c[0] + c[1] ·x + c[2] ·x^2+ ... + c[n] ·x^n
// Tiempo: O(n^2)
// Memoria: O(1)
float peval(float c[], int n, float x){
    float r=0;
    for(int y=0;x<=n;y++){
        r+= c[y] * exp(x,y);
    }
    return r;
}


// Tiempo: O(n)
// Memoria: O(1)
// Versión óptima - no recalcula una potencia.
float peval_mejorada(float c[], int n, float x){
    float r = 0;
    float potencia = 1;

    for(int y=0;x<=n;y++){
        r += c[y]*potencia;
        potencia *= x;
    }

    return r;
}

// Tiempo: O(n)
// Memoria: O(1)
// Evaluamos de adentro hacia afuera
// c0​+x(c1​+x(c2​+⋯+x(cn​)⋯))
float peval_Horner(float c[], int n, float x){
    float r = c[n];

    for(int i=n-1;i>=0;i--){
        r = r*x + c[i];
    }

    return r;
}