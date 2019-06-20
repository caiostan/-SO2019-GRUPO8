#include <math.h>
#include <stdio.h>
#include <string.h>

// para aumentar o numero de iteracoes aumente esse numero
// maximo 647, acima disso estoura o long double
#define MAX 10000
// note que esse metodo com apenas 2 iteracoes (MAX = 2)
// converge para pi com precisao 10^-15

long double a(int n);
long double s(int n);
long double r(int n);

long double rvalor[MAX + 1];  // guarda valor ja calculados para evitar calculos repetidos
char rcalculado[MAX + 1];  // guarda se o valor pedido ja foi calculado para evitar calculos repetidos

/*
 *  FORMULAS PARA CONVERGENCIA CUBICA
 */

long double a(int n) {
    if (n == 0) {
        return 1.0 / 3.0;
    } else {
        long double rr = r(n);
        return rr * rr * a(n - 1) - powl(3.0, n - 1) * (rr * rr - 1.0);
    }
}

long double s(int n) {
    if (n == 0) {
        return (sqrtl(3.0) - 1) / 2.0;
    } else {
        return (r(n) - 1) / 2.0;
    }
}

long double r(int n) {
    if (!rcalculado[n]) {   // se ainda nao foi calculado, calcula
        rcalculado[n] = 1;  // marca q esse valor foi calculado
        long double ss = s(n - 1);
        // calcula, guarda e retorna:
        return rvalor[n] = 3.0 / (1.0 + 2.0 * powl(1 - ss * ss * ss, 1.0 / 3.0));
    } else {  // se ja foi calculado, retorna valor guardado
        return rvalor[n];
    }
}

long double pi(int n) {
    return 1.0 / a(n);
}

int main() {
    memset(rcalculado, 0, sizeof(rcalculado));  // define todas as contas como 'ainda nao calculadas'
    printf("%.6Lf\n", pi(MAX));
}