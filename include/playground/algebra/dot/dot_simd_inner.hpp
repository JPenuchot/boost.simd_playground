#pragma once

#include <numeric>

#include <boost/range/numeric.hpp>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>
#include <boost/simd/range/segmented_aligned_range.hpp>

#include "../../types/parray.hpp"
#include "../../types/pvector.hpp"

namespace pg { namespace algebra {
	namespace bs = boost::simd;

	template< typename T
			, std::size_t N
			>
	T dot_simd_inner	( parray<T, N>& a
						, parray<T, N>& b
						) {
		bs::pack<T> p_res{T(0)};
		auto s_res = T(0);

		auto a_alr = bs::segmented_aligned_range(a.begin(), a.end());
		auto b_alr = bs::segmented_aligned_range(b.begin(), b.end());

		p_res = boost::inner_product(a_alr.body, b_alr.body, p_res);
		s_res = boost::inner_product(a_alr.tail, b_alr.tail, s_res);

		return bs::sum(p_res) + s_res;
	}

	template< typename T >
	T dot_simd_inner	( pvector<T>& a
						, pvector<T>& b
						) {
		bs::pack<T> p_res{T(0)};
		auto s_res = T(0);

		auto a_alr = bs::segmented_aligned_range(a.begin(), a.end());
		auto b_alr = bs::segmented_aligned_range(b.begin(), b.end());

		p_res = boost::inner_product(a_alr.body, b_alr.body, p_res);
		s_res = boost::inner_product(a_alr.tail, b_alr.tail, s_res);

		return bs::sum(p_res) + s_res;
	}

}	}