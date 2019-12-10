#!/bin/bash
#
#PBS -N CP_project_sequencial_simplista
#PBS -l walltime=1:00:00
#PBS -l nodes=1:ppn=40:r652
#PBS -qmei

module load gcc/5.3.0

cd CP/Projeto/sequencial/Simplista/

rm -f exec

gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec

I="1 2 3 4 5 6 7 8"

for i in $I; do
	echo $i
	./exec ../imgTeste/gun.pbm ../imgResult/gun.pbm ../times/Simplista/timegun.txt
	./exec ../imgTeste/digital.pbm ../imgResult/digital.pbm ../times/Simplista/timedigital.txt
	./exec ../imgTeste/exemplo.pbm ../imgResult/exemplo.pbm ../times/Simplista/timeexemplo.txt
done