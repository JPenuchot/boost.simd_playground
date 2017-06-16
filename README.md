# boost.simd_playground

This is just a public repo to keep an online backup of my work at the LRI. The roadmap is detailed [here](./TODO.md).

## Structure

The base type is located in jpenuchot/pvector.hpp, the algebric functions are then located in jpenuchot/algebra/*.hpp.

## Benchmarks

Benchmarks are fully automated and based on [Google Benchmark](https://github.com/google/benchmark). You'll have to install it first then place it in the main folder.

## Requirements

[boost.simd](https://github.com/numscale/boost.simd) is also required and must be placed in the main folder, as well as [libboost 1.64](http://www.boost.org/users/history/version_1_64_0.html).

## Install

You can place folders manually and compile Google Benchmark yourself, or you might want to simply run ```./prepare```.
