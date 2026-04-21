#include "myblas.h"

void dcopy(int n, const double* X, double* Y) {
    for (int i = 0; i < n; ++i) Y[i] = X[i];
}