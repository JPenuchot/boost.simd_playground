/**
 * Enable/Disable benchmarks
 */

#pragma once

#include "def.hpp"

#define BM_VECMAT(type) \
	BENCHMARK_TEMPLATE(vecmat__vecmat4__dumb, type); \
	BENCHMARK_TEMPLATE(vecmat__vecmat4__simd, type); \
	BENCHMARK_TEMPLATE(vecmat__vecmat4__glm, type);