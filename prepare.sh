#!/bin/bash

ORIGIN=$(pwd)

EXTLIB_FOLDER="ext/"

echo

echo -n "WARNING : This will install Google Benchmark in your /usr/local/lib folder, are you sure you want to continue ? [y/n] : "
read ANS

while [ ! "$ANS" = 'y' ] && [ ! "$ANS" = 'n' ]; do
	echo
	echo -n "[y/n] : "
	read ANS
done

if [ "$ANS" = 'n' ]; then
	exit
fi

echo

## Preparing external lib folder

if [ ! -d "${EXTLIB_FOLDER}" ]; then
 	mkdir ${EXTLIB_FOLDER}
else
	rm -rf ${EXTLIB_FOLDER}
	mkdir ${EXTLIB_FOLDER}
fi
cd ${EXTLIB_FOLDER}

# boost.simd

git clone https://github.com/numscale/boost.simd

# glm

git clone https://github.com/g-truc/glm/


# boost 1.64.0

wget https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
tar xf boost_1_64_0.tar.gz
rm boost_1_64_0.tar.gz

# gbenchmark

git clone https://github.com/google/benchmark
cd benchmark
mkdir .build
cd .build
cmake ..
sudo make install
cd ..
rm -rf .build
cd ..

# OpenBLAS

git clone https://github.com/xianyi/OpenBLAS
cd OpenBLAS
make
make install PREFIX=./

cd ${ORIGIN}

# fast-asm-compare

git clone https://github.com/jpenuchot/fast-asm-compare
cd fast-asm-compare/ext
ln -s ../../ext/* .
cd ../
ln -s ../examples/compare/* .
