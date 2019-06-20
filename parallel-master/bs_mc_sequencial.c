#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "statistics.h"
#include "random.h"

long double max(long double a, long double b) { return ((a > b) ? a : b); }

int main(int argc, char *argv[]) {
    unsigned long long i = 0;

    setSeed(time(NULL));  //semente para os numeros aleatorios

    /*
     * Por favor, certifique-se de inserir
     * os valores de S, E, r, sigma, T e M
     * nessa ordem.
     */
    long double S = 0, E = 0, r = 0, s = 0, T = 0;
    unsigned long long M = 0;
    scanf("%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%llu", &S, &E, &r, &s, &T, &M);

    //Alocacao do vetor trials do algoritmo de Black Scholes
    double *trials = NULL;
    trials = (double *)calloc(M, sizeof(double));

    for (i = 0; i < M; i++) {
        long double t = S * expl((r - 0.5 * s * s) * T + s * sqrtl(T) * randomNumber());
        trials[i] = expl(-r * T) * max(t - E, 0);
    }

    long double tmean = mean(trials, M);
    long double tstddev = stddev(trials, M, tmean);
    long double confwidth = 1.96 * tstddev / sqrtl(M);
    long double confmin = tmean - confwidth;
    long double confmax = tmean + confwidth;

    printf("S        %d\n", (int)S);
    printf("E        %d\n", (int)E);
    printf("r        %d\n", (int)r);
    printf("sigma    %d\n", (int)s);
    printf("T        %d\n", (int)T);
    printf("M        %d\n", (int)M);
    printf("Confidence interval: (%.4Lf, %.4Lf)\n", confmin, confmax);

    free(trials);

    return 0;
}
