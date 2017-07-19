#pragma once

#include <iostream>

#ifdef FASMCMP
	#include <iacaMarks.h>
#endif

#include "../../types.hpp"
#include "../vecmat.hpp"
#include "../matvec.hpp"
#include "../../helper/transpose.hpp"

namespace pg { namespace graphics {
	namespace bs = boost::simd;

	template <typename T>
	BOOST_FORCEINLINE void batch3(mat3<T>& mat, T* src, std::size_t size, T* dest){
		//	TODO
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
	BOOST_FORCEINLINE void batch_matvec4(mat4<T>& mat, T* src, std::size_t size, T* dest){
		auto& a_start = src;
		auto& b_start = dest;

		auto a_end = a_start + (4 * size);

		vec4<T> res0;
		vec4<T> res1;
		vec4<T> res2;
		vec4<T> res3;

		//	Split split split split...
		auto mat_split1 = bs::slice(mat);
		auto mat_split2_0 = bs::slice(mat_split1[0]);
		auto mat_split2_1 = bs::slice(mat_split1[1]);

		auto c0 = mat_split2_0[0];
		auto c1 = mat_split2_0[1];
		auto c2 = mat_split2_1[0];
		auto c3 = mat_split2_1[1];

		//	Goin' fast
		for(;a_start + 16 <= a_end; a_start += 16, b_start += 16){
			#ifdef FASMCMP
				IACA_START
			#endif

			vec4<T> vec0(a_start);
			vec4<T> vec1(&a_start[4]);
			vec4<T> vec2(&a_start[8]);
			vec4<T> vec3(&a_start[12]);

			auto res0 = (c0 * vec0[0]) + (c1 * vec0[1]) + (c2 * vec0[2]) + (c3 * vec0[3]);
			auto res1 = (c0 * vec1[0]) + (c1 * vec1[1]) + (c2 * vec1[2]) + (c3 * vec1[3]);
			auto res2 = (c0 * vec2[0]) + (c1 * vec2[1]) + (c2 * vec2[2]) + (c3 * vec2[3]);
			auto res3 = (c0 * vec3[0]) + (c1 * vec3[1]) + (c2 * vec3[2]) + (c3 * vec3[3]);

			bs::store(res0, b_start);
			bs::store(res1, &b_start[4]);
			bs::store(res2, &b_start[8]);
			bs::store(res3, &b_start[12]);

		}

		#ifdef FASMCMP
			IACA_END
		#endif

		for(;a_start + 4 <= a_end; a_start += 4, b_start += 4){
			mult4(mat, vec4<T>(a_start), res0);
			bs::store(res0, b_start);
		}
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
	BOOST_FORCEINLINE void batch_vecmat4_(mat4<T>& mat, T* src, std::size_t size, T* dest){
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
			mult4(mat, vec4<T>(a_start), res0);
			bs::store(res0, b_start);
		}
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
		mat4<T> matt;
		pg::graphics::transpose4(mat, matt);
		batch_matvec4(matt, src, size, dest);
	}

}	}
