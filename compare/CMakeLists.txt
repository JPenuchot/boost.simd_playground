cmake_minimum_required(VERSION 2.8.9)
project(Compare)

#	Adding compiler optimizations

SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14 -mavx")

#	Ckecking for packages

#find_package(GBenchmark REQUIRED)

#	Adding includes

include_directories("../ext/boost_1_64_0" "../ext/boost.simd/include" "../include")

#	Linking libraries

#link_libraries("/usr/local/lib/libbenchmark")

#	Adding sources

file(GLOB_RECURSE SOURCES1 "src1/*.cpp")
file(GLOB_RECURSE SOURCES2 "src2/*.cpp")

add_executable(prog1 ${SOURCES1})
add_executable(prog2 ${SOURCES2})
