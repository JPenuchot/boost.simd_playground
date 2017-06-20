#include <benchmark/benchmark_api.h>

#include <boost/array.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/pack.hpp>

#include <jpenuchot/parray.hpp>
#include <jpenuchot/pvector.hpp>
#include <jpenuchot/algebra/unsafe_dot.hpp>

#include <vector>
#include <array>
#include <numeric>
#include <memory>

#ifndef BENCH_TYPE
	#define BENCH_TYPE float
#endif
using btype = BENCH_TYPE;

namespace ja = jp::algebra;

#define BM_ARRAY(size) \
static void BM_dot_array_##size(benchmark::State& state) { \
	alignas(boost::simd::pack<btype>::alignment) std::array<btype, (size)> arr; \
	std::iota(arr.begin(), arr.end(), 0.f); \
	while(state.KeepRunning()){ \
		benchmark::DoNotOptimize(arr_dot(arr, arr)); \
	} \
} \
BENCHMARK(BM_dot_array_##size);

#define BM_ARRAY_SIMD(size) \
static void BM_dot_array_simd_##size(benchmark::State& state) { \
	alignas(boost::simd::pack<btype>::alignment) std::array<btype, (size)> arr; \
	std::iota(arr.begin(), arr.end(), 0.f); \
	while(state.KeepRunning()){ \
		benchmark::DoNotOptimize(ja::dot_simd(arr, arr)); \
	} \
} \
BENCHMARK(BM_dot_array_simd_##size);

#define BM_VECTOR(size) \
static void BM_dot_vector_##size(benchmark::State& state) { \
	std::vector<btype, boost::simd::allocator<btype>> arr( (size) ); \
	std::iota(arr.begin(), arr.end(), 0.f); \
	while(state.KeepRunning()){ \
		benchmark::DoNotOptimize(vec_dot(arr, arr)); \
	} \
} \
BENCHMARK(BM_dot_vector_##size);

template<typename T>
T vec_dot(std::vector<T, boost::simd::allocator<btype>>& a, std::vector<T, boost::simd::allocator<btype>>& b){
    auto a_first = a.data();
    auto b_first = b.data();

    auto a_last = a_first + a.size();

    auto res = T(0);

    for(; a_first != a_last; a_first++, b_first++){ res += *a_first * *b_first; }

	return res;
}

template<std::size_t N, typename T>
T arr_dot(std::array<T, N>& a, std::array<T, N>& b){
    auto a_first = a.data();
    auto b_first = b.data();

    auto a_last = a_first + a.size();

    auto res = T(0);

    for(; a_first != a_last; a_first++, b_first++){ res += *a_first * *b_first; }

	return res;
}

#define BM_VEC_VS_ARR(size) \
	BM_VECTOR(size) \
	BM_ARRAY_SIMD(size) \
	BM_ARRAY(size)

BM_VEC_VS_ARR(10)
BM_VEC_VS_ARR(16)
BM_VEC_VS_ARR(32)
BM_VEC_VS_ARR(100)
BM_VEC_VS_ARR(128)
BM_VEC_VS_ARR(512)
BM_VEC_VS_ARR(1000)
BM_VEC_VS_ARR(1024)
BM_VEC_VS_ARR(4096)
BM_VEC_VS_ARR(16384)
