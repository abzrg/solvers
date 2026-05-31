#include "cg.hpp"

int main()
{
    Mat<double> A
    (
        2,
        2,
        {4,1,
         1,3}
    );

    Vec<double> b{1,2};

    auto x = conjugate_gradient(A,b);

    assert(std::abs(x[0] - 1.0/11.0) < 1e-8);
    assert(std::abs(x[1] - 7.0/11.0) < 1e-8);

    return 0;
}
