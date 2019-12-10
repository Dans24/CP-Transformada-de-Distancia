#!/bin/bash
#
#PBS -N CP_project_sequencial_chunk
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=40:r652
#PBS -qmei

module load gcc/5.3.0

cd CP/Projeto/sequencial/Chunk/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

I="1 2 3 4 5 6 7 8"

for i in $I; do
	echo $i
	./exec ../imgTeste/gun.pbm ../imgResult/gun_chunk.pbm ../times/Chunk/timegun.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digital_chunk.pbm ../times/Chunk/timedigital.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo_chunk.pbm ../times/Chunk/timeexemplo.txt
done