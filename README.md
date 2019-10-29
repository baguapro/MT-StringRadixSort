Table of Contents
=================

* [Table of Contents](#table-of-contents)
* [Algorithm development and analysis with RadixSort](#algorithm-development-and-analysis-with-radixsort)
  * [Introduction](#introduction)
  * [License](#license)
  * [Test.](#test)
  * [Benchmark](#benchmark)
  * [Analysis](#analysis)
    

# Algorithm development and analysis with RadixSort

## Introduction
Code to go with the series of blog posts (https://themindseye.io) looking at the processes in developing and analysing a simpile sorting algorithm in modern C++

## License
All code in this repository is licensed under the terms of the MIT license, see LICENSE.md for details

## Test.
To build the test go in the test directory and run:

```
mkdir build
cd build
cmake ..
make run_tests
```
The tests require googletest and the make process will download and build the googletest library as part of the test build and run process.

## Benchmark
To build and run the benchmarks go to the benchmarks directory and run:

```
mkdir build
cd build
cmake ..
make run_benchmarks
```
The benchamrking requires google benchmark the make process will download and build the google benchmark library as part of the build process

## Analysis
