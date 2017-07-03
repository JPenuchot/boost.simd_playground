#include <boost/simd/pack.hpp>

#include <iostream>
#include <algorithm>

#include <playground/pmat_r.hpp>
#include <playground/algebra/gemv/gemv.hpp>

#include <cblas.h>

int main(){
	pg::pmat_r<float, 10, 10> pmattest;
	pg::parray<float, 10> parrtest;

	std::for_each(pmattest.begin(), pmattest.end(), [](auto& vec){
		std::transform(vec.begin(), vec.end(), vec.begin(), [](auto elmt){
			return 1.f;
		});
	});

	std::transform(parrtest.begin(), parrtest.end(), parrtest.begin(), [](auto elmt){
		return 1.f;
	});

	auto& restest = pg::algebra::gemv_simd(pmattest, parrtest);

	for(auto elmt : restest)
		std::cout << elmt << std::endl;	
}
