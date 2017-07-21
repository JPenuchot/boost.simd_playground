# boost.simd_playground

Meta-project for my work at the LRI. Everything I've been working on lately is available on other repositories :

-	[boost.simd_linalgebra](https://github.com/jpenuchot/boost.simd_linalgebra) : Basic linear algebra kernels for performance comparison with OpenBLAS and Intel MKL
-	[boost.simd_graphics](https://github.com/jpenuchot/boost.simd_graphics) : Basic 3D graphics library for performance comparison with GLM

You'll also find my dev blog about the project [here](http://www.penuch.it/boost.simd_playground/), which is basically a compilation of benchmarks, insights and remarks about [boost.simd](https://github.com/NumScale/boost.simd) (might be out-of-date).

## Featured work

The goal of that internship is to make high-performance code fully written in C++ relying on boost.simd to make SIMD optimized computing kernels and compare their performance with state of the art libraries written using custom assembly or regular SIMD intrinsics. Every piece of code written here will fully support the platform you compile it for, as long as boost.simd supports it.

For now, every project I worked on during this internship proved that well-written, generic C++ code can be as good as or even better than custom ASM/C++ code for every architecture.

![](./boostsimd-floor-is.jpg)
