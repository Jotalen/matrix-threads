//Week 11 Lab by Josue Gallegos Cortes (dal997096)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int **MA, **MB, **MC;
int N, M, K;
int total_sum = 0;

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

typedef struct {
    int id;
    int start_col;
    int end_col;
} package_t;

void multiply(int row, int col) {
    int sum = 0;
    for (int k = 0; k < N; k++) {
        sum += MA[row][k] * MB[k][col];
    }

    pthread_mutex_lock(&mutex1);
    MC[row][col] = sum;
    pthread_mutex_unlock(&mutex1);
}

void *worker(void *arg) {
    package_t *p = (package_t *)arg;

    for (int j = p->start_col; j < p->end_col; j++) {
        for (int i = 0; i < N; i++) {
            multiply(i, j);
        }
    }

    int local_sum = 0;
    for (int j = p->start_col; j < p->end_col; j++) {
        for (int i = 0; i < N; i++) {
            local_sum += MC[i][j];
        }
    }

    pthread_mutex_lock(&mutex2);
    total_sum += local_sum;
    pthread_mutex_unlock(&mutex2);

    free(p);
    return NULL;
}

void print_matrix(int **mat) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%5d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s N M K\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    M = atoi(argv[2]);
    K = atoi(argv[3]);

    if (N < M || N % M != 0) {
        printf("Invalid input: N must be >= M and N %% M == 0\n");
        return 1;
    }

    printf("Week 11 Lab (Thread Programming with Matrix Multiplication) - Josue Gallegos Cortes\n");
    printf("\nArguments: N=%d M=%d\n", N, M);
    system("date; hostname; whoami; ls -l");


    MA = (int **)malloc(N * sizeof(int *));
    MB = (int **)malloc(N * sizeof(int *));
    MC = (int **)malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++) {
        MA[i] = (int *)malloc(N * sizeof(int));
        MB[i] = (int *)malloc(N * sizeof(int));
        MC[i] = (int *)malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            MA[i][j] = K;
            MB[i][j] = K;
            MC[i][j] = 0;
        }
    }

    printf("\nMatrix A:\n");
    print_matrix(MA);

    printf("\nMatrix B:\n");
    print_matrix(MB);

    pthread_t threads[M];
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    int cols_per_thread = N / M;

    for (int t = 0; t < M; t++) {
        package_t *p = (package_t *)malloc(sizeof(package_t));
        p->id = t;
        p->start_col = t * cols_per_thread;
        p->end_col = p->start_col + cols_per_thread;

        pthread_create(&threads[t], NULL, worker, p);
    }

    for (int t = 0; t < M; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("\nMatrix C:\n");
    print_matrix(MC);

    printf("\nTotal Sum = %d\n", total_sum);

    printf("Week 11 Lab (Thread Programming with Matrix Multiplication) - Josue Gallegos Cortes\n");
    printf("\nArguments: N=%d M=%d\n", N, M);
    system("date; hostname; whoami; ls -l");

    for (int i = 0; i < N; i++) {
        free(MA[i]);
        free(MB[i]);
        free(MC[i]);
    }

    free(MA);
    free(MB);
    free(MC);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}
