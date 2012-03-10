#!/bin/bash

mkdir -p ./build

cd ./build

cmake ..

make

cd ..

ln -s -f ./build/test/test_time ./test_time
