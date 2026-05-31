add_executable(test_cg test_cg.cpp)
target_link_libraries(test_cg PRIVATE solvers::cg)
add_test(
  NAME test_cg
  COMMAND test_cg
)
set_property(
    TEST test_cg
    PROPERTY LABELS "solvers"
)
