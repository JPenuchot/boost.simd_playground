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
	 * @brief      Cumputes a Matrix x Vector product for size 3 operands
	 *
	 * @param[in]  mat   The matrix
	 * @param[in]  src   The source
	 * @param      dest  The destination
	 *
	 * @tparam     T     Numeric type
	 */
	template <typename T>
	inline void mult3(const mat3<T>& mat, const vec3<T>& src, vec3<T>& dest){
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

	/**
	 * @brief      Cumputes a Matrix x Vector product for size 4 operands
	 *
	 * @param[in]  mat   The matrix
	 * @param[in]  src   The source
	 * @param      dest  The destination
	 *
	 * @tparam     T     Numeric type
	 */
	template <typename T>
	inline void mult4(const mat4<T>& mat, const vec4<T>& src, vec4<T>& dest){
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