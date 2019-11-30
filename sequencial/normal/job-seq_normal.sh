#!/bin/bash
#
#PBS -N CP_project_sequencial_normal
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=1:r652
#PBS -qcpar

module load gcc/5.3.0

cd CP/Projeto/sequencial/normal/

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

I="1 2 3 4 5 6 7 8"

for i in $I; do
	echo $i
	./exec ../imgTeste/gun.pbm ../imgResult/gun_normal.pbm ../times/timegun_normal.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digital_normal.pbm ../times/timedigital_normal.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo_normal.pbm ../times/timeexemplo_normal.txt
done