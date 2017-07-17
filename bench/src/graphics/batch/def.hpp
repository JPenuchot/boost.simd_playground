#pragma once

#include <benchmark/benchmark.h>

#include <array>
#include <numeric>

#include <playground/graphics/mat4x4.hpp>
#include <playground/graphics/mat3x3.hpp>

#include <playground/graphics/vec3.hpp>
#include <playground/graphics/vec4.hpp>

#include <playground/graphics/algebra/batch/matvec.hpp>
#include <playground/graphics/algebra/batch/vecmat.hpp>

#include <glm/glm.hpp>

#include "../dumb_versions.hpp"

namespace pgg = pg::graphics;

//	DUMB

template <typename T, std::size_t N>
static void batch__matvec4__dumb (benchmark::State& state){
	std::array<std::array<T, 4>, 4> mat {
		T(1), T(2), T(3), T(4),
		T(5), T(6), T(7), T(8),
		T(9), T(10), T(11), T(12),
		T(13), T(14), T(15), T(16)
	};

	std::array<T, 4 * N> vecarr;
	std::iota(vecarr.begin(), vecarr.end(), T(0));
	std::array<T, 4> vec;

	while(state.KeepRunning()){
		for(std::size_t i = 0; i + 3 < 4 * N; i+=4){
			std::copy(vecarr.data(), &(vecarr.data())[i + 4], vec.begin());
			matvec_dumb(mat, vec, vec);
			std::copy(vec.begin(), vec.end(), &vecarr[i]);
		}
		//benchmark::DoNotOptimize(vec);
	}
}

template <typename T, std::size_t N>
static void batch__vecmat4__dumb (benchmark::State& state){
	std::array<std::array<T, 4>, 4> mat {
		T(1), T(2), T(3), T(4),
		T(5), T(6), T(7), T(8),
		T(9), T(10), T(11), T(12),
		T(13), T(14), T(15), T(16)
	};

	std::array<T, 4 * N> vecarr;
	std::iota(vecarr.begin(), vecarr.end(), T(0));
	std::array<T, 4> vec;

	while(state.KeepRunning()){
		for(std::size_t i = 0; i + 3 < 4 * N; i+=4){
			std::copy(vecarr.data(), &(vecarr.data())[i + 4], vec.begin());
			vecmat_dumb(vec, mat, vec);
			std::copy(vec.begin(), vec.end(), &vecarr[i]);
		}
		//benchmark::DoNotOptimize(vec);
	}
}

//	SIMD

template <typename T, std::size_t N>
static void batch__matvec4__simd (benchmark::State& state){
	pgg::mat4<T> mat {
		T(1), T(2), T(3), T(4),
		T(5), T(6), T(7), T(8),
		T(9), T(10), T(11), T(12),
		T(13), T(14), T(15), T(16)
	};

	std::array<T, 4 * N> vec;
	std::iota(vec.begin(), vec.end(), T(0));

	while(state.KeepRunning()){
		pgg::batch_matvec4(mat, vec.data(), N, vec.data());
		benchmark::DoNotOptimize(vec);
	}
}


template <typename T, std::size_t N>
static void batch__vecmat4__simd (benchmark::State& state){
	pgg::mat4<T> mat {
		T(1), T(2), T(3), T(4),
		T(5), T(6), T(7), T(8),
		T(9), T(10), T(11), T(12),
		T(13), T(14), T(15), T(16)
	};

	std::array<T, 4 * N> vec;
	std::iota(vec.begin(), vec.end(), T(0));

	while(state.KeepRunning()){
		pgg::batch_vecmat4(mat, vec.data(), N, vec.data());
		benchmark::DoNotOptimize(vec);
	}
}

//	GLM


template <typename T, std::size_t N>
static void batch__matvec4__glm (benchmark::State& state){
	glm::mat4 mat {
		T(1), T(2), T(3), T(4),
		T(5), T(6), T(7), T(8),
		T(9), T(10), T(11), T(12),
		T(13), T(14), T(15), T(16)
	};

	std::array<T, 4 * N> vecarr;
	std::iota(vecarr.begin(), vecarr.end(), T(0));

	while(state.KeepRunning()){
		T* arr_beg = vecarr.data();
		T* arr_end = vecarr.data() + vecarr.size();

		for(; arr_beg + 16 <= arr_end; arr_beg+=16){
			//	Unroll unroll unroll unroll...
			glm::vec4 vec0(0.f);
			glm::vec4 vec1(0.f);
			glm::vec4 vec2(0.f);
			glm::vec4 vec3(0.f);

			vec0.x = arr_beg[0];
			vec0.y = arr_beg[1];
			vec0.z = arr_beg[2];
			vec0.w = arr_beg[3];

			vec1.x = arr_beg[4];
			vec1.y = arr_beg[5];
			vec1.z = arr_beg[6];
			vec1.w = arr_beg[7];

			vec2.x = arr_beg[8];
			vec2.y = arr_beg[9];
			vec2.z = arr_beg[10];
			vec2.w = arr_beg[11];

			vec3.x = arr_beg[12];
			vec3.y = arr_beg[13];
			vec3.z = arr_beg[14];
			vec3.w = arr_beg[15];

			vec0 = mat * vec0;
			vec1 = mat * vec1;
			vec2 = mat * vec2;
			vec3 = mat * vec3;

			arr_beg[0] = vec0.x;
			arr_beg[1] = vec0.y;
			arr_beg[2] = vec0.z;
			arr_beg[3] = vec0.w;

			arr_beg[4] = vec1.x;
			arr_beg[5] = vec1.y;
			arr_beg[6] = vec1.z;
			arr_beg[7] = vec1.w;

			arr_beg[8] = vec2.x;
			arr_beg[9] = vec2.y;
			arr_beg[10] = vec2.z;
			arr_beg[11] = vec2.w;

			arr_beg[12] = vec3.x;
			arr_beg[13] = vec3.y;
			arr_beg[14] = vec3.z;
			arr_beg[15] = vec3.w;
		}

		for(; arr_beg + 4 <= arr_end; arr_beg+=4){
			glm::vec4 vec0(0.f);
			
			vec0.x = arr_beg[0];
			vec0.y = arr_beg[1];
			vec0.z = arr_beg[2];
			vec0.w = arr_beg[3];

			vec0 = mat * vec0;

			arr_beg[0] = vec0.x;
			arr_beg[1] = vec0.y;
			arr_beg[2] = vec0.z;
			arr_beg[3] = vec0.w;
		}

	}
}


template <typename T, std::size_t N>
static void batch__vecmat4__glm (benchmark::State& state){
	glm::mat4 mat {
		T(1), T(2), T(3), T(4),
		T(5), T(6), T(7), T(8),
		T(9), T(10), T(11), T(12),
		T(13), T(14), T(15), T(16)
	};

	std::array<T, 4 * N> vecarr;
	std::iota(vecarr.begin(), vecarr.end(), T(0));

	while(state.KeepRunning()){
		for(std::size_t i = 0; i < 4 * N; i+=4){
			glm::vec4 vec(0.f);

			vec.x = vecarr[i];
			vec.y = vecarr[i + 1];
			vec.z = vecarr[i + 2];
			vec.w = vecarr[i + 3];
			
			vec = vec * mat;
			
			vecarr[i] = vec.x;
			vecarr[i + 1] = vec.y;
			vecarr[i + 2] = vec.z;
			vecarr[i + 3] = vec.w;
		}
	}
}
