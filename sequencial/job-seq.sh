#!/bin/bash
#
#PBS -N CP_project_sequencial
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=40:r652
#PBS -qmei

module load gcc/5.3.0

cd CP/Projeto/sequencial/chunk/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

I="1 2 3 4 5 6 7 8"

for i in $I; do
	echo $i
	./exec ../imgTeste/gun.pbm ../imgResult/gun_chunk.pbm ../times/timegun_chunk.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digital_chunk.pbm ../times/timedigital_chunk.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo_chunk.pbm ../times/timeexemplo_chunk.txt
done

cd CP/Projeto/sequencial/chunkoptimized/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

I="1 2 3 4 5 6 7 8"

for i in $I; do
	echo $i
	./exec ../imgTeste/gun.pbm ../imgResult/gun_chunko.pbm ../times/timegun_chunko.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digital_chunko.pbm ../times/timedigital_chunko.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo_chunko.pbm ../times/timeexemplo_chunko.txt
done

cd CP/Projeto/sequencial/normal/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

I="1 2 3 4 5 6 7 8"

for i in $I; do
	echo $i
	./exec ../imgTeste/gun.pbm ../imgResult/gun_normal.pbm ../times/timegun_normal.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digital_normal.pbm ../times/timedigital_normal.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo_normal.pbm ../times/timeexemplo_normal.txt
done