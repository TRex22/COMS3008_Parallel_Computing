#!/bin/bash
g++ -fopenmp 1.AccessingMultiDimensionalArrays.cpp -o example1.out
g++ -fopenmp 2.DisplayOutputFromThreads.cpp -o example2.out
g++ -fopenmp 3.VectorDotProduct.cpp -o example3.out

g++ -fopenmp DataProcessor.cpp -o dataProcessor.out
