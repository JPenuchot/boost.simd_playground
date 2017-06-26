#include <iostream>
#include <numeric>

#include <cblas.h>
#include <jpenuchot/pvector.hpp>

int main(){
	constexpr std::size_t size = 8 << 10;
	jp::pvector<float> pvec(size);
	std::iota(pvec.begin(), pvec.end(), 0);
	auto y = cblas_sdot(size, pvec.data(), 1, pvec.data(), 1);
	std::cout << y << '\n';
}
