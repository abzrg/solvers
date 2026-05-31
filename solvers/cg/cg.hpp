#pragma once

#include "linalg.hpp"

/// Conjugate Gradient Solver
///
/// Solves:
///     A x = b
///
/// Requirements:
///     - A symmetric positive definite (real)
///     - A Hermitian positive definite (complex)
///
/// Complexity:
///     O(k * nnz(A))
///
/// where k is the iteration count.
template<FloatingLinearAlgebraScalar S>
Vec<S> conjugate_gradient
(
    const Mat<S>& A,
    const Vec<S>& b,
    ulabel max_iters = 1000,
    S tolerance = S{1e-10})
{
    Vec<S> x(b.size());

    Vec<S> r = b - A * x;
    Vec<S> p = r;

    S rsold = r*r;

    for (ulabel i = 0; i < max_iters; ++i)
    {
        Vec<S> Ap = A * p;

        S alpha = rsold / (p*Ap);

        x += alpha * p;

        r -= alpha * Ap;

        S rsnew = r*r;

        if (std::sqrt(std::abs(rsnew)) < tolerance)
        {
            break;
        }

        p = r + (rsnew / rsold) * p;

        rsold = rsnew;
    }

    return x;
}
