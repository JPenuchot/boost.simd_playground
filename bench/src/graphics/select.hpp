#pragma once

#include "matvec/select.hpp"
#include "vecmat/select.hpp"
#include "batch/select.hpp"
#include "matmat/select.hpp"

#define BM_GRAPHICS \
	BM_MATMAT(float) \
	BM_MATVEC(float) \
	BM_VECMAT(float) \
	BM_BATCH(float)
	
	//BM_MATVEC(double)
	//BM_VECMAT(double)