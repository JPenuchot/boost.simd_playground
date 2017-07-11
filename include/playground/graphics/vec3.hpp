#include <boost/simd/pack.hpp>

namespace pg { namespace graphics {
	template< typename T >
	using vec3 = boost::simd::pack<T, 4>;
}	}