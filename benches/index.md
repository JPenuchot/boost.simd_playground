# [~devblog](../)/benches

There you have some benchmark comparisons between "dumb" methods (No SIMD optimization) and the other ones : using SIMD inner product with boost.simd's ```segmented_aligned_range``` and a manually unrolled one (That is not optimized for small sizes... Yet).

Units :

- Time in nanoseconds
- Bench size in number of elements

Specs :

- Dell XPS 9350
- Intel(R) Core(TM) i7-6560U CPU @ 2.20GHz

## AVX - double

![](./images/bench_avx_double_graph_dot.svg)

## AVX float

![](./images/bench_avx_float_graph_dot.svg)

## SSE 4.2 - double

![](./images/bench_sse4.2_double_graph_dot.svg)

## SSE 4.2 - float

![](./images/bench_sse4.2_float_graph_dot.svg)
