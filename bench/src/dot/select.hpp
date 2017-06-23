#pragma once

#include "jpenuchot/select.hpp"
#include "openblas/select.hpp"

#define BM_DOT \
	BM_DOT_SIZE(2) \
	BM_DOT_SIZE(32) \
	BM_DOT_SIZE(512) \
	BM_DOT_SIZE(2048) \
	BM_DOT_SIZE(32768) \
	BM_DOT_SIZE(524288) \
	BM_DOT_SIZE(2097152) \
	BM_DOT_SIZE(33554432) \
	BM_DOT_SIZE(536870912)

#define BM_DOT_SIZE(size) \
	BM_DOT_JPENUCHOT(size) \
	BM_DOT_BLAS(size)
