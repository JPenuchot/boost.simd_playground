# g++ src/main.cpp -O3 -Ibenchmark/include -L/usr/local/lib/ -lbenchmark -lpthread

cmake_minimum_required(VERSION 2.8.9)
project(Bench)

#	Adding compiler optimizations

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 --std=c++14 -DNDEBUG")

#	Ckecking for packages

#find_package(GBenchmark REQUIRED)

#	Adding includes

include_directories("../boost_1_64_0/include" "../boost.simd/include" "benchmark/include" "../include")

#	Linking libraries

link_directories("/usr/local/lib")
link_libraries("benchmark" "pthread")

#	Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(prog.avx_float ${SOURCES})
add_executable(prog.sse42_float ${SOURCES})
add_executable(prog.avx_double ${SOURCES})
add_executable(prog.sse4_2_double ${SOURCES})

SET_TARGET_PROPERTIES(prog.avx_float PROPERTIES
	COMPILE_FLAGS " -mavx  -DBENCH_TYPE=float")
SET_TARGET_PROPERTIES(prog.sse42_float PROPERTIES
	COMPILE_FLAGS " -msse4.2  -DBENCH_TYPE=float")
SET_TARGET_PROPERTIES(prog.avx_double PROPERTIES
	COMPILE_FLAGS " -mavx  -DBENCH_TYPE=double")
SET_TARGET_PROPERTIES(prog.sse4_2_double PROPERTIES
	COMPILE_FLAGS " -msse4.2  -DBENCH_TYPE=double")
