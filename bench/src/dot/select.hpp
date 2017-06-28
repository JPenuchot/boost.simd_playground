#pragma once

#include "jpenuchot/select.hpp"
#include "openblas/select.hpp"

/*
 *	BENCHMARK SIZES
 *
 *	Benchmark sizes are tailored for a Xeon E5-2673 and are separated
 *	so the first block fits in the L1 cache, 2nd in the L2 cache, etc.
 *	
 *	* Xeon E5-2673 specs :
 *		
 *		- 2400		MHz
 *		
 *		- 32K		L1d
 *		- 256K		L2
 *		- 30720K	L3
 */

#ifdef BENCH_DOUBLE

	#define BM_DOT \
			BM_DOT_SIZE(2) \
			BM_DOT_SIZE(256) \
			BM_DOT_SIZE(1024) \
			\
			BM_DOT_SIZE(2048) \
			BM_DOT_SIZE(4096) \
			BM_DOT_SIZE(16384) \
			\
			BM_DOT_SIZE(262144) \
			BM_DOT_SIZE(983040) \
			BM_DOT_SIZE(1966080) \
			\
			BM_DOT_SIZE(16777216) \
			BM_DOT_SIZE(67108864) \
			BM_DOT_SIZE(268435456)

#else

	#define BM_DOT \
		BM_DOT_SIZE(2) \
		BM_DOT_SIZE(512) \
		BM_DOT_SIZE(2048) \
		\
		BM_DOT_SIZE(4096) \
		BM_DOT_SIZE(8196) \
		BM_DOT_SIZE(32768) \
		\
		BM_DOT_SIZE(524288) \
		BM_DOT_SIZE(1966080) \
		BM_DOT_SIZE(3932160) \
		\
		BM_DOT_SIZE(33554432) \
		BM_DOT_SIZE(134217728) \
		BM_DOT_SIZE(536870912)

#endif

#define BM_DOT_SIZE(size) \
	BM_DOT_JPENUCHOT(size) \
	BM_DOT_BLAS(size)
