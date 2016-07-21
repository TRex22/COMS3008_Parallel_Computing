#!/bin/bash
g++ -fopenmp -std=c++11 AccessingMultiDimensionalArrays.cpp -o example1.out
g++ -fopenmp -std=c++11 DisplayOutputFromThreads.cpp -o example2.out
g++ -fopenmp -std=c++11 VectorDotProduct.cpp -o example3.out