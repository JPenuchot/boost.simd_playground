#include <boost/simd/pack.hpp>

#include <iostream>

#include <jpenuchot/algebra/dot.hpp>

int main(){
	jp::pvector<float, 5> a; a.data = {{ 2.f, 1.f, 1.f, 7.f, 2.f }};
	jp::pvector<float, 5> b; b.data = {{ 2.f, 3.f, 4.f, 2.f, 2.f }};

	std::cout	<< jp::algebra::dot_dumb(a, b) << '\n'
				<< jp::algebra::dot_simd(a, b) << '\n';
}
