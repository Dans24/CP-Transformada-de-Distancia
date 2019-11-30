#!/bin/bash
#
#PBS -N CP_project_parallel_wocollapse
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=40:r652
#PBS -qcpar

module load gcc/5.3.0

cd CP/Projeto/parallel/WOcollapse/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

THREADS="2 4 8 10 16 20 32 40 2 4 8 10 16 20 32 40"

for thread in $THREADS; do
	echo $thread
	export OMP_NUM_THREADS=$thread
	./exec ../imgTeste/gun.pbm ../imgResult/gunWOcollapse.pbm ../times/timegunWOcollapse.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digitalWOcollapse.pbm ../times/timedigitalWOcollapse.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemploWOcollapse.pbm ../times/timeexemploWOcollapse.txt
done