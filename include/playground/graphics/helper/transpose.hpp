#pragma once

#include <boost/simd/pack.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/reduction.hpp>

#include "../types.hpp"

namespace pg { namespace graphics {

	template <typename T>
	BOOST_FORCEINLINE void transpose4(const mat4<T>& src, mat4<T>& dest){
		namespace bs = boost::simd;

		dest = bs::shuffle<
			0,	4,	8,	12,
			1,	5,	9,	13,
			2,	6,	10,	14,
			3,	7,	11,	15
		>(src);

		//dest[0] =	src[0];	dest[1] =	src[4];	dest[2] =	src[8];		dest[3] =	src[12]; 
		//dest[4] =	src[1];	dest[5] =	src[5];	dest[6] =	src[9];		dest[7] =	src[13]; 
		//dest[8] =	src[2];	dest[9] =	src[6];	dest[10] =	src[10];	dest[11] =	src[14]; 
		//dest[12] =	src[3];	dest[13] =	src[7];	dest[14] =	src[11];	dest[15] =	src[15]; 

		/*

		bs::pack<T, 8> mss0 = bs::slice_low(src);
		bs::pack<T, 8> mss1 = bs::slice_high(src);

		bs::pack<T, 4> ms0 = bs::slice_low(mss0);
		bs::pack<T, 4> ms1 = bs::slice_high(mss0);
		bs::pack<T, 4> ms2 = bs::slice_low(mss1);
		bs::pack<T, 4> ms3 = bs::slice_high(mss1);

		//	Typically the kind of stuff you wanna do only once and for all... I might figure out a better way to do that later
		
		//bs::pack<T, 4> line0 = bs::shuffle<0, 4, 8, 12>(mss0, mss1);
		bs::pack<T, 4> line0 =
			  bs::shuffle<0, 4, -1, -1>(ms0, ms1)
			+ bs::shuffle<-1, -1, 0, 4>(ms2, ms3);

		//bs::pack<T, 4> line1 = bs::shuffle<1, 5, 9, 13>(mss0, mss1);
		bs::pack<T, 4> line1 =
			  bs::shuffle<1, 5, -1, -1>(ms0, ms1)
			+ bs::shuffle<-1, -1, 1, 5>(ms2, ms3);
		
		//bs::pack<T, 4> line2 = bs::shuffle<2, 6, 10, 14>(mss0, mss1);
		bs::pack<T, 4> line2 =
			  bs::shuffle<2, 6, -1, -1>(ms0, ms1)
			+ bs::shuffle<-1, -1, 2, 6>(ms2, ms3);
		
		//bs::pack<T, 4> line3 = bs::shuffle<3, 7, 11, 15>(mss0, mss1);
		bs::pack<T, 4> line3 =
			  bs::shuffle<3, 7, -1, -1>(ms0, ms1)
			+ bs::shuffle<-1, -1, 3, 7>(ms2, ms3);

		dest = bs::combine(bs::combine
			( line0
			, line1), bs::combine
			( line2
			, line3));
			*/
	}

}	}