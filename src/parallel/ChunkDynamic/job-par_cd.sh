#!/bin/bash
#
#PBS -N CP_project_parallel_chunkdynamic
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=40:r652
#PBS -qmei

module load gcc/5.3.0

cd CP/Projeto/parallel/ChunkDynamic/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

THREADS="1 2 4 8 10 16 20 32 40 1 2 4 8 10 16 20 32 40 1 2 4 8 10 16 20 32 40 1 2 4 8 10 16 20 32 40"

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../imgResult/gunChunkDynamic.pbm ../times/ChunkDynamic/timegun.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digitalChunkDynamic.pbm ../times/ChunkDynamic/timedigital.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemploChunkDynamic.pbm ../times/ChunkDynamic/timeexemplo.txt
done