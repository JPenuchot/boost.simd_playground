/**
 * Enable/Disable benchmarks
 */

#pragma once

#include "def.hpp"

#define BM_MATVEC(type) \
	BENCHMARK_TEMPLATE(matvec__matvec4__dumb, type); \
	BENCHMARK_TEMPLATE(matvec__matvec4__simd, type); \
	BENCHMARK_TEMPLATE(matvec__matvec4__glm, type);