/**
 * Enable/Disable benchmarks
 */

#pragma once

#include "def.hpp"

#define BM_DOT_BLAS(size) \
	BM_DOT_PVECTOR_OPENBLAS(size)
	