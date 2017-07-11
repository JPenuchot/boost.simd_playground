
#include <iostream>
#include <algorithm>
#include <array>
#include <numeric>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include <playground/graphics/types.hpp>

#include <playground/graphics/algebra/batch/matvec.hpp>

//#include <iacaMarks.h>

int main(){
	using namespace pg::graphics;
	namespace bs = boost::simd;

	alignas(32) std::array<float, 4 * 1024> vecs;
	std::iota(vecs.begin(), vecs.end(), 1.f);

	mat4<float> A{
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	};

	mat4<float> B;

	std::cout << A;

	transpose4(A, B);

	std::cout << B;

	batch_matvec4(A, vecs.data(), 1024, vecs.data());

	//for(auto a : vecs) std::cout << a << ", ";

}
