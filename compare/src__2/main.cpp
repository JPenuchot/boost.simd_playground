#include <iostream>
#include <numeric>

#include <playground/pvector.hpp>
#include <cblas.h>

#include <iacaMarks.h>

int main(){
	pg::pvector<float> pvec(8 << 10);
	std::iota(pvec.begin(), pvec.end(), 0);
	auto y = cblas_sdot(8 << 10, pvec.data(), 1, pvec.data(), 1);
	std::cout << y << '\n';
}
