#include <boost/simd/pack.hpp>

#include <iostream>

#include <jpenuchot/algebra/dot/dot.hpp>
#include <jpenuchot/pvector.hpp>
#include <jpenuchot/parray.hpp>

#include <cblas.h>

int main(){
	jp::pvector<float> pvec(2 << 20);
	std::iota(pvec.begin(), pvec.end(), 0);

	auto x = jp::algebra::dot_simd(pvec, pvec);
	std::cout << x << '\n';
	//x = jp::algebra::dot_simd(pvec, pvec);
	//std::cout << x << '\n';
	//x = cblas_sdot(pvec.size(), pvec.data(), 1, pvec.data(), 1);
	//std::cout << x << '\n';
}
