#include <benchmark/benchmark_api.h>

#include <jpenuchot/parray.hpp>
#include <jpenuchot/pvector.hpp>
#include <jpenuchot/algebra/dot.hpp>
#include <jpenuchot/algebra/unsafe_dot.hpp>


#ifndef BENCH_TYPE
	#define BENCH_TYPE float
#endif
using btype = BENCH_TYPE;

namespace ja = jp::algebra;

/*	====================
 *	ARRAY
 *	================= */

#define BM_DOT_PARRAY_DUMB(size) \
		static void dot__parray__dumb__##size(benchmark::State& state) { \
			jp::parray<btype, std::size_t((size))> p; \
			std::iota(p.data.begin(), p.data.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(ja::dot_dumb(p, p)); \
			} \
		} \
		BENCHMARK(dot__parray__dumb__##size);

#define BM_DOT_PARRAY_SIMD_INNER(size) \
		static void dot__parray__simd_inner__##size(benchmark::State& state) { \
			jp::parray<btype, std::size_t((size))> p; \
			std::iota(p.data.begin(), p.data.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(ja::dot_inner(p, p)); \
			} \
		} \
		BENCHMARK(dot__parray__simd_inner__##size);

#define BM_DOT_PARRAY_SIMD_FU(size) \
	static void dot__parray__simd_full_unroll__##size(benchmark::State& state) { \
		jp::parray<btype, std::size_t((size))> p; \
		std::iota(p.data.begin(), p.data.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(ja::dot_simd_full_unroll(p, p)); \
		} \
	} \
	BENCHMARK(dot__parray__simd_full_unroll__##size);

#define BM_DOT_PARRAY_SIMD_2U(size) \
	static void dot__parray__simd_2_unrolls__##size(benchmark::State& state) { \
		jp::parray<btype, std::size_t((size))> p; \
		std::iota(p.data.begin(), p.data.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(ja::dot_simd_2_unrolls(p, p)); \
		} \
	} \
	BENCHMARK(dot__parray__simd_2_unrolls__##size);

#define BM_DOT_PARRAY_SIMD(size) \
	static void dot__parray__simd__##size(benchmark::State& state) { \
		constexpr auto sz = std::size_t((size)); \
		jp::parray<btype, sz> p; \
		std::iota(p.data.begin(), p.data.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(ja::dot_simd(p, p)); \
		} \
	} \
	BENCHMARK(dot__parray__simd__##size);

#define BM_DOT_PARRAY_SIMD_UNSAFE(size) \
	static void dot__parray__simd_unsafe__##size(benchmark::State& state) { \
		constexpr auto sz = std::size_t((size)); \
		jp::parray<btype, sz> p; \
		std::iota(p.data.begin(), p.data.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(ja::dot_simd(p.data, p.data)); \
		} \
	} \
	BENCHMARK(dot__parray__simd_unsafe__##size);

/*	====================
 *	VECTOR
 *	================= */

#define BM_DOT_PVECTOR_DUMB(size) \
		static void dot__pvector__dumb__##size(benchmark::State& state) { \
			jp::pvector<btype> p((size)); \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(ja::dot_dumb(p, p)); \
			} \
		} \
		BENCHMARK(dot__pvector__dumb__##size);

#define BM_DOT_PVECTOR_SIMD(size) \
		static void dot__pvector__simd__##size(benchmark::State& state) { \
			jp::pvector<btype> p((size)); \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(ja::dot_simd(p, p)); \
			} \
		} \
		BENCHMARK(dot__pvector__simd__##size);

#define BM_DOT_PVECTOR_SIMD_INNER(size) \
		static void dot__pvector__simd_inner__##size(benchmark::State& state) { \
			jp::pvector<btype> p((size)); \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(ja::dot_inner(p, p)); \
			} \
		} \
		BENCHMARK(dot__pvector__simd_inner__##size);

/*	====================
 *	GENERAL
 *	================= */

