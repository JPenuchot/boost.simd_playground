#pragma once

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include "../../types/parray.hpp"
#include "../../types/pvector.hpp"

namespace pg { namespace algebra {
	namespace bs = boost::simd;

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
		pack_t resp0{T(0)};
		pack_t resp1{T(0)};
		pack_t resp2{T(0)};
		pack_t resp3{T(0)};

		//	Scalar bit
		T ress = T(0);

		T* a_ptr = a.data();
		T* b_ptr = b.data();

		T* a_end = a_ptr + a.size();

		//	Comfort...
		constexpr auto sz = pack_t::static_size;

		//	SIMD, unrolled 4 times
		while(a_ptr + (sz * 4) <= a_end){
			pack_t pa0(a_ptr);
			pack_t pb0(b_ptr);
			a_ptr++; b_ptr++;

			pack_t pa1(&a_ptr[sz]);
			pack_t pb1(&b_ptr[sz]);
			a_ptr++; b_ptr++;

			pack_t pa2(&a_ptr[2 * sz]);
			pack_t pb2(&b_ptr[2 * sz]);
			a_ptr++; b_ptr++;

			pack_t pa3(&a_ptr[3 * sz]);
			pack_t pb3(&b_ptr[3 * sz]);
			a_ptr++; b_ptr++;

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
		pack_t resp0{T(0)};
		pack_t resp1{T(0)};
		pack_t resp2{T(0)};
		pack_t resp3{T(0)};

		//	Scalar bit
		T ress = T(0);

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

}	}