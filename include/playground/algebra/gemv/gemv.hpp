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
		for(std::size_t i = 0; i < M; i++){
		for(std::size_t j = 0; j < N; j++){
			res[i] += vec[j] * mat[i * mat.line_width + j];
		} }

		return &res;
	}

	template	< typename T
				, std::size_t M
				, std::size_t N
				>
	parray<T, M>& gemv_dumb(pmat_c<T, M, N>& mat, parray<T, N>& vec){
		parray<T, M> res;
		res.fill(0.f);
		for(std::size_t j = 0; j < N; j++){
		for(std::size_t i = 0; i < M; i++){
			res[i] += vec[j] * mat[j * mat.column_height + i];
		} }

		return &res;
	}
}	}