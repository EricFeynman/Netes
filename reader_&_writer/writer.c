#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define BUFFER_SIZE 256

int main() {
    key_t key = ftok("writer.c", 1);
    if (key == -1) {
        perror("ftok");
        return EXIT_FAILURE;
    }

    int semaphore, shared_memory;
    struct sembuf sem_operation;

    char* shared_memory_ptr;
    char input_buffer[BUFFER_SIZE];

    semaphore = semget(key, 2, IPC_CREAT | 0666);
    if (semaphore == -1) {
        perror("semget");
        return EXIT_FAILURE;
    }

    shared_memory = shmget(key, BUFFER_SIZE, IPC_CREAT | 0666);
    if (shared_memory == -1) {
        perror("shmget");
        return EXIT_FAILURE;
    }
    
    semctl(semaphore, 0, SETVAL, 1);
    semctl(semaphore, 1, SETVAL, 0);
    
    shared_memory_ptr = shmat(shared_memory, NULL, 0);
    if (shared_memory_ptr == (void*) -1) {
        perror("shmat");
        return EXIT_FAILURE;
    }
    
    sem_operation.sem_flg = 0;
    int flag = 1;

    while (flag) {
        printf("Enter a message: ");
        fgets(input_buffer, BUFFER_SIZE, stdin);

        if (strcmp(input_buffer, "exit\n") == 0) {
            flag = 0;
        }

	
        sem_operation.sem_num = 0;
        sem_operation.sem_op = -1;
        semop(semaphore, &sem_operation, 1);

        strcpy(shared_memory_ptr, input_buffer);

        sem_operation.sem_num = 1;
        sem_operation.sem_op = 1;
        semop(semaphore, &sem_operation, 1);
    }

    semctl(semaphore, 0, IPC_RMID);
    shmdt(shared_memory_ptr);
    shmctl(shared_memory, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}
