/**
 * Enable/Disable benchmarks
 */

#pragma once

#include "def.hpp"

#define BM_MATMAT(type) \
	BENCHMARK_TEMPLATE(matvec__matmat4__simd, type); \
	BENCHMARK_TEMPLATE(matvec__matmat4__glm, type);
	