#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/function/dot.hpp>

#include "../pvector.hpp"

namespace jp { namespace algebra {
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
	T dot_dumb	( pvector<T, N>& a
				, pvector<T, N>& b
				) {
		T res = 0;

		T* first_a = a.data.data();
		T* first_b = b.data.data();
		
		T* last_a = first_a + a.data.size();

		for(; first_a != last_a; first_a++, first_b++){
			res += *first_a * *first_b;
		}

		return res;
	}

	template< typename T
			, std::size_t N
			>
	T dot_inner	( pvector<T, N>& a
				, pvector<T, N>& b
				) {
		//	TODO
		
		//	std::inner_product
	}

	template< typename T
			, std::size_t N
			>
	T dot_auto	( pvector<T, N>& a
				, pvector<T, N>& b
				) {
		namespace bs = boost::simd;

		bs::pack<T> p_res{0};
		T s_res = 0;

		auto a_alr = bs::segmented_aligned_range_t<T>(a);
		auto b_alr = bs::segmented_aligned_range_t<T>(b);

		//	SIMD segment
		BOOST_FOREACH(boost::tie(a, b), boost::combine(std::get<1>(a_alr), std::get<1>(b_alr))){
			p_res += bs::dot(a, b);
		}

		//	Scalar segment
		BOOST_FOREACH(boost::tie(a, b), boost::combine(std::get<2>(a_alr), std::get<2>(b_alr))){
			s_res += bs::dot(a, b);
		}

		return bs::sum(p_res) + s_res;
	}

	/**
	 * @brief      Computes dot product using boost::simd::pack without ranges etc
	 *
	 * @param      a     First vector
	 * @param      b     Second vector
	 *
	 * @tparam     T     Type contained by a and b
	 * @tparam     N     a and b's size
	 *
	 * @return     Dot product of a and b
	 */
	template< typename T
			, std::size_t N
			>
	T dot_simd	( pvector<T, N>& a
				, pvector<T, N>& b
				) {

	}
} }