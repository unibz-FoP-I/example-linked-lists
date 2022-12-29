# Linked lists example

This repository demonstrate the used of dynamic memory allocation to define a general purpose linked list data structure. The type of the objects stored on the list is not specified and the same code can be used for different types. In the directory [examples](examples/) there are two different implementations, for list of strings and integers.

Other purposes of the repository is to show a possible project organisation, a more advanced use of [CMake](https://cmake.org/), and basic unit testing.

## Compilation and usage

### Requirements

The project is self contained but for compilation it requires a C compiler and a recent version of CMake (>= 3.7).

### Building the executables

It's recommended to perform an *out-of-source* build in a separate subdirectory. In the following will be using the directory `build` within the root of the repository.

The following command checks the environment and creates the build configuration:

``` bash
cmake -B build
```

To generate the executables the command should be:

`` bash
cmake --build build
```

The compilation process generates the following executables within the `./build/` directory:

- `examples/example_int`: reads a sequence of integers from `stdin` (an integer per line) into a list, and writes a JSON formatted document to `stdout` with the content of the list.
- `examples/example_str`: as the previous one but for Unicode strings.
- `build/tests/test_lnkd_lists`: run the unit tests.

### Unit tests

Tests can be run using the `ctest` command (shipped with CMake). The configuration for the tests is in the `build` directory, and they can be run using the command:

``` bash
ctest --test-dir build
```

### Cleanup

Every file generated by the configuration or compilation process is in the `build` directory. To clean everything it is sufficient to delete that directory.

## Project organisation

The source code is organised in the following top level directories:

- [src](src/): the code for the linked list data type.
- [examples](examples/): code to demonstrate how to use the generic linked list for specific types.
- [tests](tests/): code for the unit testing.
- [external](external/): external libraries used by the project.

CMake configuration is split among several `CMakeLists.txt` files in the different directories. The main [CMakeLists.txt](CMakeLists.txt) file, in the root of the repository, defines the main metadata for the project and includes the target definitions from the top level directories.

## External libraries

The project uses the following external libraries:

- [ThrowTheSwitch/Unity: Simple Unit Testing for C](https://github.com/ThrowTheSwitch/Unity)
- [sheredom/utf8.h: 📚 single header utf8 string functions for C and C++](https://github.com/sheredom/utf8.h)

## Examples

In the [examples](examples/) directory there are two programs that demonstrate how to use the library defined in [src][src/] to create lists of integers or strings. Both programs expect the sequence of items to be entered from the standard input with each element in a separate line.

### List of integers

The code is in a single file [examples/example_int.c](examples/example_int.c).

To create a list of integers from the command line the [shuf](https://explainshell.com/explain/1/shuf) command is available on most of the Linux distributions. The example code can be run as:

```bash
$ shuf -i 0-100 -n 10 | ./build/examples/example_int 
[15, 25, 26, 54, 63, 71, 72, 77, 82, 90]
```

### List of strings

The code is in a single file [examples/example_int.c](examples/example_str.c).

Most of the Unix systems (including Linux and OSX) include a file with a list of english words in [/usr/share/dict/words](https://en.wikipedia.org/wiki/Words_%28Unix%29). The `shuf` utility can be used to select a random number of words from it.

```bash
$ shuf -n 10 /usr/share/dict/words | ./build/examples/example_str 
["Platonesque", "atramental", "caltrop", "cuneator", "fittable", "formicide", "nonstimulant", "rizzonite", "signify", "spirillaceous"]
```

## Licence

The project is released under the [MIT License](https://choosealicense.com/licenses/mit/).