/**
 * Enable/Disable benchmarks
 */

#pragma once

#include "def.hpp"

#define BM_DOT_PARRAY(type, size) \
	BENCHMARK_TEMPLATE(dot__parray__dumb, type, size); \
	BENCHMARK_TEMPLATE(dot__parray__simd, type, size); \
	BENCHMARK_TEMPLATE(dot__parray__simd_inner, type, size);
	
	//BM_DOT_PARRAY_SIMD_2U(size)
	//BM_DOT_PARRAY_SIMD_FU(size)
	//BM_DOT_PARRAY_SIMD_UNSAFE(size)

#define BM_DOT_PVECTOR(type, size) \
	BENCHMARK_TEMPLATE(dot__pvector__dumb, type, size); \
	BENCHMARK_TEMPLATE(dot__pvector__simd, type, size); \
	BENCHMARK_TEMPLATE(dot__pvector__simd_inner, type, size);
	

	//	Unusable until fixed
	
	//BM_DOT_PVECTOR_SIMD_VERSION(size, 1)
	//BM_DOT_PVECTOR_SIMD_VERSION(size, 2)

#define BM_DOT_JPENUCHOT(type, size) \
	BM_DOT_PVECTOR(type, size)
	//BM_DOT_PARRAY(type, size)
