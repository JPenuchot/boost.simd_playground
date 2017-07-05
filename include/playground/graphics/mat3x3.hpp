#include <boost/simd/pack.hpp>

namespace pg { namespace graphics {
	template< typename T >
	using mat3 = boost::simd::pack<T, 16>;
}	}