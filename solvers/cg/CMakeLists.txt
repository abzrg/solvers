add_library(cg INTERFACE)
add_library(solvers::cg ALIAS cg)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cg INTERFACE core)
target_sources(
    core
      INTERFACE
        cg.hpp
)
