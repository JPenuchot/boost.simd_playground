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
		for(std::size_t i = 0; i < 4 * N; i+=4){
			glm::vec4 vec(&vecarr[i]);
			vec = mat * vec;

			vecarr[i] = vec.x;
			vecarr[i + 1] = vec.y;
			vecarr[i + 2] = vec.z;
			vecarr[i + 3] = vec.w;
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
			glm::vec4 vec(&vecarr[i]);
			vec = vec * mat;
			
			vecarr[i] = vec.x;
			vecarr[i + 1] = vec.y;
			vecarr[i + 2] = vec.z;
			vecarr[i + 3] = vec.w;
		}
	}
}
