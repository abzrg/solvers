#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#include "types.hpp"
#include "concepts.hpp"


// TODO:
// - iterators
// - begin()/end()
// - scalar multiplication
// - addition/subtraction
// - move constructors
// - transpose
// - identity matrix
// - bounds-safe row access
// - storage order documentation
// - constexpr/noexcept where appropriate

/// DESIGN:
/// - template-based design
/// - row-major flattened indexing
/// - dynamic-size matrices/vectors (use of std::vector)
/// - bounds-checked access through at()
/// - unchecked access through operator[]

/// It is hoped that it supports:
/// - integers
/// - complex numbers
/// - custom numeric types
/// - fixed-point arithmetic


// Forward Declaration
template<LinearAlgebraScalar S>
class Vec;


template<LinearAlgebraScalar S>
class Mat
{
public:
    Mat() = default;

    /// Rectangular matrix
    ///
    /// Note: if a contructor allocates memory it may throw std::throw;
    /// incorrect `noexcept` can trigger std::terminate.
    Mat(ulabel rows, ulabel cols) // noexcept ✗
    :
        rows_{rows},
        cols_{cols},
        elems_(rows*cols)
    {}

    /// Square matrix
    explicit Mat(ulabel rows)
    :
        Mat(rows, rows)
    {}

    /// Scalar matrix
    Mat(ulabel rows, ulabel cols, const S& initval)
    :
        rows_{rows},
        cols_{cols},
        elems_(rows*cols, initval)
    {}

    Mat(std::initializer_list<S> initlist, ulabel rows, ulabel cols)
    :
        rows_{rows},
        cols_{cols},
        elems_(initlist)
    {
        assert(rows*cols == initlist.size());
    }

    Mat(const std::vector<S>& initvec, ulabel rows, ulabel cols)
    :
        rows_{rows},
        cols_{cols},
        elems_(initvec)
    {
        assert(rows*cols == initvec.size());
    }

    Mat(const Vec<S>& initvec, ulabel rows, ulabel cols) noexcept
    :
        Mat(initvec.elems(), rows, cols)
    {}

    /// Matrix-Matrix multiplication
    Mat operator*(const Mat& other) const
    {
        assert(cols_ == other.rows_);

        Mat res{rows_, other.cols_, S{}};

        for (ulabel i = 0; i < rows_; ++i)
        {
            for (ulabel k = 0; k < cols_; ++k)
            {
                for (ulabel j = 0; j < other.cols_; ++j)
                {
                    res.at(i, j) += at(i, k)*other.at(k, j);
                }
            }
        }

        return res;
    }

    /// Matrix-vector multiplication
    Vec<S> operator*(const Vec<S>& v) const
    {
        assert(cols_ == v.size());

        Vec<S> res(rows_);

        for (ulabel i = 0; i < rows_; ++i)
        {
            auto& r = res.at(i);
            r = S{};

            for (ulabel j = 0; j < cols_; ++j)
            {
                r += at(i, j)*v.at(j);
            }
        }

        return res;
    }

    S& operator[](ulabel row, ulabel col)
    {
        return elems_[index(row, col)];
    }

    const S& operator[](ulabel row, ulabel col) const
    {
        return elems_[index(row, col)];
    }

    S& at(ulabel row, ulabel col)
    {
        // NOTE: std::vector::at() checks the flattened index. But
        // semantically, row/column should also be validated explicitly.
        checkrowindex(row);
        checkcolindex(col);

        return elems_.at(index(row, col));
    }

    const S& at(ulabel row, ulabel col) const
    {
        checkrowindex(row);
        checkcolindex(col);
        return elems_.at(index(row, col));
    }

    inline ulabel rows() const noexcept { return rows_; }

    inline ulabel cols() const noexcept { return cols_; }

    inline ulabel size() const noexcept { return rows_*cols_; }

    inline bool empty() const noexcept { return size() == 0; }

    // Note: a row index cannot be negative.
    inline void checkrowindex(ulabel rowindex) const noexcept
    {
        assert(rowindex < rows_);
    }

    // Note: a column index cannot be negative.
    inline void checkcolindex(ulabel colindex) const noexcept
    {
        assert(colindex < cols_);
    }

private:

    /// Indexing logic
    ///
    /// Later, if we support:
    /// - column-major
    /// - blocked/tiled storage
    /// - Morton order
    /// - SIMD layouts
    /// we only change indexing logic.
    ulabel index(ulabel row, ulabel col) const noexcept
    {
        return row * cols_ + col;
    }

private:

    ulabel rows_{};
    ulabel cols_{};
    std::vector<S> elems_{};
};
