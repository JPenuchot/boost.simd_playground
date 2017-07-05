#include <boost/simd/pack.hpp>
#include <array>

namespace pg { namespace graphics {
	template< typename T >
	class alignas(boost::simd::pack<T>::alignment) mat3 : public boost::simd::pack<T, 16> {
		
	};
}	}