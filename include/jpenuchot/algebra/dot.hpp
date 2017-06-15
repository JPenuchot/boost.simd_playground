#pragma once

#include <numeric>

#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include <boost/simd/function/load.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/function/dot.hpp>
#include <boost/simd/function/sum.hpp>

#include <boost/simd/range/segmented_aligned_range.hpp>


#include "../pvector.hpp"

namespace jp { namespace algebra {
	namespace bs = boost::simd;

	/**
	 * @brief      Computes the dot product of a and b the dumb way.
	 *
	 * @param[in]  a     First vector
	 * @param[in]  b     Second vector
	 *
	 * @tparam     T     Element tye
	 * @tparam     N     Size of vector
	 *
	 * @return     Dot product of a and b
	 */
	template< typename T
			, std::size_t N
			>
	T dot_dumb	( pvector<T, N>& a
				, pvector<T, N>& b
				) {
		T res = 0;

		T* first_a = a.data.data();
		T* first_b = b.data.data();
		
		T* last_a = first_a + a.data.size();

		for(; first_a != last_a; first_a++, first_b++){ res += *first_a * *first_b; }

		return res;
	}

	template< typename T
			, std::size_t N
			>
	T dot_inner	( pvector<T, N>& a
				, pvector<T, N>& b
				) {
		bs::pack<T> p_res{0};
		T s_res = 0;

		auto a_alr = bs::segmented_aligned_range_t<T>(a);
		auto b_alr = bs::segmented_aligned_range_t<T>(b);

		p_res = std::inner_product(std::get<1>(a_alr).begin(), std::get<1>(a_alr).end(), std::get<1>(b_alr).begin(), {0});
	}

//	template< typename T
//			, std::size_t N
//			>
//	T dot_auto	( pvector<T, N>& a
//				, pvector<T, N>& b
//				) {
//
//		//	TODO : fix that s!@#
//
//		bs::pack<T> p_res{0};
//		T s_res = 0;
//
//		auto a_alr = bs::segmented_aligned_range_t<T>(a);
//		auto b_alr = bs::segmented_aligned_range_t<T>(b);
//
//		//	SIMD segment
//		//BOOST_FOREACH(boost::tie(a, b), boost::combine(std::get<1>(a_alr), std::get<1>(b_alr))){
//		//	p_res += bs::dot(a, b);
//		//}
//
//		//	Scalar segment
//		//BOOST_FOREACH(boost::tie(a, b), boost::combine(std::get<2>(a_alr), std::get<2>(b_alr))){
//		//	s_res += bs::dot(a, b);
//		//}
//
//		//return bs::sum(p_res) + s_res;
//		return 0;
//	}

	/**
	 * @brief      Computes dot product using boost::simd::pack without ranges etc
	 *
	 * @param      a     First vector
	 * @param      b     Second vector
	 *
	 * @tparam     T     Type contained by a and b
	 * @tparam     N     a and b's size
	 *
	 * @return     Dot product of a and b
	 */
	template< typename T
			, std::size_t N
			>
	T dot_simd	( pvector<T, N>& a
				, pvector<T, N>& b
				) {
		using pack_t = bs::pack<T>;

		pack_t resp0{0};
		pack_t resp1{0};
		pack_t resp2{0};
		pack_t resp3{0};

		T ress = 0;

		T* a_ptr = a.data.data();
		T* b_ptr = b.data.data();

		T* a_end = a_ptr + a.data.size();

		constexpr auto sz = pack_t::static_size;

		//	SIMD
		for(; a_ptr + (pack_t::static_size * 4) <= a_end; a_ptr+= pack_t::static_size * 4, b_ptr+= pack_t::static_size * 4){
			pack_t pa0(a_ptr);
			pack_t pb0(b_ptr);

			pack_t pa1(&a_ptr[sz]);
			pack_t pb1(&b_ptr[sz]);

			pack_t pa2(&a_ptr[2 * sz]);
			pack_t pb2(&b_ptr[2 * sz]);

			pack_t pa3(&a_ptr[3 * sz]);
			pack_t pb3(&b_ptr[3 * sz]);

			resp0 += pa0 * pb0;
			resp1 += pa1 * pb1;
			resp2 += pa2 * pb2;
			resp3 += pa3 * pb3;
		}

		resp0 += resp1;
		resp2 += resp3;
		resp0 += resp2;

		//	Scalar
		for(; a_ptr < a_end; a_ptr++, b_ptr++){
			ress += (*a_ptr) * (*b_ptr);
		}

		return bs::sum(resp0) + ress;
	}
} }