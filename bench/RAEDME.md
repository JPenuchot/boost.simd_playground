# Bench

This folder provides a set of tools to run benchmarks on different platforms automatically with automated plot (on the way).

Benchmark architectures and types (float/double) are defined in CMakeLists.txt whereas benchmark sizes are defined in src/main.cpp.

You can enable/disable benchmark by commenting them neatly in \[operation_name\]_select.hpp. Just don't break it or the compiler will puke at your face.