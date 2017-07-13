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
	 * @param[in]  vec   The source
	 * @param      dest  The destination
	 *
	 * @tparam     T     Numeric type
	 */
	template <typename T>
	BOOST_FORCEINLINE void mult3(const vec3<T>& vec, const mat3<T>& mat, vec3<T>& dest){
		auto mss0 = bs::slice_low(mat);
		auto mss1 = bs::slice_high(mat);

		auto ms0 = bs::shuffle<0, 1, 2, -1>(bs::slice_low(mss0));
		auto ms1 = bs::shuffle<0, 1, 2, -1>(bs::slice_high(mss0));
		auto ms2 = bs::shuffle<0, 1, 2, -1>(bs::slice_low(mss1));

		dest = bs::pack<T, 4>{
			bs::dot(vec, ms0),
			bs::dot(vec, ms1),
			bs::dot(vec, ms2),
			T(0)
		};
	}

	/**
	 * @brief      Cumputes a Matrix x Vector product for size 4 operands
	 *
	 * @param[in]  mat   The matrix
	 * @param[in]  vec   The source
	 * @param      dest  The destination
	 *
	 * @tparam     T     Numeric type
	 */
	template <typename T>
	BOOST_FORCEINLINE void mult4(const vec4<T>& vec, const mat4<T>& mat, vec4<T>& dest){
		auto mss0 = bs::slice_low(mat);
		auto mss1 = bs::slice_high(mat);

		auto ms0 = bs::slice_low(mss0);
		auto ms1 = bs::slice_high(mss0);
		auto ms2 = bs::slice_low(mss1);
		auto ms3 = bs::slice_high(mss1);

		dest = bs::pack<T, 4>{
			bs::dot(vec, ms0),
			bs::dot(vec, ms1),
			bs::dot(vec, ms2),
			bs::dot(vec, ms3)
		};
	}
}	}