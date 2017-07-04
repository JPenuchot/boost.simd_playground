#pragma once

#include <numeric>

#include "../../types/parray.hpp"
#include "../../types/pvector.hpp"

namespace pg { namespace algebra {
	template< typename T
			>
	T dot_dumb	( const pvector<T>& a
				, const pvector<T>& b
				) { return std::inner_product(a.begin(), a.end(), b.begin(), T(0)); }

	template< typename T
			, std::size_t N
			>
	T dot_dumb	( const parray<T, N>& a
				, const parray<T, N>& b
				) { return std::inner_product(a.begin(), a.end(), b.begin(), T(0)); }

}	}