#include "statistics.h"
#include <math.h>

long double mean(double *v, unsigned long long len) {
    unsigned long long i = 0;
    long double sum = 0;
    for (i = 0; i < len; i++)
        sum += v[i];
    return sum / (long double)len;
}

long double stddev(double *v, unsigned long long len, long double mean) {
    unsigned long long i = 0;
    long double sum = 0, temp = 0;
    for (i = 0; i < len; i++) {
        // melhor fazer isso:
        temp = v[i] - mean;
        sum += temp * temp;
        // do que isso:
        //sum += pow(v[i] - mean, 2);
    }
    sum = sum / (long double)len;
    return sqrtl(sum);
}