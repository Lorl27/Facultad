// Tiempo : strlen: O(n) + strelen(O) = O(n)*O(n) del strcat = O(n^2) = O(len^2).
// Memoria:  O(1)
void repetir_hasta_llenar(char *s, char *res, int len){
    *res = 0;

    while(strlen(res) + strlen(s) + 1 < len){
        strcat(res, s);
    }
}

//Mejorada:
// Tiempo : O(len).
// Memoria:  O(1)
void repetir_hasta_llenar(char *s, char *res, int len){
    *res = 0;
    int tamRes=0;
    int longi=strlen(s);
    while(tamRes + longi + 1 < len){
        memcpy(res + tamRes, s, longi);
        tamRes+=longi;
    }

    res[tamRes] = '\0';
}