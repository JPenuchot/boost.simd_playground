#include <benchmark/benchmark_api.h>

#include <jpenuchot/parray.hpp>
#include <jpenuchot/pvector.hpp>

#include <cblas.h>

#ifndef BENCH_TYPE
	#define BENCH_TYPE float
#endif
using btype = BENCH_TYPE;

//	Function overloads (because cblas is very user friendly)

float openblas_dot(const int n, float* x, const int incx, float* y, const int incy)
{ return cblas_sdot(n, x, incx, y, incy); }

double openblas_dot(const int n, double* x, const int incx, double* y, const int incy)
{ return cblas_ddot(n, x, incx, y, incy); }

#define BM_DOT_PVECTOR_OPENBLAS(size) \
		static void dot__pvector__openblas__##size(benchmark::State& state) { \
			jp::pvector<btype> p((size)); \
			std::iota(p.begin(), p.end(), 0); \
			while(state.KeepRunning()){ \
				openblas_dot(size, p.data(), 1, p.data(), 1); \
				benchmark::DoNotOptimize(cblas_sdot); \
			} \
		} \
		BENCHMARK(dot__pvector__openblas__##size);
