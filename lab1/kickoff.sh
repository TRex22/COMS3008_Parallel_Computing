#!/bin/bash

./example1.out
./example2.out
./example3.out

./dataProcessor.out results/Example1_col.csv results/mine/Example1_col_avg.csv 50
./dataProcessor.out results/Example1_row.csv results/mine/Example1_col_avg.csv 50