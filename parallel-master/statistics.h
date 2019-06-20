#ifndef STATISTICS_H
#define STATISTICS_H

// reotrna a media do vetor
long double mean(double *v, unsigned long long len);
// retorna o desvio padrao do vetor
long double stddev(double *v, unsigned long long len, long double mean);

#endif