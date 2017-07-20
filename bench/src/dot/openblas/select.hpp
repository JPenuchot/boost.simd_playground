/**
 * Enable/Disable benchmarks
 */

#pragma once

#include "def.hpp"

#define BM_DOT_OPENBLAS(type, size) \
	BENCHMARK_TEMPLATE(dot__pvector__openblas, type, size);
	