#include <benchmark/benchmark_api.h>

#include <jpenuchot/pvector.hpp>
#include <jpenuchot/algebra/dot.hpp>


#ifndef BENCH_TYPE
	#define BENCH_TYPE float
#endif
using btype = BENCH_TYPE;

namespace ja = jp::algebra;

#define BM_DOT_DUMB(size) \
		static void BM_dot_dumb_##size(benchmark::State& state) { \
			jp::pvector<btype, std::size_t(16 * (size))> p; \
			std::iota(p.data.begin(), p.data.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(ja::dot_dumb(p, p)); \
			} \
		} \
		BENCHMARK(BM_dot_dumb_##size);

#define BM_DOT_SIMD_FU(size) \
	static void BM_dot_simd_full_unroll_##size(benchmark::State& state) { \
		jp::pvector<btype, std::size_t(16 * (size))> p; \
		std::iota(p.data.begin(), p.data.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(ja::dot_simd_full_unroll(p, p)); \
		} \
	} \
	BENCHMARK(BM_dot_simd_full_unroll_##size);

#define BM_DOT_SIMD_2U(size) \
	static void BM_dot_simd_2_unrolls_##size(benchmark::State& state) { \
		jp::pvector<btype, std::size_t(16 * (size))> p; \
		std::iota(p.data.begin(), p.data.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(ja::dot_simd_2_unrolls(p, p)); \
		} \
	} \
	BENCHMARK(BM_dot_simd_2_unrolls_##size);

#define BM_DOT_SIMD_1U(size) \
	static void BM_dot_simd_1_unroll_##size(benchmark::State& state) { \
		jp::pvector<btype, std::size_t(16 * (size))> p; \
		std::iota(p.data.begin(), p.data.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(ja::dot_simd_1_unroll(p, p)); \
		} \
	} \
	BENCHMARK(BM_dot_simd_1_unroll_##size);


#define BM_DOT(size) \
	BM_DOT_DUMB(size) \
	BM_DOT_SIMD_FU(size) \
	BM_DOT_SIMD_2U(size) \
	BM_DOT_SIMD_1U(size)


BM_DOT(10)
BM_DOT(16)
BM_DOT(32)
BM_DOT(100)
BM_DOT(128)
BM_DOT(512)
BM_DOT(1000)
BM_DOT(1024)
BM_DOT(4096)
BM_DOT(16384)
