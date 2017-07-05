#include <iostream>
#include <algorithm>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include <playground/graphics/types.hpp>
#include <playground/graphics/algebra/dot.hpp>
#include <playground/graphics/algebra/matvec.hpp>

//#include <cblas.h>

int main(){
	using namespace pg::graphics;
	namespace bs = boost::simd;

	vec4<float> a{1.f};
	
	a[0] = 0.f;
	a[1] = 2.f;
	a[2] = 3.f;
	a[3] = 4.f;

	for(auto val : a) std::cout << val << ";";
		std::cout << '\n';
	
	mat4<float> M;
	std::transform(M.begin(), M.end(), M.begin(), [](auto val){ return 1.f;	});
	
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	mult(M, a, a);

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	
	for(auto val : a) std::cout << val << ";";
		std::cout << '\n';
}
