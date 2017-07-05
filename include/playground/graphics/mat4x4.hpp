#include <boost/simd/pack.hpp>
#include <array>

namespace pg { namespace graphics {
	template< typename T >
	class alignas(boost::simd::pack<T>::alignment) mat4 : public boost::simd::pack<T, 16> {
		
	};
}	}