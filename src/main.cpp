#include <iostream>
#include <algorithm>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include <playground/graphics/types.hpp>
#include <playground/graphics/algebra/dot.hpp>
#include <playground/graphics/algebra/matvec.hpp>

//#include <cblas.h>

int main(){
	namespace pgg = pg::graphics;
	namespace bs = boost::simd;

	pgg::vec4<float> a;
	
	a[0] = 1.f;
	a[1] = 2.f;
	a[2] = 3.f;
	a[3] = 4.f;

	bs::pack<float, 4> ap {1.f};
	bs::pack<float, 4> bp {2.f};

	//float test = bs::dot(ap, bp);

	for(auto val : a) std::cout << val << ";"; std::cout << '\n';
	
	pgg::mat4<float> M;
	std::transform(M.begin(), M.end(), M.begin(), [](auto val){ return 1.f;	});
	pgg::matvec_c(M, a, a);
	for(auto val : a) std::cout << val << ";"; std::cout << '\n';
}
