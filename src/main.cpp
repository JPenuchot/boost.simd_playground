#include <boost/simd/pack.hpp>

#include <iostream>

#include <jpenuchot/algebra/dot.hpp>

int main(){
	jp::pvector<float> a(5); a = { 2.f, 1.f, 1.f, 7.f, 2.f };
	jp::pvector<float> b(5); b = { 2.f, 3.f, 4.f, 2.f, 2.f };

	jp::pvector<float> pvec(8 << 17);
	std::iota(pvec.begin(), pvec.end(), 0);

	auto x = jp::algebra::dot_dumb(pvec, pvec);
	std::cout << x << '\n';
	auto y = jp::algebra::dot_simd(pvec, pvec);
	std::cout << y << '\n';
	auto z = jp::algebra::dot_inner(pvec, pvec);
	std::cout << z << '\n';
}

