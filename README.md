# boost.simd_playground

This is just a public repo to keep an online backup of my work at the LRI. The roadmap is detailed [here](./TODO.md).

## Structure

The base type is located in jpenuchot/pvector.hpp, the algebric functions are then located in jpenuchot/algebra/*.hpp.

## Benchmarks

Benchmarks are fully automated and based on [Google Benchmark](https://github.com/google/benchmark). You'll have to install it first then place it in the main folder.

[boost.simd](https://github.com/numscale/boost.simd) is also required and must be placed in the main folder, as well as [libboost 1.64](http://www.boost.org/users/history/version_1_64_0.html).

You might want to simply run :

```./prepare```

or

```bash
git clone https://github.com/numscale/boost.simd
git clone https://github.com/google/benchmark
cd benchmark
sudo make install
cd ..
wget https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
tar xvf boost_1_64_0.tar.gz
rm boost_1_64_0.tar.gz
```