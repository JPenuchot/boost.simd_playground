/**
 * Enable/Disable benchmarks
 */

#pragma once

#include "def.hpp"

#ifdef BENCH_DOUBLE
	using btype = double;
#else
	using btype = float;
#endif

#define BM_DOT_BLAS(size) \
	BENCHMARK_TEMPLATE(dot__pvector__openblas, float, size);
	