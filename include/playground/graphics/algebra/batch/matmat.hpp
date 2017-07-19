#pragma once

#include <iostream>

#ifdef FASMCMP
	#include <iacaMarks.h>
#endif

#include "../../types.hpp"
#include "../../helper/transpose.hpp"

namespace pg { namespace graphics {
	namespace bs = boost::simd;

	template <typename T>
	void batch_matmat4(mat4<T>& mat, T* src, std::size_t size, T* dest){
		auto& a_start = src;
		auto& b_start = dest;

		auto a_end = a_start + (16 * size);

		for(; a_start + 16 <= a_end; a_start++, b_start++){
			//	TODO
		}
	}

}	}