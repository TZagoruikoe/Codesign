all: task
	./task

task: task.c
	gcc -DN=10000000 -mavx2 -mfma -Wall -Werror -O0 task.c -o task

clean:
	rm ./task