#pragma once

#include "dot_simd_versions.hpp"

namespace jp { namespace algebra {
	namespace bs = boost::simd;

	/**
	 * @brief      Alias for the best version of dot_simd yet
	 *
	 * @param      a     Vector A
	 * @param      b     Vector B
	 *
	 * @tparam     T     Vectors' type
	 *
	 * @return     The dot product of A and B
	 */
	template< typename T >
	constexpr T dot_simd(pvector<T>& a, pvector<T>& b) { return dot_simd_2(a, b); }
}	}