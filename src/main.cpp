
#include <iostream>
#include <algorithm>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include <playground/graphics/types.hpp>

#include <playground/graphics/memory/load.hpp>

#include <playground/graphics/algebra/dot.hpp>
#include <playground/graphics/algebra/matvec.hpp>
#include <playground/graphics/algebra/matmat.hpp>

//#include <cblas.h>

int main(){
	using namespace pg::graphics;
	namespace bs = boost::simd;

	float arr[16] = {
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
		15.f
	};

	mat4<float> A(arr);

	pg::graphics::mult4(A, A, A);

	std::cout << A << '\n';
}
