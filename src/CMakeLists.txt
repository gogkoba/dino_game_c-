cmake_minimum_required(VERSION 3.10.0)

add_executable(proj_test test.cpp lib.cpp)
# ^ Взять test.cpp и lib.cpp, собрать вместе, назвать proj_test (proj_test.exe)
target_link_libraries(proj_test PUBLIC doctest::doctest default CONAN_PKG::raylib raylib-cpp)
# ^ Использовать в proj_test библиотеки doctest::doctest и default и raylib
doctest_discover_tests(proj_test)
# ^ Прочитать из proj_test список тестов

add_executable(proj main.cpp lib.cpp)
target_link_libraries(proj PUBLIC default CONAN_PKG::fmt CONAN_PKG::raylib raylib-cpp)
