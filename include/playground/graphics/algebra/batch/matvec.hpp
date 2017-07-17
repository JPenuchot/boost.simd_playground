#pragma once

#include <iostream>

#ifdef FASMCMP
	#include <iacaMarks.h>
#endif

#include "../../types.hpp"
#include "../vecmat.hpp"
#include "../../helper/transpose.hpp"

namespace pg { namespace graphics {
	namespace bs = boost::simd;

	template <typename T>
	BOOST_FORCEINLINE void batch3(mat3<T>& mat, vec3<T>* src, std::size_t size, T* dest){
		//	TODO
	}

	/**
	 * @brief      Vector * Matrix product batch
	 *
	 * @param      mat   The matrix
	 * @param      src   The source
	 * @param[in]  size  The size
	 * @param      dest  The destination
	 *
	 * @tparam     T     Type
	 */
	template <typename T>
	BOOST_FORCEINLINE void batch_vecmat4(mat4<T>& mat, T* src, std::size_t size, T* dest){
		auto& a_start = src;
		auto& b_start = dest;

		auto a_end = a_start + (4 * size);

		vec4<T> res0;
		vec4<T> res1;
		vec4<T> res2;
		vec4<T> res3;

		//	Goin' fast
		for(;a_start + 16 <= a_end; a_start += 16, b_start += 16){
			#ifdef FASMCMP
				IACA_START
			#endif

			mult4(vec4<T>(a_start), mat, res0);
			mult4(vec4<T>(&a_start[4]), mat, res1);
			mult4(vec4<T>(&a_start[8]), mat, res2);
			mult4(vec4<T>(&a_start[12]), mat, res3);

			bs::store(res0, b_start);
			bs::store(res1, &b_start[4]);
			bs::store(res2, &b_start[8]);
			bs::store(res3, &b_start[12]);

		}

		#ifdef FASMCMP
			IACA_END
		#endif

		for(;a_start + 4 <= a_end; a_start += 4, b_start += 4){
			mult4(vec4<T>(a_start), mat, res0);
			bs::store(res0, b_start);
		}
	}

	/**
	 * @brief      Matrix * Vector product batch
	 *
	 * @param      mat_  The matrix
	 * @param      src   The source
	 * @param[in]  size  The size
	 * @param      dest  The destination
	 *
	 * @tparam     T     Type
	 */
	template <typename T>
	BOOST_FORCEINLINE void batch_matvec4(mat4<T>& mat_, T* src, std::size_t size, T* dest){
		mat4<T> mat;
		transpose4(mat_, mat);
		batch_vecmat4(mat, src, size, dest);
	}

}	}
