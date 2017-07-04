#pragma once

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include "../types.hpp"

namespace pg { namespace graphics {
	template<typename T>
	T dot (vec4<T>& a, vec4<T>& b){
		boost::simd::pack<T, 4> pack_a(a.data());
		boost::simd::pack<T, 4> pack_b(b.data());

		return boost::simd::dot(pack_a, pack_b);
	}

}	}