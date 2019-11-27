#!/bin/bash
#
#PBS -N parallel
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=40:r652
#PBS -qcpar mei

module load gcc/7.1.0

cd CP/Projeto/parallel/ChunkOptimized/

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec
gcc -std=c99 run.c -o run

THREADS="1 2 4 8 16 32 20 40"

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./run
done