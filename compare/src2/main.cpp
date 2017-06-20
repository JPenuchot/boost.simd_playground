#include <boost/simd/pack.hpp>

#include <iostream>

#include <jpenuchot/algebra/dot.hpp>

int main(){
	jp::parray<float, 8 << 17> pvec;
	std::iota(pvec.data.begin(), pvec.data.end(), 0);
	auto y = jp::algebra::dot_simd_1_unroll(pvec, pvec);
	std::cout << y << '\n';
}
