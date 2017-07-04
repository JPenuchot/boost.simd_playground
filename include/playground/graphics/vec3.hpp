#include <boost/simd/pack.hpp>
#include <array>

namespace pg { namespace graphics {
	template< typename T >
	class alignas(boost::simd::pack<T>::alignment) vec3 : public std::array<T, 4> {};
}	}