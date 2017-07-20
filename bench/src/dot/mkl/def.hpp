#include <benchmark/benchmark.h>

#include <playground/parray.hpp>
#include <playground/pvector.hpp>

#include <numeric>

#include <mkl.h>

float mkl_dot(const int n, float* x, const int incx, float* y, const int incy)
{ return cblas_sdot(n, x, incx, y, incy); }

double mkl_dot(const int n, double* x, const int incx, double* y, const int incy)
{ return cblas_ddot(n, x, incx, y, incy); }


template <typename T, std::size_t size>
static void dot__pvector__mkl(benchmark::State& state) {
	pg::pvector<T> p(size);
	std::iota(p.begin(), p.end(), 0);
	while(state.KeepRunning())
		benchmark::DoNotOptimize(mkl_dot(size, p.data(), 1, p.data(), 1));
}
