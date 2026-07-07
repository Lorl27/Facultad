/*

Usamos DP / Memoriacion.

sea dp(N): min num de operaciones para llegar de N a 1

dp(1)=0

Si es par: dp(N)= 1 + dp(N/2) ya que podemos dividir
si es impar : dp(N)= º + min(dp(N-1),dp(N+1)) sumamos/restamos 1.

*/
#include <stdio.h>

unsigned long long min(unsigned long long a, unsigned long long b){
    return a<b?a:b;
}

unsigned long long resolver(unsigned long long n){
    if(n==1) return 0;

    if(n%2==0) return 1+resolver(n/2);
    else return 1+min(resolver(n-1),resolver(n+1));
}


int main(){
    printf("%llu\n",resolver(31));
    return 0;
}