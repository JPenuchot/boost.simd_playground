cmake_minimum_required(VERSION 2.8.9)
project(Main)

#	Adding compiler optimizations

#SET(CMAKE_C_COMPILER /usr/bin/clang)
#SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14 -msse4.2")

#	Ckecking for packages

#find_package(GBenchmark REQUIRED)

#	Adding includes

include_directories(
	"include"
	"ext/boost_1_64_0"
	"ext/boost.simd/include"
	"ext/OpenBLAS/include"
)

#	Linking libraries

link_directories("ext/OpenBLAS/lib")
link_libraries("openblas")

#	Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(prog ${SOURCES})
