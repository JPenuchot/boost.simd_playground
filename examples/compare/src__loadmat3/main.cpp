
#include <iostream>
#include <algorithm>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include <playground/graphics/types.hpp>

#include <playground/graphics/memory/load.hpp>

#include <playground/graphics/algebra/dot.hpp>
#include <playground/graphics/algebra/matvec.hpp>
#include <playground/graphics/algebra/matmat.hpp>

#include <iacaMarks.h>

int main(){
	using namespace pg::graphics;
	namespace bs = boost::simd;

	alignas(32) float arr[36] = {
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
		11.f,
		12.f,
		13.f,
		14.f,
		15.f,
		16.f,
		17.f,
		18.f,
		19.f,
		20.f,
		21.f,
		22.f,
		23.f,
		24.f,
		25.f,
		26.f,
		27.f,
		28.f,
		29.f,
		30.f,
		31.f,
		32.f,
		33.f,
		34.f,
		35.f
	};

	mat4<float> A(arr);
	mat4<float> B(arr);
	mat4<float> C(arr);
	mat4<float> D(arr);

	IACA_START

	pg::graphics::load(arr, A, B, C, D);

	IACA_END

	std::cout
		<< A << '\n'
		<< B << '\n'
		<< C << '\n'
		<< D << '\n';
}
