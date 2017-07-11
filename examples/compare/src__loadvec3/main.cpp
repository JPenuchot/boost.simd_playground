
#include <iostream>
#include <algorithm>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include <playground/graphics/types.hpp>
#include <playground/graphics/algebra/dot.hpp>
#include <playground/graphics/algebra/matvec.hpp>
#include <playground/graphics/memory/load.hpp>

#include <iacaMarks.h>

int main(){
	using namespace pg::graphics;
	namespace bs = boost::simd;

	float arr[12] = {
		0.f,
		1.f,
		2.f,
		3.f,
		4.f,
		5.f,
		6.f,
		7.f,
		8.f,
		9.f,
		10.f,
		11.f
	};

	vec3<float> v0;
	vec3<float> v1;
	vec3<float> v2;
	vec3<float> v3;

	IACA_START

	pg::graphics::load(arr, v0, v1, v2, v3);

	IACA_END

	std::cout	<< v0 << '\n'
				<< v1 << '\n'
				<< v2 << '\n'
				<< v3 << '\n';
}
