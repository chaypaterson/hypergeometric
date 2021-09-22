/* hypergeometric.h
 * This header file contains the types and declarations for the
 * iteration state object and stepper.
 */

#ifndef HYPER_HEAD
#define HYPER_HEAD

typedef double real; // TODO real could be fixed point? not floating point
typedef unsigned int index;
typedef real (*function)(index n);

// because this is defined here in the header, pointers to hyper_state can be
// dereferenced and their contents are visible in any compilation unit that
// includes this header. hyper_state is a public struct

typedef struct {
    index n;
    real term;
    real total_F;
    function recur;
} hyper_state;

hyper_state hyper_construct(index initial_n, real first_term, function recur);

void hyper_step(hyper_state *iterator, real x);

#endif
