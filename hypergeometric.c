#include "hypergeometric.h"

/* hypergeometric.c
 * This file contains the definitions of the constructor and stepper.
 */

hyper_state hyper_construct(index initial_n, real first_term, function recur) {
    hyper_state iterator;
    iterator.n = initial_n;
    iterator.term = first_term;
    iterator.total = first_term;
    iterator.recur = recur; // TODO: do we really have a good reason to change
    // the recurrence relation in the middle of a computation? Maybe we should
    // encapsulate hyper_state as an opaque pointer and make the constructor a
    // void-returning method.

    return iterator;
}

void hyper_step(hyper_state *iterator, real x) {
    iterator->term *= x * (iterator->recur)(iterator->n);
    iterator->total += iterator->term;
    ++(iterator->n);
}
