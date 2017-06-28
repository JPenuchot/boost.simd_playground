//	pVector : Vector type optimized using boost::simd::pack type.

#pragma once

#include <boost/array.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/pack.hpp>

#include <iterator>
#include <algorithm>
#include <vector>
#include <array>

namespace jp {
	template<typename T, std::size_t N, std::size_t M>
	using pvector<N, M> = std::vector<T, boost::simd::allocator<T>>;
}
