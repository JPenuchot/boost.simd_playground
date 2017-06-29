#include <boost/simd/pack.hpp>

#include <iostream>

#include <playground/algebra/dot/dot.hpp>
#include <playground/pvector.hpp>
#include <playground/parray.hpp>

#include <cblas.h>

int main(){
	pg::pvector<float> pvec(2 << 20);
	std::iota(pvec.begin(), pvec.end(), 0);

	auto x = pg::algebra::dot_simd(pvec, pvec);
	std::cout << x << '\n';
	//x = pg::algebra::dot_simd(pvec, pvec);
	//std::cout << x << '\n';
	//x = cblas_sdot(pvec.size(), pvec.data(), 1, pvec.data(), 1);
	//std::cout << x << '\n';
}
