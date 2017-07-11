#include <boost/simd/pack.hpp>

namespace pg { namespace graphics {
	namespace bs = boost::simd;

	template< typename T >
	using vec4 = boost::simd::pack<T, 4>;
}	}