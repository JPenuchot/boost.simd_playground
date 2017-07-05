#include <boost/simd/pack.hpp>
#include <boost/simd/function/store.hpp>

#include <array>
#include <string>

namespace pg { namespace graphics {
	namespace bs = boost::simd;

	template< typename T >
	class alignas(boost::simd::pack<T>::alignment) vec4 : public boost::simd::pack<T, 4> {};
}	}