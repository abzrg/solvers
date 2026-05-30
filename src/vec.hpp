#pragma once

#include <cassert>
#include <initializer_list>
#include <ostream>
#include <vector>

#include "types.hpp"
#include "concepts.hpp"
#include "complex.hpp"

/*
   Opeations

- [x] Vec + Vec
- [x] Vec - Vec
- [x] Vec += Vec
- [x] Vec -= Vec

- [x] Vec * scalar
- [x] scalar * Vec
- [x] Vec / scalar
- [x] Vec *= scalar
- [x] Vec /= scalar

- [x] dot(a,b)
- [x] inner(a,b)
- [x] hadamard(a,b)
- [x] norm(v)

*/


// ---


template<LinearAlgebraScalar S>
class Vec
{
public:
    Vec() = default;

    explicit Vec(ulabel sz)
    :
        elems_(sz)
    {}

    explicit Vec(ulabel sz, S initval)
    :
        elems_(sz, initval)
    {}

    // NOTE: initializer lists are usually passed by value because they are
    // basically lightweight proxy objects.
    Vec(std::initializer_list<S> initlist)
    :
        elems_{initlist}
    {}

    /// Element-wise (Hadamard) product
    Vec<S> hadamard(const Vec& other) const
    {
        assert(size() == other.size());

        Vec result(size());

        for (ulabel i = 0, sz = size(); i < sz; ++i)
        {
            result.at(i) = at(i)*other.at(i);
        }

        return result;
    }

    /// Inner product (Hermitian inner product)
    ///
    /// Over complex vector spaces, inner product usually means Hermitian inner
    /// product
    ///
    ///     ⟨x,y⟩ = Σ_i \bar{x}_i y_i
    ///
    S inner(const Vec<S>& other) const
    {
        assert(size() == other.size());

        S result{};

        for (ulabel i = 0; i < size(); ++i)
        {
            // NOTE: std::conj() promotes real numbers into complex numbers.
            // That's why we use the free function template `conjugate`.
            // It returns non-complex numbers as they are and via a
            // specialization returns complex conjugate of complex numbers.
            result += conjugate(at(i)) * other.at(i);
        }

        return result;
    }

    S operator*(const Vec& other) const
    {
        return inner(other);
    }

    /// Algebraic dot product: dot(a, b)
    ///
    /// Over real vector spaces, dot product is the same as inner product
    ///
    ///     ⟨x,y⟩ = Σ_i x_i y_i
    ///
    S dot(const Vec& other) const
    {
        assert(size() == other.size());

        S result{};

        for (ulabel i = 0, sz = size(); i < sz; ++i)
        {
            result += at(i)*other.at(i);
        }

        return result;
    }

    Vec operator+(const Vec& other) const
    {
        assert(size() == other.size());

        Vec result(size());

        for (ulabel i = 0; i < size(); ++i)
        {
            result.at(i) = at(i) + other.at(i);
        }

        return result;
    }

    Vec& operator+=(const Vec& other)
    {
        assert(size() == other.size());

        for (ulabel i = 0; i < size(); ++i)
        {
            at(i) += other.at(i);
        }

        return *this;
    }

    Vec operator-(const Vec& other) const
    {
        assert(size() == other.size());

        Vec result(size());

        for (ulabel i = 0; i < size(); ++i)
        {
            result.at(i) = at(i) - other.at(i);
        }

        return result;
    }

    Vec& operator-=(const Vec& other)
    {
        assert(size() == other.size());

        for (ulabel i = 0; i < size(); ++i)
        {
            at(i) -= other.at(i);
        }

        return *this;
    }

    /// Scalar multiplication
    Vec operator*(const S& alpha) const
    {
        Vec result(size());

        for (ulabel i = 0; i < size(); ++i)
        {
            result.at(i) = at(i) * alpha;
        }

        return result;
    }

    // Does not make sense
    auto operator*=(const Vec&) = delete;

    Vec& operator*=(const S& alpha)
    {
        for (ulabel i = 0; i < size(); ++i)
        {
            at(i) *= alpha;
        }

        return *this;
    }

    // Does not make sense
    auto operator/(const Vec&) const = delete;

    // Scalar division
    Vec operator/(const S& alpha) const
    {
        auto inv = S{1}/alpha;
        return *this*inv;
    }

    Vec& operator/=(const S& alpha)
    {
        for (ulabel i = 0; i < size(); ++i)
        {
            at(i) /= alpha;
        }

        return *this;
    }

    // TODO? (only intended to be used for integers)
    bool operator==(const Vec&) const = default;

    // L-2 norm
    auto norm() const
    {
        using std::sqrt;
        using std::abs;

        return sqrt(abs(inner(*this, *this)));
    }

    inline const S& at(ulabel index) const
    {
        checkindex(index);
        return elems_.at(index);
    }

    inline S& at(ulabel index)
    {
        checkindex(index);
        return elems_.at(index);
    }

    S& operator[](ulabel index)
    {
        return elems_[index];
    }

    const S& operator[](ulabel index) const
    {
        return elems_[index];
    }

    inline const std::vector<S>& elems() const noexcept
    {
        return elems_;
    }

    inline ulabel size() const noexcept
    {
        return elems_.size();
    }

    inline void checkindex(ulabel index) const noexcept
    {
        assert(index < elems_.size());
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec& vec);

private:
    std::vector<S> elems_{};
};


// ---


template<FloatingLinearAlgebraScalar FS>
bool approx_equal
(
    const Vec<FS>& vec,
    const Vec<FS>& other,
    double rel_tol = 1e-9,
    double abs_tol = 1e-12)
{
    assert(vec.size() == other.size());

    for (ulabel i = 0, sz = vec.size(); i < sz; ++i)
    {
        auto diff  = std::abs(vec.at(i) - other.at(i));
        auto scale = std::max(std::abs(vec.at(i)), std::abs(other.at(i)));
        if (diff > abs_tol + rel_tol*scale)
            return false;
    }

    return true;
}

template<LinearAlgebraScalar S>
S dot(const Vec<S>& vec, const Vec<S>& other)
{
    assert(vec.size() == other.size());

    S result{};

    for (ulabel i = 0, sz = vec.size(); i < sz; ++i)
    {
        result += vec.at(i)*other.at(i);
    }

    return result;
}

template<LinearAlgebraScalar S>
S inner(const Vec<S>& vec, const Vec<S>& other)
{
    return vec.inner(other);
}

template<LinearAlgebraScalar S>
auto norm(const Vec<S>& vec)
{
    return vec.norm();
}

template<LinearAlgebraScalar S>
Vec<S> hadamard(const Vec<S>& vec, const Vec<S>& other)
{
    return vec.hadamard(other);
}

template<LinearAlgebraScalar S>
Vec<S> operator*(const S& alpha, const Vec<S>& vec)
{
    return vec*alpha;
}

// Does not make sense
// template<LinearAlgebraScalar T>
// Vec<T> operator/(const T& alpha, const Vec<T>& vec)
// {
//     return vec/alpha;
// }

template<LinearAlgebraScalar S>
std::ostream& operator<<(std::ostream& os, const Vec<S>& vec)
{
    os << "[";

    if (vec.size() == 0)
    {
        os << "]";
        return os;
    }

    for (size_t i = 0; i < vec.size() - 1; i++)
    {
        os << vec.at(i) << ", ";
    }

    os << vec.at(vec.size() - 1)
       << "]";

    return os;
}
