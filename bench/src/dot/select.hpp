#pragma once

#include "jpenuchot/select.hpp"
#include "openblas/select.hpp"

#undef BM_DOT
#define BM_DOT\
	BM_DOT_SIZE(2) \
	BM_DOT_SIZE(3) \
	BM_DOT_SIZE(4) \
	BM_DOT_SIZE(6) \
	BM_DOT_SIZE(8) \
	BM_DOT_SIZE(10) \
	BM_DOT_SIZE(16) \
	BM_DOT_SIZE(32) \
	BM_DOT_SIZE(100) \
	BM_DOT_SIZE(128) \
	BM_DOT_SIZE(512) \
	BM_DOT_SIZE(1000) \
	BM_DOT_SIZE(1024) \
	BM_DOT_SIZE(4096) \
	BM_DOT_SIZE(16384)

#undef BM_DOT_SIZE
#define BM_DOT_SIZE(size) \
	BM_DOT_JPENUCHOT(size) \
	BM_DOT_BLAS(size)
