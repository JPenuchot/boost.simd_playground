#include <boost/simd/pack.hpp>

namespace pg { namespace graphics {
	template< typename T >
	class mat4 : public boost::simd::pack<T, 16> {
		
	};
}	}