#pragma once

#include <iostream>

#include <boost/simd/pack.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/reduction.hpp>

#include "../types.hpp"

namespace pg { namespace graphics {
	namespace bs = boost::simd;
	
	template <typename T>
	inline void mult3(const mat3<T>& A, const mat3<T>& B, mat3<T>& dest){
		//	TODO
	}

	template <typename T>
	inline void mult4(const mat4<T>& A, const mat4<T>& B, mat4<T>& dest){
		//	Slice slice slice slice...
		auto B__0 = bs::slice_low(B);
		auto B__1 = bs::slice_high(B);

		auto B0 = bs::slice_low(B__0);
		auto B1 = bs::slice_high(B__0);
		auto B2 = bs::slice_low(B__1);
		auto B3 = bs::slice_high(B__1);
		
		//	Compute compute compute compute...

		//	res0
		auto res0 =
			vec4<T>(A[0]) * B0 +
			vec4<T>(A[1]) * B1 +
			vec4<T>(A[2]) * B2 +
			vec4<T>(A[3]) * B3;

		//	res1
		auto res1 =
			vec4<T>(A[4]) * B0 +
			vec4<T>(A[5]) * B1 +
			vec4<T>(A[6]) * B2 +
			vec4<T>(A[7]) * B3;

		//	res2
		auto res2 =
			vec4<T>(A[8]) * B0 +
			vec4<T>(A[9]) * B1 +
			vec4<T>(A[10]) * B2 +
			vec4<T>(A[11]) * B3;

		//	res3
		auto res3 =
			vec4<T>(A[12]) * B0 +
			vec4<T>(A[13]) * B1 +
			vec4<T>(A[14]) * B2 +
			vec4<T>(A[15]) * B3;

		dest = bs::combine(
				bs::combine(res0, res1),
				bs::combine(res2, res3));
	}
}	}