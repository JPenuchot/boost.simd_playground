#include <benchmark/benchmark.h>

#include <array>
#include <numeric>

#include <playground/graphics/mat4x4.hpp>
#include <playground/graphics/mat3x3.hpp>

#include <playground/graphics/vec3.hpp>
#include <playground/graphics/vec4.hpp>

namespace pgg = pg::graphics;

/**
 * @brief      Dumb reference for matvec product
 *
 * @param      mat   The matrix
 * @param      vec   The vector
 * @param      res   The result
 *
 * @tparam     T     Type
 * @tparam     N     Size
 */
template <typename T, std::size_t N>
void matvec_dumb(std::array<std::array<T, N>, N>& mat, std::array<T, N>&vec, std::array<T, N>& res){
	for(std::size_t i = 0; i < N; i++)
		res[i] = std::inner_product(vec.begin(), vec.end(), mat[i].begin(), T(0));
}


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
static void matvec__matvec4__dumb (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}

template <typename T>
static void matvec__matvec4__simd (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}

template <typename T>
static void matvec__matvec4__glm (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}

template <typename T>
static void matvec__matvec3__dumb (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}

template <typename T>
static void matvec__matvec3__simd (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}

template <typename T>
static void matvec__matvec3__glm (benchmark::State& state){
	//	Prepare
	while(state.KeepRunning()){
		//	Run
	}
}