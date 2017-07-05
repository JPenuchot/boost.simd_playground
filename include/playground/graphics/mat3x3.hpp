#include <boost/simd/pack.hpp>

namespace pg { namespace graphics {
	template< typename T >
	class mat3 : public boost::simd::pack<T, 16> {
		
	};
}	}