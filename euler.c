#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "hypergeometric.h"

real exp_recur(index n) {
    return 1.0 / (n + 1);
}

int main(void) {
    real error = 1e-16;
    real x = 1.0;
    hyper_state euler_state = hyper_construct(0, x, exp_recur);
    while (fabs(euler_state.term) > error) hyper_step(&euler_state, x);

    printf("%1.20f \n", euler_state.total_F);
    return 0;
}
