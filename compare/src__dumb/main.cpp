#include <iostream>
#include <numeric>
#include <vector>

#include <playground/pvector.hpp>

#include <iacaMarks.h>

int main(){
	std::vector<float> pvec((8 << 10) + 1);
	std::iota(pvec.begin(), pvec.end(), 0);
	
	float y = 0.f;

	auto a_start = pvec.data();
	auto b_start = pvec.data();
	auto a_end = pvec.data() + pvec.size();

	for(;a_start < a_end; a_start++, b_start++) {
		IACA_START
		y += *a_start * *b_start;
	}
	IACA_END

	std::cout << y << '\n';
}
