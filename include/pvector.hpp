//	pVector : Vector type optimized using boost::simd::pack type.

#pragma once

#include <boost/array.hpp>
#include <boost/simd/memory/allocator.hpp>

#include <iterator>
#include <algorithm>
#include <vector>
#include <array>

namespace jp {
	
	template< typename T
			, std::size_t N
			>
	class pvector {
		static_assert(std::is_fundamental<T>::value,
			"Type must be fundamental.");

		public:
			constexpr std::size_t getSize(){ return N; }
			
			alignas(16) std::array<T,N> data;
	};

	/**
	 * @brief      Matches the size of two pvector objects
	 *
	 * @param[in]  a     First vector
	 * @param[in]  b     Second vector
	 *
	 * @tparam     T     Contained type
	 * @tparam     N     Size of a
	 * @tparam     NN    Size of b
	 *
	 * @return     true if sizes match otherwise false
	 */
	template< typename T
			, typename TT
			, std::size_t N
			, std::size_t NN
			>
	constexpr bool pVectorMatch ( const pvector<T, N>  a
								, const pvector<TT, NN> b
								)
	{ return N == NN; }
}