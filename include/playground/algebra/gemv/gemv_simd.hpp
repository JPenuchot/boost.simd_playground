#pragma once

#include <boost/iterator/zip_iterator.hpp>

#include <algorithm>

#include "../../types/parray.hpp"
#include "../../types/pmat_r.hpp"
#include "../../types/pmat_c.hpp"

#include "../dot/dot.hpp"

namespace pg { namespace algebra {
	namespace bs = boost::simd;

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
		using pack_t = bs::pack<T>;
		constexpr auto sz = pack_t::static_size;
		constexpr auto sz4 = sz * 4;

		parray<T, M>* res = new parray<T, M>;
		
		pack_t resp0{T(0)};
		pack_t resp1{T(0)};
		pack_t resp2{T(0)};
		pack_t resp3{T(0)};

		for(std::size_t j = 0; j < N; j++){
			auto mat_beg = mat[j].data();
			auto mat_end = mat[j].data() + mat[j].size_t();

			auto vec_beg = vec.data();

			//	TODO : 4x unrolled loop
			
		}

		return &res;
	}

}	}