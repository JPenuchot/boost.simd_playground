#pragma once

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>
#include <boost/simd/arithmetic.hpp>

#include <boost/simd/function/load.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/function/dot.hpp>
#include <boost/simd/function/sum.hpp>

#include "../../parray.hpp"
#include "../../pvector.hpp"

namespace jp { namespace algebra {
	namespace bs = boost::simd;

	/**
	 * @brief      Computes dot product using unrolled loop
	 *
	 * @param      a     Vector
	 * @param      b     Vector
	 *
	 * @tparam     T     a and b's type
	 *
	 * @return     Dot product of a and b
	 */
	template< typename T
			>
	T dot_simd_1	( pvector<T>& a
					, pvector<T>& b
					) {
		using pack_t = bs::pack<T>;
		constexpr auto sz = pack_t::static_size;
		constexpr auto sz4 = sz * 4;

		//	Init SIMD vectors
		bs::pack<T> resp0{T(0)};
		bs::pack<T> resp1{T(0)};
		bs::pack<T> resp2{T(0)};
		bs::pack<T> resp3{T(0)};

		//	Scalar bit
		auto ress = T(0);

		//	Pointers
		auto a_ptr = a.data();
		auto b_ptr = b.data();
		auto a_end = a_ptr + a.size();

		//	SIMD, unrolled 4 times
		while(a_ptr + sz4 <= a_end){
			pack_t pa0(a_ptr);
			pack_t pb0(b_ptr);
			a_ptr+=sz; b_ptr+=sz;

			pack_t pa1(a_ptr);
			pack_t pb1(b_ptr);
			a_ptr+=sz; b_ptr+=sz;

			pack_t pa2(a_ptr);
			pack_t pb2(b_ptr);
			a_ptr+=sz; b_ptr+=sz;

			pack_t pa3(a_ptr);
			pack_t pb3(b_ptr);
			a_ptr+=sz; b_ptr+=sz;

			resp0 += pa0 * pb0;
			resp1 += pa1 * pb1;
			resp2 += pa2 * pb2;
			resp3 += pa3 * pb3;
		}

		resp0 += resp1;
		resp2 += resp3;
		resp0 += resp2;

		//	Scalar (end)
		for(; a_ptr < a_end; a_ptr++, b_ptr++)
			ress += (*a_ptr) * (*b_ptr);

		return bs::sum(resp0) + ress;
	}

	/**
	 * @brief      Computes dot product using an unrolled loop and forced fmadd
	 * 
	 *
	 * @param      a     Vector
	 * @param      b     Vector
	 *
	 * @tparam     T     a and b's type
	 *
	 * @return     Dot product of a and b
	 */
	template< typename T
			>
	T dot_simd_2	( pvector<T>& a
					, pvector<T>& b
					) {
		using pack_t = bs::pack<T>;
		constexpr auto sz = pack_t::static_size;
		constexpr auto sz4 = sz * 4;

		//	Init SIMD vectors
		bs::pack<T> resp0{T(0)};
		bs::pack<T> resp1{T(0)};
		bs::pack<T> resp2{T(0)};
		bs::pack<T> resp3{T(0)};

		//	Scalar bit
		auto ress = T(0);

		//	Pointers
		auto a_ptr = a.data();
		auto b_ptr = b.data();
		auto a_end = a_ptr + a.size();

		//	SIMD, unrolled 4 times
		while(a_ptr + sz4 <= a_end){
			resp0 += pack_t(a_ptr) * pack_t(b_ptr);
			a_ptr+=sz; b_ptr+=sz;

			resp1 += pack_t(a_ptr) * pack_t(b_ptr);
			a_ptr+=sz; b_ptr+=sz;

			resp2 += pack_t(a_ptr) * pack_t(b_ptr);
			a_ptr+=sz; b_ptr+=sz;

			resp3 += pack_t(a_ptr) * pack_t(b_ptr);
			a_ptr+=sz; b_ptr+=sz;
		}

		resp0 += resp1;
		resp2 += resp3;
		resp0 += resp2;

		//	Scalar (end)
		for(; a_ptr < a_end; a_ptr++, b_ptr++)
			ress += (*a_ptr) * (*b_ptr);

		return bs::sum(resp0) + ress;
	}

}	}