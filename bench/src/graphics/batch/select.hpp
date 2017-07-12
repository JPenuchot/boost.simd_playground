#pragma once

#include "def.hpp"

#include <benchmark/benchmark.h>

#define BM_BATCH_SIZE(type, size) \
	BENCHMARK_TEMPLATE(batch__matvec4__simd, type, size); \
	BENCHMARK_TEMPLATE(batch__vecmat4__simd, type, size); \
	BENCHMARK_TEMPLATE(batch__matvec4__glm, type, size); \
	BENCHMARK_TEMPLATE(batch__vecmat4__glm, type, size);
	
	//BENCHMARK_TEMPLATE(batch__matvec4__dumb, type, size);
	//BENCHMARK_TEMPLATE(batch__vecmat4__dumb, type, size);

#define BM_BATCH(type) \
	BM_BATCH_SIZE(type, 1024) \
	BM_BATCH_SIZE(type, 4096) \
	BM_BATCH_SIZE(type, 16384) \
	BM_BATCH_SIZE(type, 65536)
	
	//BM_BATCH_SIZE(type, 262144)
	//BM_BATCH_SIZE(type, 1048576)
