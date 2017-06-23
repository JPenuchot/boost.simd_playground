cmake_minimum_required(VERSION 2.8.9)
project(Bench)

#	Adding compiler optimizations

#SET(CMAKE_C_COMPILER /usr/bin/clang)
#SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 --std=c++14 -DNDEBUG")

## Preparing build for multiple architectures and numeric types

#	List of SIMD architectures
set(BENCH_ARCHS
	"avx"
	"sse4.2"
)

#	List of float typesw
set(BENCH_TYPES
	"float"
	"double"
)

#	Adding includes

<<<<<<< HEAD
include_directories(
	"../ext/boost_1_64_0"
	"../ext/boost.simd/include"
	"../ext/benchmark/include"
	"../ext/OpenBLAS/include"
	"../include" 
)
=======
include_directories("../ext/boost_1_64_0" "../ext/boost.simd/include" "ext/benchmark/include" "../include" OpenBLAS_INCLUDE_DIR)
link_directories("/usr/local/lib" OpenBLAS_LIB)

>>>>>>> d83c6a44c9dc024df7da095ce5c12d7797898b9c

#	Linking libraries

link_directories(
	"/usr/local/lib"
	"../ext/OpenBLAS/lib"
)
link_libraries(
	"benchmark"
	"pthread"
	"openblas"
)

#	Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Iterating over architectures
foreach(BARCH ${BENCH_ARCHS})
# Iterating over types
foreach(BTYPE ${BENCH_TYPES})

	set(TNAME "bench_${BARCH}_${BTYPE}")
	add_executable(${TNAME} ${SOURCES})
	set_target_properties(${TNAME}
		PROPERTIES COMPILE_FLAGS " -m${BARCH} -DBENCH_TYPE=${BTYPE}")

endforeach(BTYPE)
endforeach(BARCH)
