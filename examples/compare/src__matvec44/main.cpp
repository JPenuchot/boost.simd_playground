#include <iostream>
#include <algorithm>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include <playground/graphics/types.hpp>
#include <playground/graphics/algebra/dot.hpp>
#include <playground/graphics/algebra/matvec.hpp>

#include <iacaMarks.h>

int main(){
	using namespace pg::graphics;

	vec4<float> a{
		0.f,
		2.f,
		3.f,
		4.f
	};
	
	mat4<float> M{1.f};
	std::transform(M.begin(), M.end(), M.begin(), [](auto val){ return 1.f;	});
	
	IACA_START

	mult4(M, a, a);

	IACA_END

	std::cout << a << '\n';
}
