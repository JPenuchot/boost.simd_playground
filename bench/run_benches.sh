#!/bin/bash

## Managing default directories, args etc...

ORIGIN=$(pwd)

DEFAULT_CMAKE_BUILD_DIR=".build"
DEFAULT_BIN_DIR="bin"
DEFAULT_OUTPUT_DIR="output"

CMAKE_BUILD_DIR=$1
BIN_DIR=$2
OUTPUT_DIR=$3

if [ -z "$CMAKE_BUILD_DIR" ]; then
	CMAKE_BUILD_DIR=${DEFAULT_CMAKE_BUILD_DIR}
fi

if [ -z "$BIN_DIR" ]; then
	BIN_DIR=${DEFAULT_BIN_DIR}
fi

if [ -z "$OUTPUT_DIR" ]; then
	OUTPUT_DIR=${DEFAULT_OUTPUT_DIR}
fi

## Ensuring output folder exists

if [ ! -d "$OUTPUT_DIR" ]; then
  mkdir ${OUTPUT_DIR}
fi

## Build everything

./build.sh ${CMAKE_BUILD_DIR} ${BIN_DIR}

## Run benchmarks

echo
echo "-= IT'S BENCH TIME =-"
echo

EXEC_LIST=$(ls ${BIN_DIR})

for BENCH_EXEC in ${EXEC_LIST}; do
	echo "Running ${BENCH_EXEC}..."
	echo
	#${BIN_DIR}/${BENCH_EXEC} --benchmark_out_format=json --benchmark_out=${OUTPUT_DIR}/${BENCH_EXEC}_report.json | tee ${OUTPUT_DIR}/${BENCH_EXEC}_output.txt
	${BIN_DIR}/${BENCH_EXEC} --benchmark_report_aggregates_only=true --benchmark_repetitions=10 --benchmark_out_format=json --benchmark_out=${OUTPUT_DIR}/${BENCH_EXEC}_report.json | tee ${OUTPUT_DIR}/${BENCH_EXEC}_output.txt
	./tools/json_to_plot.js ${OUTPUT_DIR}/${BENCH_EXEC}_report.json ${OUTPUT_DIR}/${BENCH_EXEC}_graph # &> /dev/null
done