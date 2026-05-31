#include <print>
#include "linalg.hpp"
#include "vec.hpp"
#include <iostream>
#include <complex>

int test_ctor_set_size()
{
    Vec<int> v(5);
    return v.size() == 5;
}

int test_ctor_initlist()
{
    Vec<int> v{1,2,3};
    return v.at(1) == 2;
}

int test_dot()
{
    return dot(Vec{1, 2, 3}, Vec{4, 5, 6}) == 32;
}

int test_hadamard()
{
    return hadamard(Vec{1, 2, 3}, Vec{4, 5, 6}) == Vec{4, 10, 18};
}

int test_inner()
{
    Vec<int> a{1,2,3};
    Vec<int> b{4,5,6};

}

int test_access_boundcheck()
{
    Vec<int> v(3);

    try
    {
        v.at(100);
        assert(false);
    }
    catch (...)
    {
        return 1;
    }

    return 0;
}

int test_complex_numbers()
{
    using cplx = std::complex<double>;

    Vec<cplx> a{{1,2},{3,4}};
    Vec<cplx> b{{5,6},{7,8}};

    [[maybe_unused]] auto d = a*b;
    // std::println("{}", d);
    // python -c 'print((1+2j)*(5+6j) + (3+4j)*(7+8j))'
    std::cout << d << std::endl;

    auto inr1 = inner(a,b);
    auto inr2 = std::conj(a.at(0))*b.at(0) + std::conj(a.at(1))*b.at(1);
    std::cout << inr1 << std::endl;  // (70,-8)
    std::cout << inr2 << std::endl;
}

int main()
{
    // Complex support

    // Bounds safety test
    {
    }
}
