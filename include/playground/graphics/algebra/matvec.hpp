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
	inline void matvec_r(const mat4<T>&mat, const vec4<T>& src, vec4<T>& dest){
		//	Split split split split...
		auto split1 = bs::split(mat);
		auto split2_0 = bs::split(split1[0]);
		auto split2_1 = bs::split(split1[1]);

		auto r0 = split2_0[0];
		auto r1 = split2_0[1];
		auto r2 = split2_1[0];
		auto r3 = split2_1[1];

		//	Dot dot dot dot...
		dest[0] = bs::dot(r0, src);
		dest[1] = bs::dot(r1, src);
		dest[2] = bs::dot(r2, src);
		dest[3] = bs::dot(r3, src);
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
	inline void matvec_c(const mat4<T>&mat, const vec4<T>& src, vec4<T>& dest){
		//	Split split split split...
		auto mat_split1 = bs::split(mat);
		auto mat_split2_0 = bs::split(mat_split1[0]);
		auto mat_split2_1 = bs::split(mat_split1[1]);

		auto c0 = mat_split2_0[0];
		auto c1 = mat_split2_0[1];
		auto c2 = mat_split2_1[0];
		auto c3 = mat_split2_1[1];

		//	Same on scalar
		auto vec_split1 = bs::split(src);
		auto vec_split2_0 = bs::split(vec_split1[0]);
		auto vec_split2_1 = bs::split(vec_split1[1]);

		auto v0 = vec_split2_0[0];
		auto v1 = vec_split2_0[1];
		auto v2 = vec_split2_1[0];
		auto v3 = vec_split2_1[1];

		bs::pack<T, 4> res1 = 
			  (bs::pack<T, 4>(&mat[0]) * v0)
			+ (bs::pack<T, 4>(&mat[4]) * v1);

		bs::pack<T, 4> res2 =
			  (bs::pack<T, 4>(&mat[8]) * v2)
			+ (bs::pack<T, 4>(&mat[12]) * v3);
		
		dest = res1 + res2;
	}
}	}