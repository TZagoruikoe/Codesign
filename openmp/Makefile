all: omptask
	./task 3 4

omptask: omptask.c
	gcc -fopenmp -Wall -Wextra -O3 omptask.c -o task

clean:
	rm ./task