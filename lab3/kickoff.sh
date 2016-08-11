#!/bin/bash
mkdir results
#initThreads initialPartitions blockSize noIncrements incrementSize writeFile?
./example1.out 1 10 1 1000000 10 1
#initThread particleCount blockSize noIncrements incrementSize writeFile?
./example2.out 1000 25 1000 500 1 4

#./dataProcessor.out
#mkdir results/mine
#./dataProcessor.out results/Example1.csv results/mine/Example1.csv 25
