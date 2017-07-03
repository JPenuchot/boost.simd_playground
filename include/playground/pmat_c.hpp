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
	class alignas(boost::simd::pack<T>::alignment) pmat_c : public std::array<T, N * padding::padded_size<T>(M) > {
	private:

	public:
		static const auto padded_height = padding::padded_size<T>(M);
	};
}
