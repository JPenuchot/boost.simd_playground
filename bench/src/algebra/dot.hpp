#include <jpenuchot/pvector.hpp>

#include <jpenuchot/algebra/dot.hpp>

namespace ja = jp::algebra;

static void BM_dot_dumb(benchmark::State& state) {
	while(state.KeepRunning()){
		//	Fill vectors
		state.PauseTiming();

		jp::pvector<float, 8 << 8> pvec;
		std::iota(pvec.data.begin(), pvec.data.end(), 0);

		//	Compute
		state.ResumeTiming();

		float res = ja::dot_dumb(pvec, pvec);
	}
}
BENCHMARK(BM_dot_dumb);

static void BM_dot_simd(benchmark::State& state) {
	while(state.KeepRunning()){
		//	Fill vectors
		state.PauseTiming();

		jp::pvector<float, 8 << 8> pvec;
		std::iota(pvec.data.begin(), pvec.data.end(), 0);

		//	Compute
		state.ResumeTiming();

		float res = ja::dot_simd(pvec, pvec);
	}
}
BENCHMARK(BM_dot_simd);