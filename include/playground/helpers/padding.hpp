#pragma once

#include <boost/array.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/pack.hpp>

#include <iterator>
#include <algorithm>
#include <vector>
#include <array>

namespace pg { namespace padding {
	/**
	 * @brief      Returns the adequate padding to make a container fit perfectly in SIMD registers
	 *
	 * @param[in]  m     Size
	 *
	 * @tparam     T     Container's contained type
	 *
	 * @return     Padding
	 */
	template <typename T>
	inline constexpr std::size_t padding(std::size_t m){
		constexpr auto card = sizeof(boost::simd::cardinal_of_t<T>);
		return (m % card == 0 ? 0 : card - (m % card));
	}

	/**
	 * @brief      Returns the padded size of a container so it can fit perfectly in SIMD registers
	 *
	 * @param[in]  m     Size
	 *
	 * @tparam     T     Container's contained type
	 *
	 * @return     Adjusted size
	 */
	template <typename T>
	inline constexpr std::size_t padded_size(std::size_t m){ return m + padding<T>(m); }

}	}