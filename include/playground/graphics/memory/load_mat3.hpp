#pragma once

#pragma once

#include <iostream>

#include <boost/simd/pack.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/reduction.hpp>

#include "../types.hpp"
#include "load_vec3.hpp"

namespace pg { namespace graphics {

	/**
	 * @brief      Loads a mat3
	 *
	 * @param      data  The data
	 * @param      res   The destination
	 *
	 * @tparam     T     Type
	 */
	template <typename T>
	BOOST_FORCEINLINE void load(T* data, mat3<T>& res){
		namespace bs = boost::simd;

		//	Getting our 4 vec3 into 3 pack<T, 4>
		bs::pack<T, 8> pp0(data);

		auto p0 = bs::slice_low(pp0);
		auto p1 = bs::slice_high(pp0);
		auto p2 = data[8];

		auto pd0 = p0;
		auto pd1 = bs::slide<3>(p0, p1);
		auto pd2 = bs::slide<2>(p1, p2);
		pd2[3] = p2;

		res = bs::combine
			( bs::combine(pd0,pd1)
			, bs::combine(pd2,bs::pack<T, 4>(T(0))));
	}

	/**
	 * @brief      Loads 4 mat3 optimally
	 *
	 * @param      data  The data
	 * @param      md0   Destination 0
	 * @param      md1   Destination 1
	 * @param      md2   Destination 2
	 * @param      md3   Destination 3
	 *
	 * @tparam     T     Type
	 */
	template <typename T>
	BOOST_FORCEINLINE void load(T* data, mat3<T>& md0, mat3<T>& md1, mat3<T>& md2, mat3<T>& md3){
		namespace bs = boost::simd;

		vec3<T> p0;
		vec3<T> p1;
		vec3<T> p2;
		vec3<T> p3;
		vec3<T> p0_;
		vec3<T> p1_;

		load(data, p0, p1, p2, p3);

		md0 = bs::combine
		( bs::combine
		( p0
		, p1), bs::combine
		( p2, vec3<T>(T(0))));

		data += 12;
		load(data, p0, p1, p2, p0_);

		md1 = bs::combine
		( bs::combine
		( p3
		, p0), bs::combine
		( p1, vec3<T>(T(0))));

		data += 12;
		load(data, p0, p1, p1_, p3);

		md2 = bs::combine
		( bs::combine
		( p2
		, p0_), bs::combine
		( p0, vec3<T>(T(0))));

		md3 = bs::combine
		( bs::combine
		( p1
		, p1_), bs::combine
		( p3, vec3<T>(T(0))));
	}

}	}