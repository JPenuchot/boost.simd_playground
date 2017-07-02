//	pVector : Vector type optimized using boost::simd::pack type.

#pragma once

#include <boost/array.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/pack.hpp>

#include <iterator>
#include <algorithm>
#include <vector>
#include <array>

namespace pg {
	template <typename T>
	constexpr std::size_t pmat_width(std::size_t m){
		constexpr auto card = boost::simd::cardinal_of<T>::size_t;
		return m + (m % card == 0 ? 0 : card - (m % card));
	}

	template <typename T>
	constexpr std::size_t pmat_size(std::size_t n, std::size_t m){
		constexpr auto card = boost::simd::cardinal_of<T>::size_t;
		return n * pmat_width<T>(m);
	}

	/**
	 * @brief      Static sized matrix, aligned and padded for SIMD stuff
	 *
	 * @tparam     T     Type
	 * @tparam     N     Line count
	 * @tparam     M     Row count
	 */
	template< typename T
			, std::size_t N
			, std::size_t M
			>
	class alignas(boost::simd::pack<T>::alignment) pmat : std::array<T, N * pmat_width<T>(M) > {
	private:

	public:
		static const auto padded_width = pmat_width<T>(M);

		constexpr T& operator() (std::size_t i, std::size_t j){ return this[i * padded_width + j]; }
		
		constexpr auto line_width(){ return padded_width; }
	};
}
