#!/bin/bash

./example1.out
./example2.out
./example3.out

#Example 1 data process
./dataProcessor.out results/Example1_col.csv results/mine/Example1_col_avg.csv 50
./dataProcessor.out results/Example1_row.csv results/mine/Example1_col_avg.csv 50

#Example 2 data process
./dataProcessor.out results/Example3_1_VaryNoThreads_FixedArraySize.csv results/mine/Example3_1_VaryNoThreads_FixedArraySize_avg.csv 50
./dataProcessor.out results/Example3_2_VaryArraySize_FixedThreadCount4.csv results/mine/Example3_2_VaryArraySize_FixedThreadCount4_avg.csv 50
./dataProcessor.out results/Example3_3_RND_Parallel_VaryThreads.csv results/mine/Example3_3_RND_Parallel_VaryThreads_avg.csv 50
./dataProcessor.out results/Example3_4_RND_Parallel_VaryArraySize.csv results/mine/Example3_4_RND_Parallel_VaryArraySize_avg.csv 50