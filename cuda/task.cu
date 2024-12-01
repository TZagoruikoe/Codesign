#include <stdio.h>
#include <cuda_runtime.h>

__global__ void sumVec(int* vec1, int* vec2, int* res, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < size) {
        vec1[idx] = idx * 10;
        vec2[idx] = idx * 2;
        res[idx] = vec1[idx] + vec2[idx];
    }
}

int main() {
    int* vec1;
    int* vec2;
    int* res;
    const int data_size = 1024 * 1024;

    cudaMalloc(&vec1, data_size * sizeof(int));
    cudaMalloc(&vec2, data_size * sizeof(int));
    cudaMalloc(&res, data_size * sizeof(int));

    cudaEvent_t start, stop, sync_event;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventCreate(&sync_event);

    cudaEventRecord(start);

    sumVec<<<(data_size + 255) / 256, 256>>>(vec1, vec2, res, data_size);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float elapsed_time = 0;
    cudaEventElapsedTime(&elapsed_time, start, stop);
    printf("Kernel execution time: %.2f ms\n", elapsed_time);

    cudaEventRecord(sync_event);

    cudaStream_t stream1, stream2;
    cudaStreamCreate(&stream1);
    cudaStreamCreate(&stream2);

    sumVec<<<(data_size + 255) / 256, 256, 0, stream1>>>(vec1, vec2, res, data_size / 2);
    sumVec<<<(data_size + 255) / 256, 256, 0, stream2>>>(vec1 + data_size / 2, vec2 + data_size / 2, res + data_size / 2, data_size / 2);

    cudaStreamWaitEvent(stream1, sync_event, 0);
    cudaStreamWaitEvent(stream2, sync_event, 0);

    cudaStreamSynchronize(stream1);
    cudaStreamSynchronize(stream2);

    printf("Streams synchronized after sync_event.\n");

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaEventDestroy(sync_event);
    cudaStreamDestroy(stream1);
    cudaStreamDestroy(stream2);
    cudaFree(vec1);
    cudaFree(vec2);
    cudaFree(res);

    return 0;
}