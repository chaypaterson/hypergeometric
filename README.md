# hypergeometric

A reasonably efficient iterative calculator of hypergeometric series.

This is a C project that demonstrates how the (n+1)th term of a hypergeometric
series can be computed in O(1) time given n and the previous term. This is
better than a naive implementation which could be O(n).

A hypergeometric series

     F(x) = \sum_n a_n x^n

is one for which successive coefficients are a rational function of n:

     a_{n+1} / a_n = A(n) / B(n)

where A and B are polynomials.

This suggests an efficient way to calculate them. In a struct:

    Store the value of the most recent term, a_n * x.
    Store the total accumulated value of the series so far, total_F.
    Store n.
    For convenience, store a pointer to A(n)/B(n), the recurrence relation.

To get the next term, calculate

     term *= x * A(n) / B(n)
     total_f += term
     n++

We can put this iteration step in either a for or a while loop.

This iteration requires a constant number of operations to compute the n-th
term. This is much better than a naive implementation of Taylor series, which
might require n+1 multiplications to calculate a_n * x^n.
 
