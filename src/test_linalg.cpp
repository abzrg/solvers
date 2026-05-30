#include <print>
#include "linalg.hpp"
#include <iostream>
#include <complex>

void test_Vec()
{
    // Constructor (setting size)
    {
        Vec<int> v(5);
        assert(v.size() == 5);
    }

    // Constructor through initializer list
    {
        Vec<int> v{1,2,3};
        assert(v.at(1) == 2);
    }

    // Dot and Hadamard product
    {
        Vec<int> a{1,2,3};
        Vec<int> b{4,5,6};

        assert(a*b == 32);

        auto c = hadamard(a,b);
        assert(c.at(0) == 4);
        assert(c.at(1) == 10);
        assert(c.at(2) == 18);
    }

    // Complex support
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

    // Bounds safety test
    {
        Vec<int> v(3);

        try
        {
            v.at(100);
            assert(false);
        }
        catch (...)
        {}
    }
}

void test_Mat()
{
    // Identity matrix behavior
    {
        Mat<int> I(3,3,0);
        I[0, 0] = 1;
        I[1, 1] = 1;
        I[2, 2] = 1;

        Vec<int> v{1,2,3};
        auto Iv = I*v;

        assert(v.at(0) == Iv.at(0));
        assert(v.at(1) == Iv.at(1));
        assert(v.at(2) == Iv.at(2));
    }

    // Matrix multiplication sanity
    {
        Mat<int> A(2,2,1); // all ones
        Mat<int> B(2,2,1);

        auto C = A * B;

        assert(C.at(0,0) == 2);
        assert(C.at(0,1) == 2);
    }

    // Matrix-vector multiplication
    {
        Mat<int> A(2,2,1);
        Vec<int> v{1,2};

        auto r = A * v;

        assert(r.at(0) == 3);
        assert(r.at(1) == 3);
    }

    // Bounds safety test
    {
        Mat<int> m(2,2);

        try
        {
            m.at(100,0);
            assert(false);
        }
        catch (...)
        {}
    }
}

int main()
{
    test_Vec();
    test_Mat();
}
