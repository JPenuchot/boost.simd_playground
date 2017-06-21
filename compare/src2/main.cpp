#include <boost/simd/pack.hpp>

#include <iostream>

#include <jpenuchot/algebra/dot.hpp>

int main(){
	jp::pvector<float> pvec(8 << 10);
	std::iota(pvec.begin(), pvec.end(), 0);
	auto y = jp::algebra::dot_inner(pvec, pvec);
	std::cout << y << '\n';
}
