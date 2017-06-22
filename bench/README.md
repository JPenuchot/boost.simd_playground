# Bench

This folder provides a set of tools to run benchmarks on different platforms automatically with automated plot (on the way).

Benchmark architectures and types (float/double) are defined in CMakeLists.txt whereas benchmark sizes are defined in src/main.cpp.

You can enable/disable benchmark by commenting them neatly in \[operation_name\]_select.hpp. Just don't break it or the compiler will puke at your face.

## Writing benches

All benches must bee written following the same rules :

- Code is generated using macros that accept a "size" parameter
- Benchmark function names must be formatted as ```[operation]__[type]__[method]__##size```
- Macro name must be formatted as ```BM_[operation]_[type]_[method]```

Be careful to respect the function name formatting as it will then be parsed according to this format.

## Automatic plotting

Because why the hell not ?

Install "plotter" using npm, make sure gnuplot is installed on your machine and you're ready to go. Benchmark graphs are generated automatically with ```run_benches```.