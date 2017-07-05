#include <boost/simd/pack.hpp>

namespace pg { namespace graphics {
	namespace bs = boost::simd;

	template< typename T >
	class vec4 : public boost::simd::pack<T, 4> {};
}	}