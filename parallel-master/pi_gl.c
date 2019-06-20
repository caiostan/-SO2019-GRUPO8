#include <math.h>
#include <stdio.h>
#include <string.h>

// para aumentar o numero de iteracoes aumente esse numero
// maximo 16384, acima disso estoura o long double
#define MAX 10000
// note que esse metodo com apenas 3 iteracoes (MAX = 3)
// converge para pi com precisao 10^-17

long double a(int n);
long double b(int n);
long double t(int n);
long double p(int n);

long double avalor[MAX + 1];  // guarda valor ja calculados
long double bvalor[MAX + 1];  // para evitar calculos repetidos
long double pvalor[MAX + 1];

char acalculado[MAX + 1];  // guarda se o valor pedido ja foi calculado
char bcalculado[MAX + 1];  // para evitar calculos repetidos
char pcalculado[MAX + 1];

long double a(int n) {
    if (!acalculado[n]) {  // se ainda nao foi calculado, calcula
        if (n == 0) {
            acalculado[n] = 1;  // marca q esse valor foi calculado
            // calcula, guarda e retorna:
            return avalor[n] = 1.0;
        } else {
            acalculado[n] = 1;  // marca q esse valor foi calculado
            // calcula, guarda e retorna:
            return avalor[n] = (a(n - 1) + b(n - 1)) / 2.0;
        }
    } else {  // se ja foi calculado, retorna valor guardado
        return avalor[n];
    }
}

long double b(int n) {
    if (!bcalculado[n]) {  // se ainda nao foi calculado, calcula
        if (n == 0) {
            bcalculado[n] = 1;  // marca q esse valor foi calculado
            // calcula, guarda e retorna:
            return bvalor[n] = 1.0 / sqrtl(2.0);
        } else {
            bcalculado[n] = 1;  // marca q esse valor foi calculado
            // calcula, guarda e retorna:
            return bvalor[n] = sqrtl(a(n - 1) * b(n - 1));
        }
    } else {  // se ja foi calculado, retorna valor guardado
        return bvalor[n];
    }
}

long double t(int n) {  // nunca eh recalculado => nao precisa ser guardado
    if (n == 0) {
        return 0.25;
    } else {
        return t(n - 1) - p(n - 1) * powl(a(n - 1) - a(n), 2);
    }
}

long double p(int n) {
    if (!pcalculado[n]) {  // se ainda nao foi calculado, calcula
        if (n == 0) {
            pcalculado[n] = 1;  // marca q esse valor foi calculado
            // calcula, guarda e retorna:
            return pvalor[n] = 1;
        } else {
            pcalculado[n] = 1;  // marca q esse valor foi calculado
            // calcula, guarda e retorna:
            return pvalor[n] = 2.0 * p(n - 1);
        }
    } else {  // se ja foi calculado, retorna valor guardado
        return pvalor[n];
    }
}

long double pi(int n) {
    return powl(a(n) + b(n), 2.0) / (4.0 * t(n));
}

int main() {
    memset(acalculado, 0, sizeof(acalculado));  // define todas as contas como 'ainda nao calculadas'
    memset(bcalculado, 0, sizeof(bcalculado));
    memset(pcalculado, 0, sizeof(pcalculado));
    printf("%.6Lf\n", pi(MAX));
}