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
	
	template< typename T
			>
	class pvector {
		public:			
			std::vector<T, boost::simd::allocator<T>> data;

			pvector(std::size_t size):
				data(std::vector<T, boost::simd::allocator<T>>(size)){}
	};
}