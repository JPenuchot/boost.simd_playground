#include <boost/simd/pack.hpp>
#include <boost/simd/function/store.hpp>

#include <array>
#include <string>

namespace pg { namespace graphics {
	namespace bs = boost::simd;

	template< typename T >
	class alignas(boost::simd::pack<T>::alignment) vec4 : public std::array<T, 4> {
	public:
		//	Constructors
		//vec4(const std::array<T, 4>& arr){ bs::store(bs::pack<T, 4>(arr), this); }
		//vec4(const std::array<T, 4> arr){ bs::store(bs::pack<T, 4>(arr), this); }
		//vec4(){ bs::store(bs::pack<T, 4>(T(0)), this); }
		//vec4(T val){ bs::store(bs::pack<T, 4>(val), this); }

		inline void operator= (const std::array<T, 4>& src){ bs::store(bs::pack<T, 4>(src), this);	}
	};
}	}