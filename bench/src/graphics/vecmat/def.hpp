#include <benchmark/benchmark.h>

#include <array>
#include <numeric>

#include <playground/graphics/mat4x4.hpp>
#include <playground/graphics/mat3x3.hpp>

#include <playground/graphics/vec3.hpp>
#include <playground/graphics/vec4.hpp>

#include <playground/graphics/algebra/vecmat.hpp>

namespace pgg = pg::graphics;

/**
 * @brief      Dumb reference for vecmat product
 *
 * @param      vec   The vector
 * @param      mat   The matrix
 * @param      res   The result
 *
 * @tparam     T     Type
 * @tparam     N     Size
 */
template <typename T, std::size_t N>
void vecmat_dumb(std::array<T, N>&vec, std::array<std::array<T, N>, N>& mat, std::array<T, N>& res){
	for(std::size_t i = 0; i < N; i++){
		for(std::size_t j = 0; j < N; j++){
			res[j] += mat[i][j] * vec[i];
		}
	}
}

template <typename T>
static void vecmat__vecmat4__dumb (benchmark::State& state){
	std::array<std::array<T, 4>, 4> mat = {
		T(1), T(2), T(3), T(4),
		T(5), T(6), T(7), T(8),
		T(9), T(10), T(11), T(12),
		T(13), T(14), T(15), T(16)
	};

	std::array<T, 4> vec = { T(1), T(2), T(3), T(4) };
	
	while(state.KeepRunning())
		vecmat_dumb(vec, mat, vec);
}

template <typename T>
static void vecmat__vecmat4__simd (benchmark::State& state){
	pgg::vec4<T> vec = { T(1), T(2), T(3), T(4) };

	pgg::mat4<T> mat = {
		T(1), T(2), T(3), T(4),
		T(5), T(6), T(7), T(8),
		T(9), T(10), T(11), T(12),
		T(13), T(14), T(15), T(16)
	};

	while(state.KeepRunning())
		pgg::mult4(vec, mat, vec);
}

template <typename T>
static void vecmat__vecmat4__glm (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}

template <typename T>
static void vecmat__vecmat3__dumb (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}

template <typename T>
static void vecmat__vecmat3__simd (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}

template <typename T>
static void vecmat__vecmat3__glm (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}