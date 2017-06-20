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
	#"sse4.2"
)

#	List of float typesw
set(BENCH_TYPES
	"float"
	#"double"
	#"int"
	#"char"
)

#	Ckecking for packages

#find_package(GBenchmark REQUIRED)

#	Adding includes

include_directories("../boost_1_64_0" "../boost.simd/include" "benchmark/include" "../include")
link_directories("/usr/local/lib")

#	Linking libraries

link_libraries("benchmark" "pthread")

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
