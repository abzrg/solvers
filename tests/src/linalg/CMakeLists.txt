add_executable(test_vec test_vec.cpp)
target_link_libraries(test_vec PRIVATE solvers::linalg)
add_test(
    NAME test_vec
    COMMAND test_vec
)
set_property(
    TEST test_vec
    PROPERTY LABELS "linalg"
)

add_executable(test_mat test_mat.cpp)
target_link_libraries(test_mat PRIVATE solvers::linalg)
add_test(
  NAME test_mat
  COMMAND test_mat
)
set_property(
    TEST test_mat
    PROPERTY LABELS "linalg"
)
