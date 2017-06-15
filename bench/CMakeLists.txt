cmake_minimum_required(VERSION 2.8.9)
project(Bench)

#	Adding compiler optimizations

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 --std=c++14 -DNDEBUG")

#	Ckecking for packages

#find_package(GBenchmark REQUIRED)

#	Adding includes

include_directories("../boost_1_64_0/include" "../boost.simd/include" "benchmark/include" "../include")
link_directories("/usr/local/lib")

#	Linking libraries

#	Adding sources

file(GLOB_RECURSE SOURCES "src/*.cpp")

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

# Iterating over architectures
foreach(BARCH ${BENCH_ARCHS})
	# Iterating over types
	foreach(BTYPE ${BENCH_TYPES})
		
		set(TNAME "prog.${BARCH}_${BTYPE}")

		message("Building : ${TNAME}")

		add_executable(${TNAME} ${SOURCES})
		
		target_link_libraries(${TNAME} "benchmark" "pthread")

		set_target_properties(${TNAME}
			PROPERTIES COMPILE_FLAGS " -m${BARCH}  -DBENCH_TYPE=${BTYPE}")
	
	endforeach(BTYPE)
endforeach(ARCH)
