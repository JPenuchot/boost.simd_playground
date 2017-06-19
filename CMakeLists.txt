cmake_minimum_required(VERSION 2.8.9)
project(ProjName)

#	Adding compiler optimizations

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14 -msse4.2")

#	Ckecking for packages

#find_package(GBenchmark REQUIRED)

#	Adding includes

include_directories("boost_1_64_0" "boost.simd/include" "include")

#	Linking libraries

#link_libraries("/usr/local/lib/libbenchmark")

#	Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(prog ${SOURCES})
