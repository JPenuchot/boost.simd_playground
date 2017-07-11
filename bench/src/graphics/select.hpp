#pragma once

#include "matvec/select.hpp"
#include "vecmat/select.hpp"
#include "batch/select.hpp"

#define BM_GRAPHICS \
	BM_MATVEC(float) \
	BM_MATVEC(double) \
	BM_VECMAT(float) \
	BM_VECMAT(double)