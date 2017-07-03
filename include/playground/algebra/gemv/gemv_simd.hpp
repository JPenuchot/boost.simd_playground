#pragma once

#include <boost/iterator/zip_iterator.hpp>

#include <algorithm>

#include "../../parray.hpp"
#include "../../pmat_r.hpp"
#include "../../pmat_c.hpp"

#include "../dot/dot.hpp"

namespace pg { namespace algebra {
	template	< typename T
				, std::size_t M
				, std::size_t N
				>
	parray<T, M>& gemv_simd(pmat_r<T, M, N>& mat, parray<T, N>& vec){
		parray<T, M>* res = new parray<T, M>;
		
		for(std::size_t i = 0; i < M; i++)
			(*res)[i] = dot_simd(mat[i], vec);

		return *res;
	}

	template	< typename T
				, std::size_t M
				, std::size_t N
				>
	parray<T, M>& gemv_simd(pmat_c<T, M, N>& mat, parray<T, N>& vec){
		parray<T, M> res;
		res.fill(0.f);

		//	TODO

		return &res;
	}

}	}