#include <benchmark/benchmark_api.h>

#include <playground/types/parray.hpp>
#include <playground/types/pvector.hpp>

#include <playground/algebra/dot/dot.hpp>

#ifdef BENCH_DOUBLE
	using btype = double;
#else
	using btype = float;
#endif

namespace pa = pg::algebra;

/*	====================
 *	ARRAY
 *	================= */

#define BM_DOT_PARRAY_DUMB(size) \
		static void dot__parray__dumb__ ##size (benchmark::State& state) { \
			pg::parray<btype, std::size_t((size))> p; \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(pa::dot_dumb(p, p)); \
			} \
		} \
		BENCHMARK(dot__parray__dumb__ ##size );

#define BM_DOT_PARRAY_SIMD_INNER(size) \
		static void dot__parray__simd_inner__ ##size (benchmark::State& state) { \
			pg::parray<btype, std::size_t((size))> p; \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(pa::dot_simd_inner(p, p)); \
			} \
		} \
		BENCHMARK(dot__parray__simd_inner__ ##size );

#define BM_DOT_PARRAY_SIMD_FU(size) \
	static void dot__parray__simd_full_unroll__ ##size (benchmark::State& state) { \
		pg::parray<btype, std::size_t((size))> p; \
		std::iota(p.begin(), p.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(pa::dot_simd_full_unroll(p, p)); \
		} \
	} \
	BENCHMARK(dot__parray__simd_full_unroll__ ##size );

#define BM_DOT_PARRAY_SIMD_2U(size) \
	static void dot__parray__simd_2_unrolls__ ##size (benchmark::State& state) { \
		pg::parray<btype, std::size_t((size))> p; \
		std::iota(p.begin(), p.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(pa::dot_simd_2_unrolls(p, p)); \
		} \
	} \
	BENCHMARK(dot__parray__simd_2_unrolls__ ##size );

#define BM_DOT_PARRAY_SIMD(size) \
	static void dot__parray__simd__ ##size (benchmark::State& state) { \
		constexpr auto sz = std::size_t((size)); \
		pg::parray<btype, sz> p; \
		std::iota(p.begin(), p.end(), 0); \
		while(state.KeepRunning()){ \
			benchmark::DoNotOptimize(pa::dot_simd(p, p)); \
		} \
	} \
	BENCHMARK(dot__parray__simd__ ##size );

/*	====================
 *	VECTOR
 *	================= */

#define BM_DOT_PVECTOR_DUMB(size) \
		static void dot__pvector__dumb__ ##size (benchmark::State& state) { \
			pg::pvector<btype> p((size)); \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(pa::dot_dumb(p, p)); \
			} \
		} \
		BENCHMARK(dot__pvector__dumb__ ##size );

#define BM_DOT_PVECTOR_SIMD(size) \
		static void dot__pvector__simd__ ##size (benchmark::State& state) { \
			pg::pvector<btype> p((size)); \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(pa::dot_simd(p, p)); \
			} \
		} \
		BENCHMARK(dot__pvector__simd__ ##size );

#define BM_DOT_PVECTOR_SIMD_INNER(size) \
		static void dot__pvector__simd_inner__ ##size (benchmark::State& state) { \
			pg::pvector<btype> p((size)); \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(pa::dot_simd_inner(p, p)); \
			} \
		} \
		BENCHMARK(dot__pvector__simd_inner__ ##size );

#define BM_DOT_PVECTOR_SIMD_VERSION(size, version) \
		static void dot__pvector__simd_##version##__##size (benchmark::State& state) { \
			pg::pvector<btype> p((size)); \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				benchmark::DoNotOptimize(pa::dot_simd_##version (p, p)); \
			} \
		} \
		BENCHMARK( dot__pvector__simd_##version##__##size );
