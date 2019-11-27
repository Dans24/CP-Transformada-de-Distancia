#!/bin/bash
#
#PBS -N parallel
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=40:r652
#PBS -qcpar mei

module load gcc/7.1.0

cd CP/Projeto/parallel/ChunkOptimized/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

THREADS="2 4 8 10 16 20 32 40"

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../times/timegunCOptimized.txt
	./exec ../imgTeste/digital.pbm ../times/timedigitalCOptimized.txt
	./exec ../imgTeste/exemplo.pbm ../times/timeexemploCOptimized.txt
done

cd ..

cd Chunk/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../times/timegunChunk.txt
	./exec ../imgTeste/digital.pbm ../times/timedigitalChunk.txt
	./exec ../imgTeste/exemplo.pbm ../times/timeexemploChunk.txt
done

cd ..

cd WOcollapse/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../times/timegunWOcollapse.txt
	./exec ../imgTeste/digital.pbm ../times/timedigitalWOcollapse.txt
	./exec ../imgTeste/exemplo.pbm ../times/timeexemploWOcollapse.txt
done

cd ..

cd Wcollapse/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../times/timegunWcollapse.txt
	./exec ../imgTeste/digital.pbm ../times/timedigitalWcollapse.txt
	./exec ../imgTeste/exemplo.pbm ../times/timeexemploWcollapse.txt
done