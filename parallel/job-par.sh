#!/bin/bash
#
#PBS -N CP_project_parallel
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=40:r652
#PBS -qmei

module load gcc/5.3.0

cd CP/Projeto/parallel/ChunkOptimizedGuided/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

THREADS="1 2 4 8 10 16 20 32 40"

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../imgResult/gunChunkOGuided.pbm ../times/ChunkOptimizedGuided/timegun.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digitalChunkOGuided.pbm ../times/ChunkOptimizedGuided/timedigital.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemploChunkOGuided.pbm ../times/ChunkOptimizedGuided/timeexemplo.txt
done

cd ../ChunkOptimizedDynamic/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../imgResult/gunChunkODynamic.pbm ../times/ChunkOptimizedDynamic/timegun.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digitalChunkODynamic.pbm ../times/ChunkOptimizedDynamic/timedigital.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemploChunkODynamic.pbm ../times/ChunkOptimizedDynamic/timeexemplo.txt
done

cd ../ChunkGuided/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../imgResult/gunChunkGuided.pbm ../times/ChunkGuided/timegun.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digitalChunkGuided.pbm ../times/ChunkGuided/timedigital.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemploChunkGuided.pbm ../times/ChunkGuided/timeexemplo.txt
done

cd ../ChunkDynamic/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../imgResult/gunChunkDynamic.pbm ../times/ChunkDynamic/timegun.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digitalChunkDynamic.pbm ../times/ChunkDynamic/timedigital.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemploChunkDynamic.pbm ../times/ChunkDynamic/timeexemplo.txt
done

cd ../WOcollapse/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../imgResult/gunWOcollapse.pbm ../times/WOcollapse/timegun.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digitalWOcollapse.pbm ../times/WOcollapse/timedigital.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemploWOcollapse.pbm ../times/WOcollapse/timeexemplo.txt
done

cd ../Wcollapse/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../imgResult/gunWcollapse.pbm ../times/Wcollapse/timegun.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digitalWcollapse.pbm ../times/Wcollapse/timedigital.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemploWcollapse.pbm ../times/Wcollapse/timeexemplo.txt
done