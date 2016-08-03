#!/bin/bash
#n averageNumber incrementSize noIncrements writeFile?
mkdir results
./example1.out 100 50 100 100 1
./example2.out 100 50 100 100 1
./example3.out 100 50 100 100 1
./example4.out 100 50 100 100 1

#./dataProcessor.out
mkdir results/mine
./dataProcessor.out results/Example1.csv results/mine/Example1.csv 50
./dataProcessor.out results/Example2.csv results/mine/Example2.csv 50
./dataProcessor.out results/Example3.csv results/mine/Example3.csv 50
./dataProcessor.out results/Example4.csv results/mine/Example4.csv 50