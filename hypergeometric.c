#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* hypergeometric.c
 * This is an iterative calculator of values of hypergeometric series
 * A hypergeometric series
 *      F(x) = \sum_n a_n x^n
 * is one for which successive coefficients are a rational function of n:
 *      a_{n+1} / a_n = A(n) / B(n)
 * where A and B are polynomials
 * This suggests an efficient way to calculate them.
 * In a struct:
 *     Store the total accumulated value of the sum so far, total_F.
 *     Store the value of the most recent term, a_n x.
 *     Store n.
 * To get the next term, calculate
 *      term *= x * A(n) / B(n)
 *      total_f += term
 *      n++
 *
 * We can put this iteration step in either a for or a while loop.
 * This iteration requires a constant number of operations to compute the n-th
 * term. This is much better than a naive implementation of Taylor series, which
 * might require n+1 multiplications to calculate a_n * x^n.
 */

typedef double real; // TODO real could be fixed point? not floating point
typedef unsigned int index;
typedef real (*function)(index n);

typedef struct {
    index n;
    real term;
    real total_F;
    function R;
} hyper_state;

hyper_state construct(index initial_n, real first_term, function recur) {
    hyper_state iterator;
    iterator.n = initial_n;
    iterator.term = first_term;
    iterator.total_F = first_term;
    iterator.R = recur;

    return iterator;
}

void hyper_step(hyper_state *iterator, real x) {
    iterator->term *= x * (iterator->R)(iterator->n);
    iterator->total_F += iterator->term;
    ++(iterator->n);
}

// those are the general methods: now, a specific recurrence.

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
    hyper_state first_part = construct(0, one_fifth, atan_recurrence);

    while (fabs(first_part.term) > error) 
        hyper_step(&first_part, one_fifth * one_fifth);

    real one_239th = 1.0 / 239;
    hyper_state next_part = construct(0, one_239th, atan_recurrence);

    while (fabs(next_part.term) > error) 
        hyper_step(&next_part, one_239th * one_239th);

    real piover4 = 4 * first_part.total_F - next_part.total_F;

    printf("and pi is: %1.20f \n", 4 * piover4);
    printf("error: %1.20f \n", 4 * error);

    return 0;
}
