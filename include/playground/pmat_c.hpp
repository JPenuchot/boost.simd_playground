//	pVector : Vector type optimized using boost::simd::pack type.

#pragma once

#include <boost/array.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/pack.hpp>

#include <iterator>
#include <algorithm>
#include <vector>
#include <array>

#include "helpers/padding.hpp"

namespace pg {
	/**
	 * @brief      Static sized matrix, aligned and padded for SIMD stuff
	 *
	 * @tparam     T     Type
	 * @tparam     N     Line count
	 * @tparam     M     Row count
	 */
	template< typename T
			, std::size_t M
			, std::size_t N
			>
	class alignas(boost::simd::pack<T>::alignment) pmat_c : public std::array<T, N * padding::padded_size<T>(M) > {
	private:

	public:
		static const auto padded_height = padding::padded_size<T>(M);

		constexpr auto& operator() (const std::size_t i, const std::size_t j){ return this[i * padded_width + j]; }
		//constexpr T operator() (std::size_t i, std::size_t j){ return this[i * padded_width + j]; }
		
		constexpr auto column_height(){ return padded_height; }
	};
}
