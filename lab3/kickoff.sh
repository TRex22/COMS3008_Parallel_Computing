#!/bin/bash
mkdir results
#initThreads maxThreads initialPartitions blockSize noIncrements incrementSize writeFile?
./example1.out 1 26000 1 1 261 100 1
#initThread maxThreads particleCount blockSize noIncrements incrementSize writeFile?
./example2.out 1 26000 1000 1 260 1000 1

#./dataProcessor.out
#mkdir results/mine
#./dataProcessor.out results/Example1.csv results/mine/Example1.csv 25 colNo colName <colNo is computer ranked ie 0 first>
#./dataProcessor.out results/Example2_parallel_particles.csv results/mine/Example2_parallel_particles_approx.csv 5 1 NoParticles
#./dataProcessor.out results/Example2_parallel_particles.csv results/mine/Example2_parallel_particles_time.csv 5 2 NoParticles
#./dataProcessor.out results/Example2_parallel_particles.csv results/mine/Example2_parallel_particles_error.csv 5 3 NoParticles
#abs error 4

#./dataProcessor.out results/Example2_parallel_threads.csv results/mine/Example2_parallel_threads_approx.csv 5 1 NoThreads
#./dataProcessor.out results/Example2_parallel_threads.csv results/mine/Example2_parallel_threads_time.csv 5 2 NoThreads
#./dataProcessor.out results/Example2_parallel_threads.csv results/mine/Example2_parallel_threads_error.csv 5 3 NoThreads

#./dataProcessor.out results/Example2_serial.csv results/mine/Example2_serial_approx.csv 5 1 NoParticles
#./dataProcessor.out results/Example2_serial.csv results/mine/Example2_serial_time.csv 5 2 NoParticles
#./dataProcessor.out results/Example2_serial.csv results/mine/Example2_serial_error.csv 5 3 NoParticles




