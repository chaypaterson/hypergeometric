#include "hypergeometric.h"

/* hypergeometric.c
 * This file contains the definitions of the constructor and stepper.
 */

hyper_state hyper_construct(index initial_n, real first_term, function recur) {
    hyper_state iterator;
    iterator.n = initial_n;
    iterator.term = first_term;
    iterator.total_F = first_term;
    iterator.recur = recur;

    return iterator;
}

void hyper_step(hyper_state *iterator, real x) {
    iterator->term *= x * (iterator->recur)(iterator->n);
    iterator->total_F += iterator->term;
    ++(iterator->n);
}
