#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Request request, request_r;
    int message = 0;
    int flag;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        message = 42;
        printf("Процесс 0: Инициирование асинхронной отправки...\n");

        sleep(10);
        MPI_Issend(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        sleep(5);

        MPI_Test(&request, &flag, MPI_STATUS_IGNORE);
        if (flag == 1) {
            printf("Процесс 0: Сообщение принято.\n");
        }
        else {
            printf("Процесс 0: Сообщение не принято.\n");
        }

    }
    else if (rank == 1) {
        MPI_Irecv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request_r);
        sleep(3);

        MPI_Test(&request_r, &flag, MPI_STATUS_IGNORE);
        if (flag == 0) {
            printf("Процесс 1: Проблемы с отправкой данных. Отмена получения...\n");

            MPI_Cancel(&request_r);
            MPI_Request_free(&request_r);

            MPI_Test(&request_r, &flag, MPI_STATUS_IGNORE);
            if (flag == 1) {
                printf("Процесс 1: Получение успешно отменено.\n");
            }
        }
        else {
            printf("Процесс 1: Сообщение получено: %d.\n", message);
        }
    }

    MPI_Finalize();
    return 0;
}
