#include <benchmark/benchmark_api.h>

#include <playground/types/parray.hpp>
#include <playground/types/pvector.hpp>

#include <playground/algebra/dot/dot.hpp>

namespace pa = pg::algebra;

/*	====================
 *	ARRAY
 *	================= */

template <typename T, std::size_t size>
static void dot__parray__dumb (benchmark::State& state) {
	pg::parray<T, std::size_t(size)> p;
	std::iota(p.begin(), p.end(), 0);
	while(state.KeepRunning()){
		benchmark::DoNotOptimize(pa::dot_dumb(p, p));
	}
}

template <typename T, std::size_t size>
static void dot__parray__simd_inner (benchmark::State& state) {
	pg::parray<T, std::size_t(size)> p;
	std::iota(p.begin(), p.end(), 0);
	while(state.KeepRunning()){
		benchmark::DoNotOptimize(pa::dot_simd_inner(p, p));
	}
}

template <typename T, std::size_t size>
static void dot__parray__simd_full_unroll (benchmark::State& state) {
	pg::parray<T, std::size_t(size)> p;
	std::iota(p.begin(), p.end(), 0);
	while(state.KeepRunning()){
		benchmark::DoNotOptimize(pa::dot_simd_full_unroll(p, p));
	}
}	

template <typename T, std::size_t size>
static void dot__parray__simd_2_unrolls (benchmark::State& state) {
	pg::parray<T, std::size_t(size)> p;
	std::iota(p.begin(), p.end(), 0);
	while(state.KeepRunning()){
		benchmark::DoNotOptimize(pa::dot_simd_2_unrolls(p, p));
	}
}

template <typename T, std::size_t size>
static void dot__parray__simd (benchmark::State& state) {
	pg::parray<T, size> p;
	std::iota(p.begin(), p.end(), 0);
	while(state.KeepRunning()){
		benchmark::DoNotOptimize(pa::dot_simd(p, p));
	}
}

/*	====================
 *	VECTOR
 *	================= */

template <typename T, std::size_t size>
static void dot__pvector__dumb (benchmark::State& state) {
	pg::pvector<T> p(size);
	std::iota(p.begin(), p.end(), 0);
	while(state.KeepRunning()){
		benchmark::DoNotOptimize(pa::dot_dumb(p, p));
	}
}

template <typename T, std::size_t size>
static void dot__pvector__simd (benchmark::State& state) {
	pg::pvector<T> p(size);
	std::iota(p.begin(), p.end(), 0);
	while(state.KeepRunning()){
		benchmark::DoNotOptimize(pa::dot_simd(p, p));
	}
}

template <typename T, std::size_t size>
static void dot__pvector__simd_inner (benchmark::State& state) {
	pg::pvector<T> p(size);
	std::iota(p.begin(), p.end(), 0);
	while(state.KeepRunning()){
		benchmark::DoNotOptimize(pa::dot_simd_inner(p, p));
	}
}


//	TODO

//template <typename T, std::size_t size>
//static void dot__pvector__simd_##version## (benchmark::State& state) {
//	pg::pvector<T> p(size);
//	std::iota(p.begin(), p.end(), 0);
//	while(state.KeepRunning()){
//		benchmark::DoNotOptimize(pa::dot_simd_##version (p, p));
//	}
//}
