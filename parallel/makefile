all: clean run

run:
	module load gcc/5.3.0
	gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec
	gcc run.c -o run
	./run

clean:
	rm -f exec