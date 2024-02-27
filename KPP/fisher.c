#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#define L 4
#define M 128
#define T 4.0
#define NTHR 2
#define TNUM M/NTHR

pthread_barrier_t start_barrier, end_barrier;

double *u0, *u;
double tau, t;

void* thread_function(void* arg) {
    long gran = (long)arg;
    if (gran == 0) {
        gran = 1;
    }

    while (t < T) {
        for (int m = gran; m < TNUM + gran; m++) {
            double tmp = (u0[m + 1] + u0[m - 1]) / 2;
            u[m] = (u0[m] + 2 * tau * tmp) / (1 + tau + (tau - 1) * tmp + u0[m]);
        }

        pthread_barrier_wait(&end_barrier);
        pthread_barrier_wait(&start_barrier);
    }
    return NULL;
}

void initialize_values() {
    double h = (double)L / M;
    tau = (h * h) / 2;
    u0 = malloc((M + 1) * sizeof(double));
    u = malloc((M + 1) * sizeof(double));
    for (int i = 0; i <= M; i++)
        u0[i] = 0;

    u0[0] = 1;
    t = tau;
}

int main() {
    // Initialization
    pthread_t threads[NTHR];
    pthread_barrier_init(&start_barrier, NULL, NTHR + 1);
    pthread_barrier_init(&end_barrier, NULL, NTHR + 1);
    initialize_values();

    // Thread creation
    for (long i = 0; i < NTHR; i++) {
        int err = pthread_create(&threads[i], NULL, thread_function, (void *)(i * TNUM));
        if (err != 0) {
            perror("Thread creation error");
            exit(EXIT_FAILURE);
        }
    }

    // Time measurement
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    while (t < T) {
        pthread_barrier_wait(&end_barrier);
        u0[M] = 0;
        u0[0] = 1.0;
        double* temp = u0;
        u0 = u;
        u = temp;
        t += tau;
        pthread_barrier_wait(&start_barrier);
    }

    gettimeofday(&end, NULL);
    // Join threads
    for (int i = 0; i < NTHR; i++) {
        pthread_join(threads[i], NULL);
    }

    // Time calculation
    long long start_usec = start.tv_sec * 1000000 + start.tv_usec;
    long long end_usec = end.tv_sec * 1000000 + end.tv_usec;
    double elapsed = (double)(end_usec - start_usec) / 1000000.0;
    printf("Elapsed time (sec): %.4f\n", elapsed);

    // Printing results
    for (int i = 0; i <= M; i += 16) {
        printf("%.3e ", u0[i]);
        if (i % 16 == 15) {
            printf("\n");
        }
    }
    printf("\n");

    // Memory cleanup
    free(u0);
    free(u);

    return 0;
}
