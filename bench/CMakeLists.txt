cmake_minimum_required(VERSION 2.8.9)
project(Bench)

#	Adding compiler optimizations

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
	"int"
	"char"
)

set(BENCH_SIZES
	"10"
	"16"
	"32"
	"100"
	"128"
	"512"
	"1000"
	"1024"
	"4096"
	"16384"
	)

#	Ckecking for packages

#find_package(GBenchmark REQUIRED)

#	Adding includes

include_directories("../boost_1_64_0/include" "../boost.simd/include" "benchmark/include" "../include")
link_directories("/usr/local/lib")

#	Linking libraries

link_libraries("benchmark" "pthread")

#	Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Iterating over architectures
foreach(BARCH ${BENCH_ARCHS})
# Iterating over types
foreach(BTYPE ${BENCH_TYPES})
# Iterating over sizes
#foreach(BSIZE ${BENCH_SIZES})
		
	#set(TNAME "prog_${BARCH}_${BTYPE}_${BSIZE}")
	set(TNAME "prog_${BARCH}_${BTYPE}")
	add_executable(${TNAME} ${SOURCES})
	set_target_properties(${TNAME}
		#PROPERTIES COMPILE_FLAGS " -m${BARCH} -DBENCH_TYPE=${BTYPE} -DBENCH_SIZE=${BSIZE}")
		PROPERTIES COMPILE_FLAGS " -m${BARCH} -DBENCH_TYPE=${BTYPE}")

#endforeach(BSIZE)
endforeach(BTYPE)
endforeach(BARCH)
