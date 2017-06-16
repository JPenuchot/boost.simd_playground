#include <boost/simd/pack.hpp>

#include <iostream>

#include <jpenuchot/algebra/dot.hpp>

int main(){
	jp::pvector<float, 5> a; a.data = {{ 2.f, 1.f, 1.f, 7.f, 2.f }};
	jp::pvector<float, 5> b; b.data = {{ 2.f, 3.f, 4.f, 2.f, 2.f }};

	jp::pvector<float, 8 << 17> pvec;
	std::iota(pvec.data.begin(), pvec.data.end(), 0);

	auto x = jp::algebra::dot_dumb(pvec, pvec);
	std::cout << x << '\n';
	auto y = jp::algebra::dot_simd_1_unroll(pvec, pvec);
	std::cout << y << '\n';

//	std::cout	<< jp::algebra::dot_dumb(pvec, pvec) << '\n'
//				<< jp::algebra::dot_simd(pvec, pvec) << '\n';
}
