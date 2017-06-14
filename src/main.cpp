#include <boost/simd/pack.hpp>

#include <iostream>

#include <algebra/dot.hpp>

int main(){
	jp::pvector<float, 3> a;
	a.data = {{ 2.f, 1.f, 1.f }};
	jp::pvector<float, 3> b;
	b.data = {{ 2.f, 3.f, 4.f }};

	std::cout	<< jp::algebra::dot_dumb(a, b) << '\n'
				<< jp::algebra::dot_auto(a, b) << '\n';
}