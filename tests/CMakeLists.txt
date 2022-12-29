
add_executable(test_lnkd_lists test_lnkd_lists.c)

target_link_libraries(test_lnkd_lists PRIVATE LinkedLists Unity)

add_test(NAME lnkd_test COMMAND test_lnkd_lists)