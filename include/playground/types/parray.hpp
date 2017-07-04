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
	
	/*
	template< typename T
			, std::size_t N
			>
	class parray {
		public:
			constexpr std::size_t getSize(){ return N; }
			
			alignas(boost::simd::pack<T>::alignment) std::array<T,N> data;
			//alignas(64) std::array<T,N> data;
	};
	*/
	template< typename T
			, std::size_t N>
	struct alignas(boost::simd::pack<T>::alignment) parray : std::array<T,N> {};
}