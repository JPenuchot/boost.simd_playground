#pragma once

#include "matvec/select.hpp"
#include "vecmat/select.hpp"
#include "batch/select.hpp"

#define BM_GRAPHICS \
	BM_BATCH(float)
	
	//BM_MATVEC(float)
	//BM_VECMAT(float)
	//BM_MATVEC(double)
	//BM_VECMAT(double)