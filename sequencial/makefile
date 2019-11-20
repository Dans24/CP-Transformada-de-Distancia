all: clean run

run:
	module load gcc/5.3.0
	gcc -O3 -std=c99 pbm.c dist.c -o exec
	./exec imgTeste/gun.pbm imgResult/gun.pbm times/timegun.txt
	./exec imgTeste/flowers.pbm imgResult/flowers.pbm times/timeflowers.txt
	./exec imgTeste/digital.pbm imgResult/digital.pbm times/timedigital.txt
	./exec imgTeste/exemplo.pbm imgResult/exemplo.pbm times/timeexemplo.txt

clean:
	rm -f exec