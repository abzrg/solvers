add_library(base INTERFACE)
add_library(solvers::base ALIAS base)
target_compile_options(
    base
      INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wsign-conversion
        -Wconversion
        -Wshadow
        -Wfatal-errors
)

add_library(core INTERFACE)
add_library(solvers::core ALIAS core)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(core INTERFACE base)
target_sources(
    core
      INTERFACE
        concepts.hpp
        types.hpp
        core.hpp
)
