#pragma once

#include <iostream>

#include <boost/simd/pack.hpp>
#include <boost/simd/function/store.hpp>
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
		bs::pack<T, 4> vec(src);
		
		bs::pack<T, 4> resp0(mat.data());
		bs::pack<T, 4> resp1(&mat.data()[4]);
		bs::pack<T, 4> resp2(&mat.data()[8]);
		bs::pack<T, 4> resp3(&mat.data()[12]);

		auto d0 = T(bs::dot(src, resp0));
		auto d1 = T(bs::dot(src, resp1));
		auto d2 = T(bs::dot(src, resp2));
		auto d3 = T(bs::dot(src, resp3));

		bs::pack<T, 4> dst;

		dst[0] = d0;
		dst[1] = d1;
		dst[2] = d2;
		dst[3] = d3;

		bs::store(dst, dest.data());
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
		bs::pack<float, 4> psrc(src);

		//	Maybe split 4 pack register into 4 scalars for better pipelining ?

		bs::pack<T, 4> res1 = 
			  (bs::pack<T, 4>(&mat[0]) * psrc[0])
			+ (bs::pack<T, 4>(&mat[4]) * psrc[1]);

		bs::pack<T, 4> res2 =
			  (bs::pack<T, 4>(&mat[8]) * psrc[2])
			+ (bs::pack<T, 4>(&mat[12]) * psrc[3]);
		
		bs::store(res1 + res2, dest.data());
	}
}	}