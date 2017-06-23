/**
 * Enable/Disable benchmarks
 */

#pragma once

#include "def.hpp"


#undef BM_DOT_PARRAY
#define BM_DOT_PARRAY(size) \
	BM_DOT_PARRAY_SIMD(size) \
	BM_DOT_PARRAY_SIMD_INNER(size) \
	BM_DOT_PARRAY_DUMB(size)
	//BM_DOT_PARRAY_SIMD_2U(size)
	//BM_DOT_PARRAY_SIMD_FU(size)
	//BM_DOT_PARRAY_SIMD_UNSAFE(size)

#undef BM_DOT_PVECTOR
#define BM_DOT_PVECTOR(size) \
	BM_DOT_PVECTOR_SIMD(size) \
	BM_DOT_PVECTOR_SIMD_INNER(size) \
	BM_DOT_PVECTOR_DUMB(size)

#undef BM_DOT_JPENUCHOT
#define BM_DOT_JPENUCHOT(size) \
	BM_DOT_PARRAY(size) \
	BM_DOT_PVECTOR(size)
