#!/bin/bash
#n averageNumber incrementSize noIncrements writeFile? noThreads
mkdir results
./example1.out 1000 25 1000 500 1 4
./example2.out 1000 25 1000 500 1 4
./example3.out 1000 25 1000 500 1 4
./example4.out 1000 25 1000 500 1 4

#./dataProcessor.out
mkdir results/mine
./dataProcessor.out results/Example1.csv results/mine/Example1.csv 25
