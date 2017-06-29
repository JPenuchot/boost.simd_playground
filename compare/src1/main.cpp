#include <iostream>
#include <numeric>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>
#include <boost/simd/arithmetic.hpp>

#include <boost/simd/function/load.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/function/dot.hpp>
#include <boost/simd/function/sum.hpp>

#include <jpenuchot/pvector.hpp>

#include <iacaMarks.h>

template< typename T
			>
	T dot_simd	( const jp::pvector<T>& a
				, const jp::pvector<T>& b
				) {
		namespace bs = boost::simd;

		using pack_t = bs::pack<T>;
		constexpr auto sz = pack_t::static_size;
		constexpr auto sz2 = sz * 2;
		constexpr auto sz3 = sz * 3;
		constexpr auto sz4 = sz * 4;

		//	Init SIMD vectors
		bs::pack<T> resp0{T(0)};
		bs::pack<T> resp1{T(0)};
		bs::pack<T> resp2{T(0)};
		bs::pack<T> resp3{T(0)};

		//	Scalar bit
		auto ress = T(0);

		//	Pointers
		auto a_ptr = a.data();
		auto b_ptr = b.data();
		auto a_end = a_ptr + a.size();

		//	SIMD, unrolled 4 times
		for(;a_ptr + sz4 <= a_end; a_ptr += sz4, b_ptr+= sz4){
			IACA_START
			resp0 = bs::fma(pack_t(a_ptr), pack_t(b_ptr), resp0);
			resp1 = bs::fma(pack_t(&a_ptr[sz]), pack_t(&b_ptr[sz]), resp1);
			resp2 = bs::fma(pack_t(&a_ptr[sz2]), pack_t(&b_ptr[sz2]), resp2);
			resp3 = bs::fma(pack_t(&a_ptr[sz3]), pack_t(&b_ptr[sz3]), resp3);
		}

		resp0 += resp1;
		resp2 += resp3;
		resp0 += resp2;
		IACA_END

		//	Scalar (end)
		for(; a_ptr < a_end; a_ptr++, b_ptr++)
			ress += (*a_ptr) * (*b_ptr);

		return bs::sum(resp0) + ress;
	}

int main(){
	jp::pvector<float> pvec(8 << 10);
	std::iota(pvec.begin(), pvec.end(), 0);
	auto y = dot_simd(pvec, pvec);
	std::cout << y << '\n';
}
