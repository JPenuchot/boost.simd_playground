//	pVector : Vector type optimized using boost::simd::pack type.

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

	/**
	 * @brief      Computes the dot product of a and b the dumb way.
	 *
	 * @param[in]  a     First vector
	 * @param[in]  b     Second vector
	 *
	 * @tparam     T     Element tye
	 * @tparam     N     Size of vector
	 *
	 * @return     Dot product of a and b
	 */
	template< typename T
			, std::size_t N
			>
	T dumb_dot	( pvector<T, N>& a
			, pvector<T, N>& b
			) {
		namespace bs = boost::simd;

		T res = 0;

		T* first_a = a.data.data();
		T* first_b = b.data.data();
		
		T* last_a = first_a + a.data.size();

		for(; first_a != last_a; first_a++, first_b++){
			res += *first_a * *first_b;
		}

		return res;
	}
}