/**
 * Enable/Disable benchmarks
 */

#pragma once

#include "def.hpp"

#define BM_DOT_MKL(type, size) \
	BENCHMARK_TEMPLATE(dot__pvector__mkl, type, size);
	