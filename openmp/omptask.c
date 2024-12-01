#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>

int compute_square(int x) {
    return x * x;
}

int compute_cube(int x) {
    return x * x * x;
}

int main(int argc, char** argv) {
    int for_squere = atoi(argv[1]);
    int for_cube = atoi(argv[2]);
    int square_result, cube_result;

    #pragma omp parallel sections firstprivate(for_squere, for_cube)
    {
        #pragma omp section
        {
            square_result = compute_square(for_squere);
            printf("Square_section...\n");
            sleep(5);
            printf("Square of %d is %d\n", for_squere, square_result);
            sleep(2);
        }

        #pragma omp section
        {
            cube_result = compute_cube(for_cube);
            printf("Cube_section...\n");
            sleep(5);
            printf("Cube of %d is %d\n", for_cube, cube_result);
            sleep(2);
        }
    }

    printf("\nWithout section:\n");

    #pragma omp parallel firstprivate(for_squere, for_cube) num_threads(2)
    {
        square_result = compute_square(for_squere);
        printf("Square_start...\n");
        sleep(5);
        printf("Square_start of %d is %d\n", for_squere, square_result);

        cube_result = compute_cube(for_cube);
        printf("Cube_wait...\n");
        sleep(5);
        printf("Cube_wait of %d is %d\n", for_cube, cube_result);
    }

    return 0;
}
