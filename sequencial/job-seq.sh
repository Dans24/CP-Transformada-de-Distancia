#!/bin/bash
#
#PBS -N parallel
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=1:r652
#PBS -qcpar mei

module load gcc/7.1.0

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec
gcc -std=c99 run.c -o run

./run