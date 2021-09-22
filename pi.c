#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "hypergeometric.h"

real atan_recurrence(index n) {
    real real_n = n;
    real ratio = - (2 * real_n + 1) / (2 * real_n + 3);
    return ratio;
}

int main(void) {
    // calculate pi from Machin's formula as a test:
    real error = 1e-14 / 4; 
    // any lower and we run into problems with finite precision and roundoff
    // TODO really "real" should denote a fixed precision number and not a
    // floating point number.

    real one_fifth = 0.2;
    hyper_state first_part = hyper_construct(0, one_fifth, atan_recurrence);

    while (fabs(first_part.term) > error) 
        hyper_step(&first_part, one_fifth * one_fifth);

    real one_239th = 1.0 / 239;
    hyper_state next_part = hyper_construct(0, one_239th, atan_recurrence);

    while (fabs(next_part.term) > error) 
        hyper_step(&next_part, one_239th * one_239th);

    real piover4 = 4 * first_part.total - next_part.total;

    printf("and pi is: %1.20f \n", 4 * piover4);
    printf("error: %1.20f \n", 4 * error);

    return 0;
}
