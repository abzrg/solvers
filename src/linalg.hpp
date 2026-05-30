#pragma once

// C++ Stuff:
//
// - value semantics
// - contiguous storage
// - explicit indexing policy
// - modern concepts
// - const correctness
// - cache-aware multiplication
// - reasonable ownership model
// - mathematically aware API naming
// - no obvious UB
// - good initialization discipline


// Further advanced stuff
// - [x] concepts
// - [ ] storage policy
// - [ ] expression templates
// - [?] SIMD support
// - [?] ownership semantics
// - [?] compile-time dimensions
// - [ ] allocator support
// - [ ] sparse matrices
// - [ ] interoperability with BLAS/LAPACK



#include <algorithm>
#include <array>
#include <cassert>
#include <initializer_list>
#include <ostream>
#include <ranges>
#include <vector>
#include <complex>

#include "concepts.hpp"
#include "types.hpp"
#include "vec.hpp"
#include "mat.hpp"
