#include <benchmark/benchmark_api.h>

#include "jpenuchot/algebra/dot_select.hpp"
//#include "misc/containers.hpp"

#define BM_ALL(size) \
	BM_DOT(size)

BM_ALL(2)
BM_ALL(3)
BM_ALL(4)
BM_ALL(6)
BM_ALL(8)
BM_ALL(10)
BM_ALL(16)
BM_ALL(32)
BM_ALL(100)
BM_ALL(128)
BM_ALL(512)
BM_ALL(1000)
BM_ALL(1024)
BM_ALL(4096)
BM_ALL(16384)

BENCHMARK_MAIN();