add_library(vec INTERFACE)
add_library(solvers::vec ALIAS vec)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(vec INTERFACE core complex)
target_sources(
    core
      INTERFACE
        vec.hpp
)


add_library(mat INTERFACE)
add_library(solvers::mat ALIAS mat)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mat INTERFACE core vec)
target_sources(
    core
      INTERFACE
        mat.hpp
)


add_library(linalg INTERFACE)
add_library(solvers::linalg ALIAS linalg)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(linalg INTERFACE vec mat)
target_sources(
    core
      INTERFACE
        linalg.hpp
)
