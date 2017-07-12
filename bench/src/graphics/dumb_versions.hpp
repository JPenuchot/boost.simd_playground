#pragma once

#include <array>
#include <numeric>

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
inline void vecmat_dumb(std::array<T, N>&vec, std::array<std::array<T, N>, N>& mat, std::array<T, N>& res){
	for(std::size_t i = 0; i < N; i++)
	for(std::size_t j = 0; j < N; j++)
		res[j] += mat[i][j] * vec[i];
}

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
inline void matvec_dumb(std::array<std::array<T, N>, N>& mat, std::array<T, N>&vec, std::array<T, N>& res){
	for(std::size_t i = 0; i < N; i++)
		res[i] = std::inner_product(vec.begin(), vec.end(), mat[i].begin(), T(0));
}