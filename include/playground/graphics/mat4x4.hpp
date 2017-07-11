#include <boost/simd/pack.hpp>

namespace pg { namespace graphics {
	template< typename T >
	using mat4 = boost::simd::pack<T, 16>;
}	}