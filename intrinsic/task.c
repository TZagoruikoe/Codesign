#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#ifndef N
#define N 16
#endif

static double rtclock() {
    struct timeval Tp;
    int stat;

    stat = gettimeofday(&Tp, NULL);
    if (stat != 0) {
        printf("Error return from gettimeofday: %d", stat);
    }

    return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}

void fill_vector(int n, float* vect) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        vect[i] = rand() % 10000 * 0.001;
    }
}

void vector_add_intr(const float* a, const float* b, float* result1, int n) {
    for (int i = 0; i < n; i += 8) {
        __m256 vec_a = _mm256_load_ps(&a[i]);
        __m256 vec_b = _mm256_load_ps(&b[i]);
        
        __m256 vec_result = _mm256_add_ps(vec_a, vec_b);
        
        _mm256_store_ps(&result1[i], vec_result);
    }
}

void vector_add_simple(const float* a, const float* b, float* result2, int n) {
    for (int i = 0; i < n; i++) {
        result2[i] = a[i] + b[i];
    }
}

int main() {
    float* a = aligned_alloc(32, N * sizeof(float));
    float* b = aligned_alloc(32, N * sizeof(float));
    float* result1 = aligned_alloc(32, N * sizeof(float));
    float* result2 = (float*)malloc(N * sizeof(float));

    double start1, end1;
    double start2, end2;

    fill_vector(N, a);
    fill_vector(N, b);

    start1 = rtclock();
    vector_add_intr(a, b, result1, N);
    end1 = rtclock();

    start2 = rtclock();
    vector_add_simple(a, b, result2, N);
    end2 = rtclock();

    if (memcmp(result1, result2, N) == 0) {
        printf("GOOD\n");
    }
    else {
        printf("ERROR\n");
    }

    printf("Elapsed intrinsik time: %lf\n", end1 - start1);
    printf("Elapsed simple time: %lf\n", end2 - start2);

    free(a);
    free(b);
    free(result1);
    free(result2);

    return 0;
}