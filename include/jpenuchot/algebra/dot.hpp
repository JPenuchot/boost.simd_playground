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


#include "../parray.hpp"
#include "../pvector.hpp"

namespace jp { namespace algebra {
	namespace bs = boost::simd;

	template< typename T
			>
	T dot_dumb	( pvector<T>& a
				, pvector<T>& b
				) {
		T res = 0;

		auto first_a = a.data();
		auto first_b = b.data();
		
		auto last_a = first_a + a.size();

		for(; first_a != last_a; first_a++, first_b++){ res += *first_a * *first_b; }

		return res;
	}

	template< typename T
			>
	T dot_simd	( pvector<T>& a
				, pvector<T>& b
				) {
		using pack_t = bs::pack<T>;

		//	Init SIMD vectors
		pack_t resp0{0};
		pack_t resp1{0};
		pack_t resp2{0};
		pack_t resp3{0};

		//	Scalar bit
		T ress = 0;

		T* a_ptr = a.data();
		T* b_ptr = b.data();

		T* a_end = a_ptr + a.size();

		//	Comfort...
		constexpr auto sz = pack_t::static_size;

		//	SIMD, unrolled 4 times
		for(; a_ptr + (sz * 4) <= a_end; a_ptr+= sz * 4, b_ptr+= sz * 4){
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

		//	Scalar (end)
		for(; a_ptr < a_end; a_ptr++, b_ptr++){
			ress += (*a_ptr) * (*b_ptr);
		}

		return bs::sum(resp0) + ress;
	}

	template< typename T >
	T dot_inner	( pvector<T>& a
				, pvector<T>& b
				) {
		bs::pack<T> p_res{0};
		T s_res = 0;

		auto a_alr = bs::segmented_aligned_range(a.begin(), a.end());
		auto b_alr = bs::segmented_aligned_range(b.begin(), b.end());

		p_res = std::inner_product(a_alr.body.begin(), a_alr.body.end(), b_alr.body.begin(), p_res);
		s_res = std::inner_product(a_alr.tail.begin(), a_alr.tail.end(), b_alr.tail.begin(), s_res);

		return bs::sum(p_res) + s_res;
	}

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
	T dot_dumb	( parray<T, N>& a
				, parray<T, N>& b
				) {
		T res = 0;

		auto first_a = a.data.data();
		auto first_b = b.data.data();
		
		auto last_a = first_a + a.data.size();

		for(; first_a != last_a; first_a++, first_b++){ res += *first_a * *first_b; }

		return res;
	}

	template< typename T
			, std::size_t N
			>
	T dot_inner	( parray<T, N>& a
				, parray<T, N>& b
				) {
		bs::pack<T> p_res{0};
		T s_res = 0;

		auto a_alr = bs::segmented_aligned_range(a.data.begin(), a.data.end());
		auto b_alr = bs::segmented_aligned_range(b.data.begin(), b.data.end());

		p_res = std::inner_product(a_alr.body.begin(), a_alr.body.end(), b_alr.body.begin(), p_res);
		s_res = std::inner_product(a_alr.tail.begin(), a_alr.tail.end(), b_alr.tail.begin(), s_res);

		return bs::sum(p_res) + s_res;
	}

//	template< typename T
//			, std::size_t N
//			>
//	T dot_auto	( parray<T, N>& a
//				, parray<T, N>& b
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
	T dot_simd_full_unroll	( parray<T, N>& a
							, parray<T, N>& b
							) {
		using pack_t = bs::pack<T>;

		//	Init SIMD vectors
		pack_t resp0{0};
		pack_t resp1{0};
		pack_t resp2{0};
		pack_t resp3{0};

		//	Scalar bit
		T ress = 0;

		T* a_ptr = a.data.data();
		T* b_ptr = b.data.data();

		T* a_end = a_ptr + a.data.size();

		//	Comfort...
		constexpr auto sz = pack_t::static_size;

		//	SIMD, unrolled 4 times
		for(; a_ptr + (sz * 4) <= a_end; a_ptr+= sz * 4, b_ptr+= sz * 4){
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

		//	SIMD, unrolled 2 times
		for(; a_ptr + (sz * 2) <= a_end; a_end += sz * 2, b_ptr += sz * 2){
			pack_t pa0(a_ptr);
			pack_t pb0(b_ptr);

			pack_t pa1(&a_ptr[sz]);
			pack_t pb1(&b_ptr[sz]);

			resp0 += pa0 * pb0;
			resp1 += pa1 * pb1;
		}

		resp0 += resp1;

		//	SIMD, not unrolled
		for(; a_ptr + sz <= a_end; a_ptr += sz, b_ptr += sz){
			pack_t pa0(a_ptr);
			pack_t pb0(b_ptr);

			resp0 += pa0 * pb0;
		}

		//	Scalar (end)
		for(; a_ptr < a_end; a_ptr++, b_ptr++){
			ress += (*a_ptr) * (*b_ptr);
		}

		return bs::sum(resp0) + ress;
	}

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
	T dot_simd_2_unrolls	( parray<T, N>& a
				, parray<T, N>& b
				) {
		using pack_t = bs::pack<T>;

		//	Init SIMD vectors
		pack_t resp0{0};
		pack_t resp1{0};
		pack_t resp2{0};
		pack_t resp3{0};

		//	Scalar bit
		T ress = 0;

		T* a_ptr = a.data.data();
		T* b_ptr = b.data.data();

		T* a_end = a_ptr + a.data.size();

		//	Comfort...
		constexpr auto sz = pack_t::static_size;

		//	SIMD, unrolled 4 times
		for(; a_ptr + (sz * 4) <= a_end; a_ptr+= sz * 4, b_ptr+= sz * 4){
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

		//	SIMD, unrolled 2 times
		for(; a_ptr + (sz * 2) <= a_end; a_end += sz * 2, b_ptr += sz * 2){
			pack_t pa0(a_ptr);
			pack_t pb0(b_ptr);

			pack_t pa1(&a_ptr[sz]);
			pack_t pb1(&b_ptr[sz]);

			resp0 += pa0 * pb0;
			resp1 += pa1 * pb1;
		}

		resp0 += resp1;

		//	Scalar (end)
		for(; a_ptr < a_end; a_ptr++, b_ptr++){
			ress += (*a_ptr) * (*b_ptr);
		}

		return bs::sum(resp0) + ress;
	}

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
	T dot_simd_1_unroll	( parray<T, N>& a
				, parray<T, N>& b
				) {
		using pack_t = bs::pack<T>;
		constexpr auto sz = pack_t::static_size;

		//	Init SIMD vectors
		pack_t resp0{0};
		pack_t resp1{0};
		pack_t resp2{0};
		pack_t resp3{0};

		//	Scalar bit
		T ress = 0;

		T* a_ptr = a.data.data();
		T* b_ptr = b.data.data();

		T* a_end = a_ptr + a.data.size();

		//	SIMD, unrolled 4 times
		for(; a_ptr + (sz * 4) <= a_end; a_ptr+= sz * 4, b_ptr+= sz * 4){
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

		//	Scalar (end)
		for(; a_ptr < a_end; a_ptr++, b_ptr++){
			ress += (*a_ptr) * (*b_ptr);
		}

		return bs::sum(resp0) + ress;
	}
} }