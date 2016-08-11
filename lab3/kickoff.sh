#!/bin/bash
mkdir results
#initThreads initialPartitions blockSize noIncrements incrementSize writeFile?
./example1.out 1 10 1 1000000 100 1
#initThread particleCount blockSize noIncrements incrementSize writeFile?
./example2.out 1 10 1 1000000 100 1

#./dataProcessor.out
mkdir results/mine
#./dataProcessor.out results/Example1.csv results/mine/Example1.csv 25 colNo colName <colNo is computer ranked ie 0 first>
./dataProcessor.out results/Exmaple2_.csv 