#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"
#include "statistics.h"

/*
 * N eh o numero threads que serao abertas
 *
 * a maioria dos computadores hoje tem 4 nucleos
 * o sistema operacional nao deixa criar mais de 825
 * threads por processo ativo, mas nao eh bom passar
 * de umas 100
 */
#define N 8

double *trials = NULL;
long double S = 0, E = 0, r = 0, s = 0, T = 0;
unsigned long long M = 0;

sem_t semaforoMain;

long double max(long double a, long double b) { return ((a > b) ? a : b); }

void BSMC(unsigned long long *intervalo) {
    unsigned long long i = 0;

    unsigned long long inicial = intervalo[0];
    unsigned long long final = intervalo[1];

    for (i = inicial; i < final; i++) {
        long double t = S * expl((r - 0.5 * s * s) * T + s * sqrtl(T) * randomNumber());
        trials[i] = expl(-r * T) * max(t - E, 0);
    }
    sem_post(&semaforoMain);
}

int main(int argc, char *argv[]) {
    unsigned long long i = 0;

    setSeed(time(NULL));  //semente para os numeros aleatorios

    sem_init(&semaforoMain, 0, 0);

    /*
     * Este vetor 'intervalo' fala para cada thread em qual intervalo do
     * vetor 'trials' ela pode escrever seus resultados dividindo igualmente
     * a quantidade de trabalho para cada thread
     */
    unsigned long long **intervalo = NULL;

    pthread_t *threads = NULL;

    /*
     * Por favor, certifique-se de inserir
     * os valores de S, E, r, sigma, T e M
     * nessa ordem.
     */
    scanf("%Lf\n%Lf\n%Lf\n%Lf\n%Lf\n%llu", &S, &E, &r, &s, &T, &M);
    if (N > M) {
        printf("M deve ser maior que o numero de threads definido\n");
        exit(1);
    }

    /*
     * Quantidade de operacoes que sera designada para cada thread
     * eh a quantidade de iteracoes dividida pela quantidade de threads
     * arredondada para baixo pois deve ser um numero inteiro
     * ex: tenho 9 iteracoes e 3 threads cada uma deve realizar 3 operacoes
     */
    unsigned long long qtdOP = (unsigned long long)floorl(M / N);

    /*
     * Alocacao dos vetores de threads e o vetor trials do algoritmo
	 * de Black Scholes
     */
    threads = (pthread_t *)calloc(N, sizeof(pthread_t));
    trials = (double *)calloc(M, sizeof(double));

    /*
     * thread 0 tem intervalo[0][0](inicial) e intervalo[0][1](final)
     * thread i tem intervalo[i][0](inicial) e intervalo[i][1](final)
     * ...
     */
    intervalo = (unsigned long long **)calloc(N, sizeof(unsigned long long *));

    for (i = 0; i < N; i++) {
        intervalo[i] = (unsigned long long *)calloc(2, sizeof(unsigned long long));
        intervalo[i][0] = i * qtdOP;
        intervalo[i][1] = intervalo[i][0] + qtdOP;
        // intervalo incial + quantidade de operacoes por thread
        if (i == N - 1) intervalo[i][1] = M;
        // se for a ultima thread ela receve o M final para evitar o
        // problema do arredondamento (qtdOP)

        // criacao das threads retorna 0 se sucesso, qualquer outro
        // numero significa erro
        if (pthread_create(&threads[i], 0, (void *)BSMC, (void *)intervalo[i]) != 0) {
            printf("Erro ao criar thread #%llu, abortando.\n", i);
            fflush(0);
            exit(1);
        }
    }
    for (i = 0; i < N; i++) {
        sem_wait(&semaforoMain);
        // Espera todas as threads terminarem para continuar
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

    free(threads);
    free(trials);
    for (i = 0; i < N; i++) free(intervalo[i]);
    free(intervalo);

    return 0;
}
