cmake_minimum_required(VERSION 4.0)

project(
    solvers
      LANGUAGES    CXX
      HOMEPAGE_URL "https://github.com/abzrg/solvers"
      DESCRIPTION  "Implementations of linear and nonlinear solvers (C++23)"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE "Debug")

add_subdirectory(src)
add_subdirectory(solvers)
enable_testing()
add_subdirectory(tests)
