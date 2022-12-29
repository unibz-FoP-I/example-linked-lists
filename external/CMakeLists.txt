
# [ThrowTheSwitch/Unity: Simple Unit Testing for C](https://github.com/ThrowTheSwitch/Unity/tree/v2.5.2)
add_library(Unity STATIC unity/unity.c)
target_include_directories(Unity PUBLIC unity)

# [sheredom/utf8.h: 📚 single header utf8 string functions for C and C++](https://github.com/sheredom/utf8.h/tree/4e4d828174c35e4564c31a9e35580c299c69a063)
add_library(Utf8 INTERFACE)
target_include_directories(Utf8 INTERFACE utf8)
