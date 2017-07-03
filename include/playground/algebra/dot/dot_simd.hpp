#pragma once

#include "dot_simd_versions.hpp"

namespace pg { namespace algebra {
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
	constexpr T dot_simd(
		  const pvector<T>& a
		, const pvector<T>& b
		) { return dot_simd_4(a, b); }

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
	template< typename T
			, std::size_t N >
	constexpr T dot_simd(
		  const parray<T, N>& a
		, const parray<T, N>& b
		) { return dot_simd_4(a, b); }
}	}