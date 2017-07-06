#pragma once

#pragma once

#include <iostream>

#include <boost/simd/pack.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/reduction.hpp>

#include "../types.hpp"

namespace pg { namespace graphics {

	/**
	 * @brief      Load 4 vec3 values optimally
	 *
	 * @param      data  Pointer to data
	 * @param      pd0   Destination pack 0
	 * @param      pd1   Destination pack 1
	 * @param      pd2   Destination pack 2
	 * @param      pd3   Destination pack 3
	 *
	 * @tparam     T     Type
	 */
	template <typename T>
	BOOST_FORCEINLINE void load(T* data, vec3<T>& pd0, vec3<T>& pd1, vec3<T>& pd2, vec3<T>& pd3){
		//	Getting our 4 vec3 into 3 pack<T, 4>
		namespace bs = boost::simd;

		bs::pack<T, 8> pp0(data);

		auto p0 = bs::slice_low(pp0);
		auto p1 = bs::slice_high(pp0);
		bs::pack<T, 4> p2(&data[8]);

		//	Everyday I'm shufflin' (Sorry port #5 :'( )
		pd1 = bs::slide<3>(p0, p1);
		pd2 = bs::slide<2>(p1, p2);
		pd0 = p0;
		pd3 = bs::slide<1>(p2);
	}

	/**
	 * @brief      Loads a single vec3
	 *
	 * @param      data  The data
	 * @param      pd    Destination
	 *
	 * @tparam     T     Type
	 */
	template <typename T>
	BOOST_FORCEINLINE void load(T* data, vec3<T>&pd) { pd = bs::shuffle<0, 1, 2, -1>(vec3<T>(data)); }
}	}