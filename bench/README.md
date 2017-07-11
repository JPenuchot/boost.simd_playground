# Bench

This folder provides a set of tools to run benchmarks on different platforms automatically with automated plot.

Benchmark architectures are defined in the CMakeLists.txt file, the rest is contained in the C++ code under `src/[CATEGORY]/[LIBRARY]/*.hpp` where def.hpp files are where benchmark code is defined whereas select.hpp is where benches are enabled/disabled.

## Writing benches

After a re-design, benches have been updated and now use templates rather than macros. Naming convention is now : `[category]__[data structure]__[method]` with a template that starts with a typename.

## Automatic plotting

##### Warning : Recent changes broke automatic plotting, don't be scared if you get scary error messages when using `run_benches`

Install "plotter" using npm, make sure gnuplot is installed on your machine and you're ready to go. Benchmark graphs are generated automatically with ```run_benches```.
