#pragma once

#include <iostream>

#ifdef FASMCMP
	#include <iacaMarks.h>
#endif

#include "../../types.hpp"
#include "../matmat.hpp"
#include "../../helper/transpose.hpp"

namespace pg { namespace graphics {
	namespace bs = boost::simd;

	template <typename T>
	void batch_matmat4(mat4<T>& mat, T* src, std::size_t size, T* dest){
		auto& a_start = src;
		auto& b_start = dest;

		auto a_end = a_start + (16 * size);

		for(; a_start + 32 <= a_end; a_start+=32, b_start+=32){
			mat4<T> m0(a_start);
			mat4<T> m1(&a_start[16]);

			mat4<T> m0d;
			mat4<T> m1d;

			mult4(mat, m0, m0d);
			mult4(mat, m1, m1d);

			bs::store(m0d, b_start);
			bs::store(m1d, &b_start[16]);
		}

		for(; a_start + 16 <= a_end; a_start+=16, b_start+=16){
			mat4<T> m0(a_start);
			mat4<T> m0d;
			mult4(mat, m0, m0d);
			bs::store(m0d, b_start);
		}
	}

}	}