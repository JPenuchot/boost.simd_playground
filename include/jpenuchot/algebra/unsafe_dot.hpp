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

template	< typename T
			, std::size_t N
			>
	T dot_simd	( std::array<T, N> a
				, std::array<T, N> b
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

} }