#pragma once

#include <concepts>
#include <complex>

// This concept includes integers, Floating point numbers, and complex numbers
//
// note: some arithmetic expressions involving references/value categories may
// fail exact same_as<T> constraints. Also some user-defined numeric types
// return proxy objects. TODO: TEST
template<typename T>
concept LinearAlgebraScalar =
requires(T a, T b)
{
    { T{} };

    // Assignability
    { a + b } -> std::same_as<T>;
    { a - b } -> std::same_as<T>;
    { a * b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;

    // Accumulation behavior
    { a += b } -> std::same_as<T&>;
    { a -= b } -> std::same_as<T&>;
    { a *= b } -> std::same_as<T&>;
};

#if 0
#include <concepts>

template<typename T>
concept LinearAlgebraScalar =
requires(T a, T b)
{
    T{};

    a + b;
    a - b;
    a * b;
    a / b;

    a += b;
    a -= b;
    a *= b;
};
#endif

template<typename T>
struct is_complex : std::false_type {};

template<typename T>
struct is_complex<std::complex<T>> : std::true_type {};

template<typename T>
concept FloatingLinearAlgebraScalar =
    (std::floating_point<T> ||
     (is_complex<T>::value &&
      std::floating_point<typename T::value_type>))
    &&
    LinearAlgebraScalar<T>;
