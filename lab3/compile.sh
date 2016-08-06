#!/bin/bash
g++ -fopenmp 1.TrapezoidalSolver.cpp -o example1.out
g++ -fopenmp 2.MonteCarloTrapezoidalSimulation.cpp -o example2.out

g++ -fopenmp DataProcessor.cpp -o dataProcessor.out