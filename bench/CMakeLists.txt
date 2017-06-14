# g++ src/main.cpp -O3 -Ibenchmark/include -L/usr/local/lib/ -lbenchmark -lpthread

cmake_minimum_required(VERSION 2.8.9)
project(Bench)

#	Adding compiler optimizations

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 --std=c++14 -msse4.2")

#	Ckecking for packages

#find_package(GBenchmark REQUIRED)

#	Adding includes

include_directories("../boost_1_64_0/include" "../boost.simd/include" "benchmark/include")

#	Linking libraries

link_directories("/usr/local/lib")
link_libraries("benchmark" "pthread")

#	Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(prog ${SOURCES})
