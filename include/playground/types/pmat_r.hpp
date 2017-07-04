#pragma once

#include <boost/simd/pack.hpp>

#include <array>

#include "../helpers/padding.hpp"
#include "parray.hpp"

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
	class alignas(boost::simd::pack<T>::alignment) pmat_r : public std::array<parray<T, N>, M > {};
}
