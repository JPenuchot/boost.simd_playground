#include <benchmark/benchmark_api.h>

#include "dot/select.hpp"
//#include "misc/containers.hpp"

#define BM_ALL \
	BM_DOT

BM_ALL

BENCHMARK_MAIN();