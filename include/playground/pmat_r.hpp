#pragma once

#include <boost/simd/pack.hpp>

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
	class alignas(boost::simd::pack<T>::alignment) pmat_r : public std::array<T, M * padding::padded_size<T>(N) > {
	public:
		static const auto padded_width = padding::padded_size<T>(N);
	};
}
