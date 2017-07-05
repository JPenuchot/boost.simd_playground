#pragma once

#include <iostream>

#include <boost/simd/pack.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/reduction.hpp>

#include "../types.hpp"

namespace pg { namespace graphics {
	namespace bs = boost::simd;
	
	/**
	 * @brief      Row-major version of the dot product.
	 *
	 * @param[in]  mat   The matrix
	 * @param[in]  src   The source
	 * @param      dest  The destination
	 *
	 * @tparam     T     Scalar type
	 */
	template <typename T>
	inline void matvec_r(const mat4<T>& mat, const vec4<T>& src, vec4<T>& dest){
		//	Split split split split...
		auto split1 = bs::slice(mat);
		auto split2_0 = bs::slice(split1[0]);
		auto split2_1 = bs::slice(split1[1]);

		auto mat0 = split2_0[0];
		auto mat1 = split2_0[1];
		auto mat2 = split2_1[0];
		auto mat3 = split2_1[1];

		//	Dot dot dot dot...
		dest[0] = bs::dot(mat0, src);
		dest[1] = bs::dot(mat1, src);
		dest[2] = bs::dot(mat2, src);
		dest[3] = bs::dot(mat3, src);
	}

	/**
	 * @brief      Column-major version of the dot product.
	 *
	 * @param[in]  mat   The matrix
	 * @param[in]  src   The source
	 * @param      dest  The destination
	 *
	 * @tparam     T     Scalar type
	 */
	template <typename T>
	inline void mult(const mat4<T>& mat, const vec4<T>& src, vec4<T>& dest){
		//	Split split split split...
		auto mat_split1 = bs::slice(mat);
		auto mat_split2_0 = bs::slice(mat_split1[0]);
		auto mat_split2_1 = bs::slice(mat_split1[1]);

		auto c0 = mat_split2_0[0];
		auto c1 = mat_split2_0[1];

		auto res1 = (c0 * src[0]) + (c1 * src[1]);

		auto c2 = mat_split2_1[0];
		auto c3 = mat_split2_1[1];
		
		auto res2 = (c2 * src[2]) + (c3 * src[3]);
		
		dest = res1 + res2;
	}
}	}