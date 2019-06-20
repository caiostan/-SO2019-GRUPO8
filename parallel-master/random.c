#include "random.h"

unsigned long int x = 0;

void setSeed(unsigned long int seed){
    x = seed;
}

long double randomNumber() {
    x = (453816693 + 843314861 * x) % 2147483648;
    return ((long double)x / 2147483648);
}