add_library(complex INTERFACE)
add_library(solvers::complex ALIAS complex)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(complex INTERFACE core)
target_sources(
    core
      INTERFACE
        complex.hpp
)
