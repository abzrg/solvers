#pragma once

#include <complex>

#include "concepts.hpp"

/// Conjugation of complex and non-complex numbers. It returns the correct
/// type, not just complex number.
template<LinearAlgebraScalar U>
static constexpr U conjugate(const U& x)
{
    return x;
}

template<LinearAlgebraScalar U>
static constexpr std::complex<U> conjugate(const std::complex<U>& x)
{
    return std::conj(x);
}
