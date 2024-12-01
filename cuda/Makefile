all: cudatask
	./task

cudatask: task.cu
	nvcc task.cu -o task

clean:
	rm ./task