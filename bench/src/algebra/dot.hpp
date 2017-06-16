#include <benchmark/benchmark_api.h>

#include <jpenuchot/pvector.hpp>
#include <jpenuchot/algebra/dot.hpp>


#ifndef BENCH_TYPE
	using mytype = float;
#else
	using mytype = BENCH_TYPE;
#endif

#ifndef BENCH_SIZE
	const unsigned int size = 4;
#else
	const unsigned int size = BENCH_SIZE;
#endif

namespace ja = jp::algebra;

static void BM_dot_dumb(benchmark::State& state) {
	jp::pvector<mytype, std::size_t(16 * size)> p;
	std::iota(p.data.begin(), p.data.end(), 0);

	while(state.KeepRunning()){
		benchmark::DoNotOptimize(ja::dot_dumb(p, p));
	}
}
BENCHMARK(BM_dot_dumb);

static void BM_dot_simd_full_unroll(benchmark::State& state) {
	jp::pvector<mytype, std::size_t(16 * size)> p;
	std::iota(p.data.begin(), p.data.end(), 0);

	while(state.KeepRunning()){
		benchmark::DoNotOptimize(ja::dot_simd_full_unroll(p, p));
	}
}
BENCHMARK(BM_dot_simd_full_unroll);

static void BM_dot_simd_2_unrolls(benchmark::State& state) {
	jp::pvector<mytype, std::size_t(16 * size)> p;
	std::iota(p.data.begin(), p.data.end(), 0);

	while(state.KeepRunning()){
		benchmark::DoNotOptimize(ja::dot_simd_2_unrolls(p, p));
	}
}
BENCHMARK(BM_dot_simd_2_unrolls);

static void BM_dot_simd_1_unroll(benchmark::State& state) {
	jp::pvector<mytype, std::size_t(16 * size)> p;
	std::iota(p.data.begin(), p.data.end(), 0);

	while(state.KeepRunning()){
		benchmark::DoNotOptimize(ja::dot_simd_1_unroll(p, p));
	}
}
BENCHMARK(BM_dot_simd_1_unroll);