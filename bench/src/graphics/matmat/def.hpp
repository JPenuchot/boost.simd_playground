#include <benchmark/benchmark.h>

#include <array>
#include <numeric>

#include <playground/graphics/mat4x4.hpp>
#include <playground/graphics/mat3x3.hpp>

#include <playground/graphics/vec3.hpp>
#include <playground/graphics/vec4.hpp>

#include <playground/graphics/algebra/matmat.hpp>

#include <playground/graphics/helper/transpose.hpp>

#include <glm/glm.hpp>

#include "../dumb_versions.hpp"

namespace pgg = pg::graphics;

template <typename T>
static void matvec__matmat4__simd (benchmark::State& state){
	pgg::mat4<T> mat {
		T(1), T(2), T(3), T(4),
		T(5), T(6), T(7), T(8),
		T(9), T(10), T(11), T(12),
		T(13), T(14), T(15), T(16)
	};

	pgg::mat4<T> matt;

	pgg::transpose4(mat, matt);

	while(state.KeepRunning()){
		pgg::mult4(mat, matt, mat);
		pgg::mult4(mat, matt, mat);
		pgg::mult4(mat, matt, mat);
		pgg::mult4(mat, matt, mat);
	}
	benchmark::DoNotOptimize(mat);
}

template <typename T>
static void matvec__matmat4__glm (benchmark::State& state){
	glm::mat4 mat {
		1.f,	2.f,	3.f,	4.f,
		5.f,	6.f,	7.f,	8.f,
		9.f,	10.f,	11.f,	12.f,
		13.f,	14.f,	15.f,	16.f
	};

	glm::mat4 matt = glm::transpose(mat);

	while(state.KeepRunning()){
		mat *= matt;
		mat *= matt;
		mat *= matt;
		mat *= matt;
	}
	benchmark::DoNotOptimize(mat);
}
