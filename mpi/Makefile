all: mpitask
	mpirun -np 2 ./task

mpitask: task.c
	mpicc -Wall -Wextra -g -O3 task.c -o task

clean:
	rm ./task