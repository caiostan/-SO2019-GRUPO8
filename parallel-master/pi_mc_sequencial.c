#include <stdio.h>
#include <time.h>
#include "random.h"

// 10^8 leva aproximadamente 1,5 segundo para ser processado
// 10^9 leva aproximadamente 15 segundos para ser processado
// 10^10 leva aproximadamente 150 segundos para ser processado
// ...
#define MAX 100000000

long double pi() {
    unsigned long long int acertos = 0;
    unsigned long long int i = 0;
    for (i = 0; i < MAX; i++) {
        double x = randomNumber();
        double y = randomNumber();
        if (x * x + y * y < 1) {
            acertos++;
        }
    }
    return 4.0 * acertos / MAX;
}

int main() {
    setSeed(time(NULL));  //semente para os numeros aleatorios
    printf("%.6Lf\n", pi());
}