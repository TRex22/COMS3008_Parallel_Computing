#!/bin/bash
g++ -fopenmp 1.lab2_seqential_factorial.cpp -o example1.out
g++ -fopenmp 2.lab2_recursive_factorial.cpp -o example2.out
g++ -fopenmp 3.lab2_parallel_seqential_factorial.cpp -o example3.out
g++ -fopenmp 4.lab2_parallel_recursive_factorial.cpp -o example4.out

g++ -fopenmp DataProcessor.cpp -o dataProcessor.out