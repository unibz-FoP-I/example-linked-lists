
add_executable(example_str example_str.c)
target_link_libraries(example_str PRIVATE LinkedLists Utf8)

add_executable(example_int example_int.c)
target_link_libraries(example_int PRIVATE LinkedLists)