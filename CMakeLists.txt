# see <https://cliutils.gitlab.io/modern-cmake/chapters/basics.html#minimum-version>
cmake_minimum_required(VERSION 3.7...3.25)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(example-linked-lists VERSION 0.1.0
            DESCRIPTION "Demonstrates the handling of Unicode strings in C")

# tells the compiler to generate most of the warnings
add_compile_options(-Wall -Wextra)

# requires the CTest module for unit testing
include(CTest)

# includes the definitions from the CMakeLists.txt files in the top level directories
add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(examples)
add_subdirectory(tests)