all: clean run

run:
	gcc -O3 -std=c99 -fopenmp -lm pbm.c dist.c -o exec
	gcc -std=c99 run.c -o run
	./run

clean:
	rm -f run
	rm -f exec