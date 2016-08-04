#!/bin/bash
#n averageNumber incrementSize noIncrements writeFile? noThreads
mkdir results
./example1.out 1000 25 3000 250 1 4
./example2.out 1000 25 3000 250 1 4
./example3.out 1000 25 3000 250 1 4
./example4.out 1000 25 3000 250 1 4

#./dataProcessor.out
mkdir results/mine
./dataProcessor.out results/Example1.csv results/mine/Example1.csv 25
./dataProcessor.out results/Example2.csv results/mine/Example2.csv 25
./dataProcessor.out results/Example3.csv results/mine/Example3.csv 25
./dataProcessor.out results/Example4.csv results/mine/Example4.csv 25