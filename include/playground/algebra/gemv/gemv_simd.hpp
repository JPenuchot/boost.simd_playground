#pragma once

#include <numeric>

#include "../../parray.hpp"
#include "../../pmat_r.hpp"
#include "../../pmat_c.hpp"

namespace pg { namespace algebra {
	template	< typename T
				, std::size_t M
				, std::size_t N
				>
	parray<T, M>& gemv_dumb(pmat_r<T, M, N>& mat, parray<T, N>& vec){
		parray<T, M> res;
		res.fill(0.f);
		
		//	TODO

		return &res;
	}

	template	< typename T
				, std::size_t M
				, std::size_t N
				>
	parray<T, M>& gemv_dumb(pmat_c<T, M, N>& mat, parray<T, N>& vec){
		parray<T, M> res;
		res.fill(0.f);

		//	TODO

		return &res;
	}
	
}	}