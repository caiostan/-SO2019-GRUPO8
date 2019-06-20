#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"

/*
 * 10^8 leva aproximadamente 6,6 segundos para ser processado
 * 10^9 leva aproximadamente 66 segundos para ser processado
 * 10^10 leva aproximadamente 660 segundos para ser processado
 * ...
 */
#define MAX 100000000

/*
 * N eh o numero threads que serao abertas
 *
 * a maioria dos computadores hoje tem 4 nucleos
 * o sistema operacional nao deixa criar mais de 825
 * threads por processo ativo, mas nao eh bom passar
 * de umas 100
 */
#define N 16

pthread_mutex_t lockAcertos;
unsigned long long int acertos = 0;
sem_t semaforoMain;

void acertosF() {
    unsigned long long int i = 0;
    for (i = 0; i < MAX / N; i++) {
        double x = randomNumber();
        double y = randomNumber();
        if (x * x + y * y < 1) {
            pthread_mutex_lock(&lockAcertos);
            acertos++;
            pthread_mutex_unlock(&lockAcertos);
        }
    }
    sem_post(&semaforoMain);
    pthread_exit(NULL);
}

long double pi() {
    return 4.0 * acertos / MAX;
}

int main() {
    int i = 0;

    //semente para os numeros aleatorios
    setSeed(time(NULL));

    // mutex e semaforo
    pthread_mutex_init(&lockAcertos, NULL);
    sem_init(&semaforoMain, 0, 0);

    //vetor de threads para amarzenar seus enderecos
    pthread_t *threads = NULL;
    threads = (pthread_t *)calloc(N, sizeof(pthread_t));

    for (i = 0; i < N; i++) {
        // criacao das threads retorna 0 se sucesso, qualquer outro
        // numero significa erro
        if (pthread_create(&threads[i], 0, (void *)acertosF, NULL) != 0) {
            printf("Erro ao criar thread #%d, abortando.\n", i);
            fflush(0);
            exit(1);
        }
    }

    for (i = 0; i < N; i++) {
        sem_wait(&semaforoMain);
        // Espera todas as threads terminarem para continuar
    }

    printf("%.6Lf\n", pi());

    free(threads);
}